# NoxEngine

![License](https://img.shields.io/apm/l/vim-mode)

NoxEngine is a basic, open source, render engine make with openGl.

How it work ?
=====

NoxEngine follow a basic render pipeline. Load, shade, render. NoxEngine is using the `VAOs/VBOs` render method for rendering objects. He also using a custom 3D model format : `NoxModel`.

NoxModels
=====

NoxModel is a basic binary file, contains `floats and int values`. The engine using the `NMloader` class for load NoxModels into memory.

NXP
=====

`NXP` is a devtool making a layer between the user and the compiler `Make`. He dowload libs, and recompile it when needed. He will also deploy a preconfigured config for some IDE. Only vs-code is supported for the moment.

How to build ?
=====

`NXP` is doing all the libs install and the project configuration for you, all you need is execute `./nxp.bat build` and NXP will download, configure and build the project for you. If you need to reload the project just execute `./nxp.bat reload` for reload project config