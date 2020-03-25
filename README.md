# Marching Cubes Experiment

### [Demo video](https://www.youtube.com/watch?v=yvjj7Xs-3U8)

## How to install on windows
1. Clone repo to local directory
2. [Install MinGW](https://sourceforge.net/projects/mingw-w64/)
3. Install libs
   1. [Find the latest GLM release](https://github.com/g-truc/glm/tags)
      and put `glm-*version#*.zip/glm` in `/lib` as `/lib/glm`
   2. [Download GLEW binaries](http://glew.sourceforge.net/)
      and put `glew...win32.zip/glew...` in `/lib` as `/lib/glew`
   3. [Get 64-bit GLFW binaries](https://www.glfw.org/download.html)
      and put `glfw...WIN64.zip/glfw...` in `/lib` as `/lib/glfw`
4. Run build.cmd

## Library versions used by me 27/05/2019
1. GLM 0.9.9.5
2. GLEW 2.1.0
3. GLFW 3.3
