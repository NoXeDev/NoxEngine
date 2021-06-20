const fs = require("fs")
const path = require("path")

let NoxEnginePath = process.cwd().split("NoxEngine")[0].concat("NoxEngine\\")

let buffer = fs.readFileSync(path.join(NoxEnginePath, 'devtools', 'nxp', 'index.js'))

eval(buffer.toString())