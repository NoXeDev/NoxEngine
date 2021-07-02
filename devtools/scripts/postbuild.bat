echo !==== PREPARE DIST ====!
echo F|xcopy "libs\GLEW\bin\Release\x64\glew32.dll" "dist\%1\glew32.dll" /F/y
echo F|xcopy "libs\GLFW\lib-static-ucrt\glfw3.dll" "dist\%1\glfw3.dll" /F/y
xcopy "test\res\" "dist\%1\res\" /E/H/y
xcopy "src\shaders\glsl\" "dist\%1\res\glsl\" /E/H/y