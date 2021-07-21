module.exports = async (download, NoxEnginePath, link, fs) => {
    await fs.promises.mkdir(NoxEnginePath+"\\libs"+"\\JSON")
    await download(link, NoxEnginePath+"\\libs"+"\\JSON", {extract: true})
}