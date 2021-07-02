const child = require("child_process")
module.exports = function(download, NoxEnginePath, MSbuildPath) {
    return new Promise((res) => {
        async function promise(download, NoxEnginePath, MSbuildPath){
            const premake = "https://github.com/premake/premake-core/releases/download/v5.0.0-alpha16/premake-5.0.0-alpha16-windows.zip"
            await download(premake, NoxEnginePath+"libs\\"+"SOIL2", {
                extract: true
            })

            await new Promise((res) => {
                let premake = child.spawn(NoxEnginePath+"libs\\"+"SOIL2\\"+"premake5.exe", ["vs2017"], {
                    cwd:NoxEnginePath+"libs\\"+"SOIL2\\"
                }).on("close", (code) => {
                    if(code !== 0){
                        console.log("ERROR PREMAKE 5")
                        process.exit(1)
                    }else {
                        res()
                    }
                })
                premake.stderr.on("data", (data) => {console.log("[-] - ERROR : " + data.toString().replace("\n", ""))})
                premake.stdout.on("data", (data) => {console.log("[*] - PREMAKE 5 : " + data.toString().replace("\n", ""))})
            })
            
            await new Promise((res) => {
                console.log("[*] - SOIL2 compilation ...")
                let build = child.spawn(MSbuildPath, ["./soil2-static-lib.vcxproj", "/p:configuration=Release", "/p:platform=x64", "/p:WindowsTargetPlatformVersion=10.0.17763.0"], {
                    cwd:NoxEnginePath+"libs\\"+"SOIL2\\"+"make\\"+"windows\\"
                }).on("close", (code) => {
                    if(code !== 0){
                        console.log("ERROR BUILDING SOIL2")
                        process.exit(1)
                    }else {
                        res()
                    }
                })
                build.stderr.on("data", (data) => {console.log("[-] - ERROR : " + data.toString().replace("\n", ""))})
                build.stdout.on("data", (data) => {console.log("[*] - PREMAKE 5 : " + data.toString().replace("\n", ""))})
            })

            res()
        }
        promise(download, NoxEnginePath, MSbuildPath).then(() => res())
    })
}