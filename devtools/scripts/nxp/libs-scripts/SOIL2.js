const child = require("child_process")
module.exports = function(download, NoxEnginePath) {
    return new Promise((res) => {
        async function promise(download, NoxEnginePath){
            const premake = "https://github.com/premake/premake-core/releases/download/v5.0.0-alpha16/premake-5.0.0-alpha16-windows.zip"
            await download(premake, NoxEnginePath+"libs\\"+"SOIL2", {
                extract: true
            })

            await new Promise((res) => {
                child.spawn(NoxEnginePath+"libs\\"+"SOIL2\\"+"premake5.exe", ["gmake"], {
                    cwd:NoxEnginePath+"libs\\"+"SOIL2\\"
                }).stdout.on("data", (data) => {console.log("[*] - PREMAKE 5 : " + data.toString().replace("\n", ""))}).on("end", () => res())
            })
            
            await new Promise((res) => {
                child.spawn("make", ["soil2-shared-lib", "config=release_x86_64", "CC=gcc"], {
                    cwd:NoxEnginePath+"libs\\"+"SOIL2\\"+"make\\"+"windows\\"
                }).stdout.on("data", (data) => {console.log("[*] - SOIL2 MAKE : " + data.toString().replace("\n", ""))}).on("end", () => res())
            })

            res()
        }
        promise(download, NoxEnginePath).then(() => res())
    })
}