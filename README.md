# 3D Engine


## Table of Contents
* [General Features](#general-features)
* [Run](#run)
* [Install / Build](#install--build)
    * [Linux](#linux)
    * [Windows (Cross-Compilation)](#windows-cross-compilation)
* [Sources](#sources)

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

## Build:

### Linux:

The latest pre-compiled executable is available in `dist/linux` 

Build:
```
$ mkdir build && cd build
$ cmake .. 
$ cmake --build .              # Compile
```

Create Distribution Package:
```
$ cmake -- build . --target dist-linux
```

### Windows (Cross-Compilation):

The latest pre-compiled executable is available in `dist/win` along with the required libraries.

Build:
```
$ mkdir build-win && cd build-win
$ cmake .. -DCMAKE_TOOLCHAIN_FILE=toolchain-mingw.cmake
$ cmake --build .              # Compile
```

Create Distribution Package:
```
$ cmake -- build . --target dist-win
```

## Run:

### Linux:

Directly: Through `build/linux/app` or `dist/linux/app`    

Cmake:
```
$ cd build
$ cmake --build . --target run
```

###  Windows:
Through `build-win/app.exe` or `dist/win/app.exe`

### Sources:   
Planet textures obtained from:   
https://www.solarsystemscope.com/textures/

External models and their textures obtained from:        
https://sketchfab.com/features/free-3d-models   
https://free3d.com/   
https://www.cgtrader.com/free-3d-models   

Sources used:         
https://learnopengl.com/Model-Loading/Mesh   
https://learnopengl.com/Lighting/Basic-Lighting   
https://learnopengl.com/Lighting/Materials   
https://learnopengl.com/Model-Loading/Assimp    
https://www.youtube.com/watch?v=sP_kiODC25Q    
https://www.mbsoftworks.sk/tutorials/opengl3/20-assimp-model-loading/    
https://www.ogldev.org/www/tutorial22/tutorial22.html    
https://www.ogldev.org/www/tutorial25/tutorial25.html    
https://learnopengl.com/Advanced-OpenGL/Cubemaps    
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
