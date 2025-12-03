# 3D Engine


## Table of Contents
* [General Features](#general-features)
* [Run](#run)
* [Install / Build](#install--build)
    * [Linux](#linux)
    * [Windows (Cross-Compilation)](#windows-cross-compilation)
* [Sources Used](#sources-used)

---

## General features:

* **Modular code structure.**
* **Basic lighting model.**
* External 3D model loading using **Assimp**.
* Object component system (**Mesh**, **Transform**, etc.)
* Primitive mesh generation (Cube, Sphere, Torus, etc.)
* World **skybox cubemap** texture loading.
* Object material customisation (Roughness, Metalness, Colour, Light interaction, etc.)
* **Diffuse Texture mapping** & **Normal texture mapping**.
* Easy to use abstractions on top of **OpenGL**.


## Run:

Distribution pakacges with pre-compiled executables / binaries are available at: 

Linux: `dist/linux/app`

Windows: `dist/win/app.exe`

## Install / Build:

### Linux:

The latest pre-compiled executable is available in `dist/linux` 

Build:
```
$ make linux
```

Run (Directly):
```
$ ./build/linux/app
```

Run (Using default target):
```
$ make run
```

Create Distribution Package:
```
$ make dist-linux
```

### Windows (Cross-Compilation):

You have to be on Linux in order to cros-compile this to Windows.   

The latest pre-compiled executable is available in `dist/win` along with the required dlls.

Build:
```
$ make win
```

Create Distribution Package:
```
$ make dist-win
```

### Sources used:   
https://learnopengl.com/Model-Loading/Mesh   
https://learnopengl.com/Lighting/Basic-Lighting   
https://learnopengl.com/Lighting/Materials   
https://learnopengl.com/Model-Loading/Assimp   
https://www.youtube.com/watch?v=sP_kiODC25Q   
https://www.mbsoftworks.sk/tutorials/opengl3/20-assimp-model-loading/   
https://www.ogldev.org/www/tutorial22/tutorial22.html   
https://www.ogldev.org/www/tutorial25/tutorial25.html   
https://jaxry.github.io/panorama-to-cubemap/   
https://antongerdelan.net/opengl/vertexbuffers.html   
https://antongerdelan.net/opengl/shaders.html   
https://www.glfw.org/documentation.html   
https://www.glfw.org/docs/latest/window_guide.html   
https://learnopengl.com/Advanced-Lighting/Normal-Mapping   
https://www.youtube.com/watch?v=TnewxQxtoKs   
https://www.youtube.com/watch?v=LRbgii6mVU4   
https://stackoverflow.com/questions/29042849/implementing-normal-mapping-using-opengl-glsl   
https://www.opengl-tutorial.org/intermediate-tutorials/tutorial-13-normal-mapping/   
