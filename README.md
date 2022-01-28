# LearnOpenGL
## Get Started with OpenGL

This is a practice repo for mastering Modern OpenGL and learn how to startup a graphics project orgnized by Cmake from scratch.

We may mostly follow the awesome classic [OpenGL tutorial](https://learnopengl.com/) , with various creative ideas you may come up with on the way.

First of all, we're going to build our [Graphics Framework](https://github.com/BFU-Graphics/LearnOpenGL.git)

## Build Instruction

[Clion](https://www.jetbrains.com/clion/) is the mostly recommended IDE to build and develop a this repo.

### I. clone the repo and dependencies repo

```git
git clone https://github.com/BFU-Graphics/LearnOpenGL.git
git clone https://github.com/BFU-Graphics/Graphics-Dependencies.git
```

### II. build dependencies

Goto [Graphics-Dependencies](https://github.com/BFU-Graphics/Graphics-Dependencies), and follow the build instruction, remember to set cmake options as

```cmake
-DEXTERNAL_INSTALL_DIR="<the LearnOpenGL root dir>/external"
```

### III. build LearnOpenGL

