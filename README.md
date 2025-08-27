# Learn OpenGL Tutorial Series
Tutorial from [LearnOpenGL.com](https://learnopengl.com/)

---
## Setup
Install [glfw](https://www.glfw.org/) and [glad](https://gen.glad.sh/)

### Prerequsits
* gcc
* cmake and make
* unzip

### glfw
1. Download latest glfw
2. Unzip archive
3. [Compile](https://www.glfw.org/docs/latest/compile_guide.html) and install (`cmake install`) with cmake

### glad
1. Download latest [glad](https://gen.gald.sh/)
    * use gl Version 3.3
    * Core (not Compatibility)
    * tick `loader` option
2. Unzip archive
3. Copy the contents of the includes folder to your includes
4. Copy and rename the gl.c file to the src/ folder and rename it to `gl.cpp`
