# 3D Engine

## General features:

- Modular code structure.
- Basic lighting model.
- External 3D model loading using Assimp.
- Object component system (Mesh, Transform, etc.)
- Primitive mesh generation (Cube, Sphere, Torus, etc.)
- World skybox cubemap texture loading.
- Object material customisation (Roughness, Metalness, Colour, Light interaction, etc.)
- Diffuse Texture mapping & Normal texture mapping.
- Easy to use abstractions on top of OpenGL.

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
