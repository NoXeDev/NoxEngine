const fs = require("fs")
const download = require("download")
const path = require("path")
const child = require("child_process")
const { hashElement } = require("folder-hash")

console.log("[*] - NoxProject Loader starting")
let NoxEnginePath = process.cwd().split("NoxEngine")[0].concat("NoxEngine\\")
if(!fs.existsSync(NoxEnginePath + "nxp.json"))
{
    console.log("[X] - nxp.json not found")
    process.exit(1)
}

if(process.argv[2] == undefined){
    console.log("Help (< > : optionnal arguments) :\n\n- build < make target / config=release (specify for make we need a release) >\n- reload < IDE (specify we just want reload IDE config)>\n")
    process.exit(0)
}

console.log("[*] - Fetching nxp.json")
const nxpcfg = require(NoxEnginePath + "nxp.json")

if(!nxpcfg["avaible-platform"].includes("win32")){
    console.log(`[*] - ${nxpcfg["name"]} can't be builded on ${process.platform}`)
    process.exit(1)
}

if(process.arch !== "x64"){
    console.log(`[*] - ${nxpcfg["name"]} can't be builded on ${process.arch}`)
    process.exit(1) 
}

if(process.argv[2] == "reload"){
    if(process.argv[3] == "IDE"){
        deployIDEconf()
    }else {
        libsDownload()
    }
}

if(process.argv[2] == "build"){
    build()
}

async function copyDir(src, dest) {
    await fs.promises.mkdir(dest, { recursive: true });
    let entries = await fs.promises.readdir(src, { withFileTypes: true });

    for (let entry of entries) {
        let srcPath = path.join(src, entry.name);
        let destPath = path.join(dest, entry.name);

        entry.isDirectory() ?
            await copyDir(srcPath, destPath) :
            await fs.promises.copyFile(srcPath, destPath);
    }
}

async function build(){
    if(!fs.existsSync(path.join(NoxEnginePath, "libs"))){
        if(!fs.existsSync(path.join(NoxEnginePath, "libs", "checksum.json"))){
            console.log("[*] - Libs missing... Reload...")
            await libsDownload()
        }
    }

    console.log("[*] - Checking libs integrity")

    let foldersChecksum = await checksumLibs()
    let checksumOriginal = await require(path.join(NoxEnginePath, "libs", "checksum.json"))

    let corruptedFiles = false

    for(hash in checksumOriginal){
        if(hash !== "checksum.json"){
            if(foldersChecksum[hash] !== checksumOriginal[hash]){
                corruptedFiles = true
            }
        }
    }

    if(corruptedFiles){
        console.log("[*] - Libs files are corrupted... Reload project ...")
        await libsDownload()
    }
    console.log("[*] - Building with make")

    let make = "all"
    if(process.argv[3]){
        make = process.argv[3]
    }

    let config = "debug"
    if(process.argv[4]){
        config = process.argv[4]
    }
    await new Promise((res) => {
        child.spawn("make", ["-f", "Engine.nxp", make, "NAME="+nxpcfg["name"], "config="+config], {cwd:NoxEnginePath})
        .stdout.on("data", (data) => console.log("[*] - MAKE : " + data.toString().replace("\n", ""))).on("end", () => res()).on("error", (err) => {
            throw new Error("[-] - Build error : "+err)
        })
    })

    console.log("[*] - Builded !")
}

function getCheckSum(file){
    return new Promise((res, rej) => {
        let pathLibs = path.join(NoxEnginePath, "libs", file)
        hashElement(pathLibs, {algo: "sha256", encoding: "hex"})
        .then(hash => {
            res(hash)
        })
        .catch(error => {
            rej('hashing failed:', error)
        })
    })
}

async function checksumLibs(){
    let filesLibs = await fs.promises.readdir(path.join(NoxEnginePath, "libs"))
    let checksumJson = {}
    for(i = 0 ; i < filesLibs.length ; i++){
        if(filesLibs[i] !== "checksum.json"){
            let checksum = await getCheckSum(filesLibs[i])
            checksumJson[filesLibs[i]] = checksum.hash
        }
    }

    return checksumJson
}

async function libsDownload() {
    if(fs.existsSync(path.join(NoxEnginePath, "libs"))){
        await fs.promises.rm(path.join(NoxEnginePath, "libs"), { recursive: true })
    }

    for(lib in nxpcfg[`libs-${process.platform}`]){
        console.log("[+] - Downloading and extract : " + lib)
        await download(nxpcfg[`libs-${process.platform}`][lib], path.join(NoxEnginePath, "libs"), {
            extract: true,
            map: file => {
                let splittedname = file.path.split("/")
                splittedname[0] = lib
                file.path = splittedname.join("/");
                return file;
            }
        })
    
    }

    if(nxpcfg["need-rebuild"]){
        console.log("[*] - Some libs need to be rebuild before start build")
        for(i = 0 ; i < nxpcfg["need-rebuild"].length ; i++){
            console.log("[*] - Launch script for rebuild : " + nxpcfg["need-rebuild"][i])
            let libscriptsPath = path.join(NoxEnginePath, "devtools", "scripts", "nxp", "libs-scripts")
            let rebuilder = await require(path.join(libscriptsPath, nxpcfg["need-rebuild"][i] + ".js"))
            await rebuilder(download, NoxEnginePath)
            console.log("[*] - "+nxpcfg["need-rebuild"][i]+" Rebuild Succes !")
        }
    }

    console.log("[*] - Checksum generation for libs")
    let checksumJson = await checksumLibs()
    await fs.promises.writeFile(path.join(NoxEnginePath, "libs", "checksum.json"), JSON.stringify(checksumJson, 1, 1))

    await deployIDEconf()
}

async function deployIDEconf()
{
    if(nxpcfg["IDE-debug-cfg"]){
        console.log("[*] - Config detected for some IDE. Deployement ...")
        for(i = 0 ; i < nxpcfg["IDE-debug-cfg"].length ; i++){
            await copyDir(path.join(NoxEnginePath, "devtools", "scripts", "nxp", "ide-cfg", nxpcfg["IDE-debug-cfg"][i]), path.join(NoxEnginePath, "."+nxpcfg["IDE-debug-cfg"][i]))
        }
    }
}