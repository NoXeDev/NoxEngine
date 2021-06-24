echo !==== PREPARE DIST ====!
cp libs/GLEW/bin/Release/x64/glew32.dll dist/%1/glew32.dll
cp libs/GLFW/lib-static-ucrt/glfw3.dll dist/%1/glfw3.dll
cp -r test/res dist/%1/
cp -r src/shaders/glsl dist/%1/res/