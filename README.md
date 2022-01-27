# LearnOpenGL
## Get Started with OpenGL

This is a practice repo for mastering Modern OpenGL and learn how to startup a graphics project orgnized by Cmake from scratch.

We may mostly follow the awesome classic [OpenGL tutorial](https://learnopengl.com/) , with various creative ideas you may come up with on the way.

First of all, we're going to build our [Graphics Framework](https://github.com/BFU-Graphics/LearnOpenGL.git)

## Build Instruction

[Clion](https://www.jetbrains.com/clion/) is the mostly recommended IDE to build and develop a this repo.

### I. clone the repo

```git
git clone https://github.com/BFU-Graphics/LearnOpenGL.git
cd LearnOpenGL
git submodule init
git submodule update
```

### II. configure dependencies one by one

#### glfw

1. open `glfw` folder as Clion Project

2. set build type to `Release`

3. set CMake options to determine `glfw` install dir

   ```cmake
   -DCMAKE_INSTALL_PREFIX="../../../external"
   ```

4. `Build` -> `Install`

#### assimp

1. open `assimp` folder as Clion Project

2. set build type to `Release`

3. set CMake options to determine `assimp` install dir

   ```cmake
   -DCMAKE_INSTALL_PREFIX="../../../external"
   ```

4. turn off the option `BUILD_SHARED_LIBS` in root CMakeLists.txt

   ```cmake
   OPTION( BUILD_SHARED_LIBS
     "Build package with shared libraries."
     ON # turn this to OFF
   )
   ```

5. `Reset Cache and Reload Project`

6. `Build` -> `Install`

#### glad

`glad` is recommend to get it from the [webservice](https://glad.dav1d.de/), and directly copy the `include` dir and `src` dir under `external` dir and remenber compile the `glad.c` with your target.

#### glm

`glm` is a header only library, copy `vendor/glm/glm` to `external/include`

#### stb

`stb` is a header only library, copy `vendor/stb` to `external/include`

### III. build repo

Open repo with Clion