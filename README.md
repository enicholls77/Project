# Simple Idle Miner

## Build Instructions
Run the following commands:
### Windows (x86):
- Install [CMake](https://cmake.org/download/)
- Install [Conan](https://docs.conan.io/en/latest/installation.html)
- set up conan:

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

### Linux (might work on MacOS as well) (x86) (WIP):
- Install [Conan](https://docs.conan.io/en/latest/installation.html)
- Follow the [Getting Started](https://docs.conan.io/en/latest/getting_started.html) guide

After setting up conan, be sure to add the following to the profile that you created (at `~/.conan/profiles/default`):
```
[conf]    
tools.system.package_manager:mode=install    
tools.system.package_manager:sudo=True
```
This will allow conan to install system dependencies automatically

- Build:

`./build.sh`

### MacOS (M1 - ARM) (WIP):
