const fs = require("fs")
const download = require("download")
const path = require("path")
const child = require("child_process")
const { hashElement } = require("folder-hash")

console.log("[*] - NoxProject Loader starting")
let NoxEnginePath = process.cwd().split("NoxEngine")[0].concat("NoxEngine\\")
let MSBuildPath = path.join(process.env["programfiles(x86)"], "Microsoft Visual Studio", "2017", "BuildTools", "MSBuild", "15.0", "Bin", "MSBuild.exe")

async function MSBuildInstall()
{
    console.log("[*] - Installing Chocolatey...")
    await new Promise((res) => {
        child.spawn('powershell', ["-Command", `& {Start-Process Powershell.exe -Wait -Verb RunAs -ArgumentList "Set-ExecutionPolicy Bypass -Scope Process -Force; [System.Net.ServicePointManager]::SecurityProtocol = [System.Net.ServicePointManager]::SecurityProtocol -bor 3072; iex ((New-Object System.Net.WebClient).DownloadString('https://chocolatey.org/install.ps1'))"}`, "-Wait"])
        .on("close", (code) => {
            if(code !== 0){
                console.log("[*] - Failed to install chocolatey, disconnect...")
                process.exit(1)
            }else {
                res()
            }
        })
    })

    let ChocoPath = path.join(process.env["ProgramData"], "chocolatey", "choco.exe")

    console.log("[*] - Installing VS2017 BuildTool...")
    await new Promise((res) => {
        child.spawn('powershell', ["-Command", `& {Start-Process Powershell.exe -Wait -Verb RunAs -ArgumentList "${ChocoPath} install visualstudio2017buildtools -y;${ChocoPath} install visualstudio2017-workload-vctools -y;${ChocoPath} install windows-sdk-10-version-1809-all -y"}`, "-Wait"])
        .on("close", (code) => {
            if(code !== 0){
                console.log("[*] - Failed to install VS2017 BuildTool, disconnect...")
                process.exit(1)
            }else {
                res()
            }
        })
    })
}

if(!fs.existsSync(NoxEnginePath + "nxp.json"))
{
    console.log("[X] - nxp.json not found")
    process.exit(1)
}

if(process.argv[2] == undefined){
    console.log("Help (< > : optionnal arguments) :\n\n- build < make target / config=release (specify for make we need a release) >\n- reload < IDE (specify we just want reload IDE config)>\n- clean < all(default) / workspace / IDE / Libs> : clean project")
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
    }else if(process.argv[3] == "msbuild"){
        MSBuildInstall()
    }
    else {
        libsDownload()
    }
}

if(process.argv[2] == "build"){
    build()
}

if(process.argv[2] == "msbuild"){
    MSBuildInstall()
}

if(process.argv[2] == "clean"){
    clean(process.argv[3])
}

async function clean(target){
    if(target == undefined){
        target = 'all'
    }
    const dirs = await fs.promises.readdir(NoxEnginePath)
    const targets = {
        'all': ['out', 'dist', 'libs', '.vscode'],
        'workspace': ['out', 'dist'],
        'IDE': ['.vscode'],
        'libs': ['libs'],
    }
    dirs.forEach(async(e) => {
        if(targets[target].includes(e)){
            await fs.promises.rm(path.join(NoxEnginePath, e), {recursive: true})
        }
    })
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
    if(!fs.existsSync(MSBuildPath)){
        console.log("[*] - MSbuild is not installed on your computer... Installing...")
        await MSBuildInstall()
    }

    if(!fs.existsSync(path.join(NoxEnginePath, "libs")) || !fs.existsSync(path.join(NoxEnginePath, "libs", "checksum.json"))){
        console.log("[*] - Libs missing... Reload...")
        await libsDownload()
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
    console.log("[*] - Building with MSBuild")

    let config = "Debug"
    if(process.argv[3]){
        config = process.argv[3]
    }
    await new Promise((res) => {
        let makeProcess = child.spawn(MSBuildPath, ["./Engine.nxp", "/p:configuration="+config, "/p:platform=x64"], {cwd:NoxEnginePath}).on("close", (code) => {
            if(code !== 0){
                console.log("[-] - Build Error, disconnect ...")
                process.exit(1)
            }else {
                res()
            }
        })

        makeProcess.stdout.on("data", (data) => console.log("[*] - MSBUILD : " + data.toString().replace("\n", "")))
        makeProcess.stderr.on("data", (data) => console.log("[*] - MSBUILD ERROR : " + data.toString().replace("\n", "")))
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
    if(!fs.existsSync(MSBuildPath)){
        console.log("[*] - MSbuild is not installed on your computer... Installing...")
        await MSBuildInstall()
    }

    if(fs.existsSync(path.join(NoxEnginePath, "libs"))){
        await fs.promises.rm(path.join(NoxEnginePath, "libs"), { recursive: true })
    }

    for(lib in nxpcfg[`libs-${process.platform}`]){
        console.log("[+] - Downloading and extract : " + lib)
        if(nxpcfg["specific-download"].includes(lib)){
            console.log(`[*] - Specific download script is specify for ${lib}. Launching...`)
            let libdownloadPath = path.join(NoxEnginePath, "devtools", "scripts", "nxp", "libs-download")
            let downloader = await require(path.join(libdownloadPath, lib+".js"))
            await downloader(download, NoxEnginePath, nxpcfg[`libs-${process.platform}`][lib], fs)
            console.log(`[*] - ${lib} script download end !`)
        }else {
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
    }

    if(nxpcfg["need-rebuild"]){
        console.log("[*] - Some libs need to be rebuild before start build")
        for(i = 0 ; i < nxpcfg["need-rebuild"].length ; i++){
            console.log("[*] - Launch script for rebuild : " + nxpcfg["need-rebuild"][i])
            let libscriptsPath = path.join(NoxEnginePath, "devtools", "scripts", "nxp", "libs-scripts")
            let rebuilder = await require(path.join(libscriptsPath, nxpcfg["need-rebuild"][i] + ".js"))
            await rebuilder(download, NoxEnginePath, MSBuildPath)
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