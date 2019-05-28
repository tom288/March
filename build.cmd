@echo off

echo BUILDING...

g++ -std=c++11 -Wall -Og -march=native -o launch.exe ^
src/main.cpp ^
-I "lib\glfw\include" ^
-I "lib\glm" ^
-I "lib\glew\include" ^
-L "lib\glfw\lib-mingw-w64" ^
-L "lib\glew\lib\Release\x64" ^
-lglfw3 -lgdi32 -lopengl32 -lglew32

if %errorlevel% == 0 (
   echo LAUNCHING...
   copy >NUL /Y lib\glew\bin\Release\x64\glew32.dll glew32.dll
   launch.exe
   echo CLOSING...
) else ( pause )
