# ProjectOmega

A 3d OpenGL playground. Not sure what this will turn into yet.

### Project Setup
This project is structured with my current personal preferred setup for CLion on Windows.
+ All sources and headers are in `/src`
+ CLion sends compiled binaries, object files, intermediates, etc to `/cmake-build-CONFIG`
+ BUT, it is important to set the run configuration to use `/bin` as the working directory. This is where `dll` and `assets` are located
+ SDL2 and spdlog are both built with MSVC. At some point I will change CMakeLists.txt to be platform independent
+ Update: I've figured out how to set the working directory for Visual Studio when using CMake, so now binaries and such go to `/out/build/<config>` instead
+ Ignored from git is `CMakeSettings.json` (used by Visual Studio) because I have cmake installed at different locations on different PCs
+ But for the sake of it, on my daily driver PC here are the settings used:

```
{
    "configurations": [
        {
            "name": "x64-Debug",
            "generator": "Ninja",
            "configurationType": "Debug",
            "inheritEnvironments": [ "msvc_x64_x64" ],
            "buildRoot": "${projectDir}\\out\\build\\${name}",
            "installRoot": "${projectDir}\\out\\install\\${name}",
            "cmakeCommandArgs": "",
            "buildCommandArgs": "",
            "ctestCommandArgs": "",
            "cmakeExecutable": "C:/Program Files/CMake/bin/cmake.exe"
        }
    ]
}
```

### Coding Conventions
+ Formatting is provided by my `.clang-format` file
+ Naming is subject to change, but currently everything belonging to ProjectOmega is `all_lower_case`