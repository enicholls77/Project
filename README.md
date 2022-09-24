# Simple Idle Miner

## Build Instructions
Run the following commands:
### Windows (x86):
- Install [CMake](https://cmake.org/download/)
- Install [Conan](https://docs.conan.io/en/latest/installation.html)
- Set up Conan:

`conan profile new default --detect`\
This should generate a new profile at `C:/Users/{username}/.conan/profiles/default`\
Here's what mine looks like:
```
[settings]
os=Windows
os_build=Windows
arch=x86_64
arch_build=x86_64
compiler=Visual Studio
compiler.version=17
build_type=Release
[options]
[build_requires]
[env]
```

- Set env. variables:

`CMAKE_GENERATOR="Desired Generator"`, e.g. `CMAKE_GENERATOR="Visual Studio 17 2022"`

**NOTE:** The generator that should be used will depend on the `compiler` and `compiler.version` setting in your conan profile.
If you plan to use Visual Studio 17 2022, like I do, make sure to [install it](https://learn.microsoft.com/en-us/visualstudio/releases/2022/release-notes)

- Build:

`./build.bat`

### Linux/MacOS (x86) (WIP):
`./build.sh`
