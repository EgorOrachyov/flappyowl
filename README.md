# flappyowl

Flappy owl is a simple 2d side-scrolling game inspired by a flappy bird game. The game itself is simple: scene consists
of a dozen of objects. It has a couple of particle effects, audio effects, sprites and scripts. The game logic is
written using Lua scripting language. Engine itself is written using C++, Vulkan, OpenAL, Lua, Yaml, etc.

Gameplay gif:

![gif](https://github.com/EgorOrachyov/flappyowl/raw/main/docs/gifs/background.gif?raw=true&sanitize=true)

> The work on the engine currently in the progress! Currently, I am working on ECS support, multi-threading, separate
> thread for vulkan backend, LZ4 resources compression, BCn textures compression, new scripting backend, new audio
> system, and brand new 3d rendering system. Check this out in new repo: https://github.com/EgorOrachyov/wmoge.

## About engine

### Preview

| ![media](https://github.com/EgorOrachyov/flappyowl/raw/main/docs/preview/window.png?raw=true&sanitize=true) |
|-------------------------------------------------------------------------------------------------------------|
| Primary window with playing game                                                                            |

| ![media](https://github.com/EgorOrachyov/flappyowl/raw/main/docs/preview/console.png?raw=true&sanitize=true) |
|--------------------------------------------------------------------------------------------------------------|
| In-game debug console with variables and commands                                                            |

| ![media](https://github.com/EgorOrachyov/flappyowl/raw/main/docs/preview/scripting.png?raw=true&sanitize=true) |
|----------------------------------------------------------------------------------------------------------------|
| Lua-based scripting for a game logic with full access to engine C++ API                                        |

| ![media](https://github.com/EgorOrachyov/flappyowl/raw/main/docs/preview/profiling.png?raw=true&sanitize=true) |
|----------------------------------------------------------------------------------------------------------------|
| Built-in profiler to collect trace                                                                             |

| ![media](https://github.com/EgorOrachyov/flappyowl/raw/main/docs/preview/config.png?raw=true&sanitize=true) |
|-------------------------------------------------------------------------------------------------------------|
| Ini-based config files for engine and game configuration                                                    |

| ![media](https://github.com/EgorOrachyov/flappyowl/raw/main/docs/preview/log.png?raw=true&sanitize=true) |
|----------------------------------------------------------------------------------------------------------|
| Logging support with file location, message type and coloring                                            |

### Features

* Moder C++17 standard based code
* Platform abstraction
* Async resource loading system
* Built-in time profiler with support to Google trace export
* Console, console commands and console variables for debugging
* Yaml for resource formats
* Config files support
* Action mapping system for input
* Resource meta information for import from external formats
* Vulkan API based rendering device abstraction
* Async shaders compilation
* Async pipelines compilation
* Online and offline shaders and pipelines cache for compilation speedup
* Sprites rendering
* True-type fonts rendering for UI
* Lua 5+ support for game logic scripting
* Entity-component based scene structure
* Scene de-serialization from yaml
* Configurable CPU-based parallel particles system
* OpenAL based audio engine support

### Platforms

* Windows 10 (tested on Windows 10).
* Linux-based OS (tested on Ubuntu 20.04).
* macOS (tested on 10.14 Mojave).

### Dependencies

* [assimp](https://github.com/assimp/assimp) for geometry, material and scene assets importing into engine.
* [audio file](https://github.com/adamstark/AudioFile) for simple audio loading from wav files.
* [compressonator](https://github.com/GPUOpen-Tools/compressonator) texture compression library.
* [cxxopts](https://github.com/jarro2783/cxxopts) for command-line options processing.
* [freetype](https://github.com/freetype/freetype) for true-type fonts loading and rendering.
* [glfw](https://github.com/glfw/glfw) for cross-platform window and input management.
* [glslang](https://github.com/KhronosGroup/glslang) for runtime glsl to spir-v shaders compilation.
* [lua](https://github.com/walterschell/Lua) project C source with cmake script for scripting.
* [lua bridge](https://github.com/vinniefalco/LuaBridge) to simplify lua and C++ bindings.
* [lz4](https://github.com/lz4/lz4) for fast compression and decompression at runtime.
* [magic enum](https://github.com/Neargye/magic_enum) for static enum reflection.
* [openal soft](https://github.com/kcat/openal-soft) as a software audio renderer.
* [rapidyaml](https://github.com/biojppm/rapidyaml) for fast yaml files parsing and serialization.
* [robin-hood hashing](https://github.com/martinus/robin-hood-hashing) for fast & memory efficient hashtable.
* [stbimage](https://github.com/nothings/stb) image utilities for images loading, writing and resizing.
* [svector](https://github.com/martinus/svector) compact SVO optimized vector for C++17 or higher.
* [tinyxml2](https://github.com/leethomason/tinyxml2) for utf-8 xml files processing.
* [vma](https://github.com/GPUOpen-LibrariesAndSDKs/VulkanMemoryAllocator) vulkan library for memory allocation.
* [volk](https://github.com/zeux/volk) meta loader for vulkan API.
* [whereami](https://github.com/gpakosz/whereami) for executable location extracting.
* [zlib](https://github.com/madler/zlib) for files compression (required for assimp and freetype).

## Disclaimer

This is a personal learning project. It does not claim to be the ultimate guide to building real AAA game engines.
However, it can be useful for those who, like me at the time, want to learn something more than the basics and do
something on their own. This project accumulates ideas and knowledge from several books and can be a good starting point
for learning!

## Also

If you have any questions, feel free to contact me at `egororachyov@gmail.com`. If you have any ideas, questions, how to
make or improve something, please, do not hesitate to open new issue or pull-request inside this project. I will try to
respond as soon as possible to them.

## License

```
MIT License

Copyright (c) 2023 Egor Orachyov

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```