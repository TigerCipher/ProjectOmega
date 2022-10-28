# ProjectOmega

A 3d OpenGL playground. Not sure what this will turn into yet.

### Project Setup
This project is structured with my current personal preferred setup for CLion on Windows.
+ All sources and headers are in `/src`
+ CLion sends compiled binaries, object files, intermediates, etc to `/cmake-build-CONFIG`
+ BUT, it is important to set the run configuration to use `/bin` as the working directory. This is where `dll` and `assets` are located

### Coding Conventions
+ Formatting is provided by my `.clang-format` file
+ Naming is subject to change, but currently everything belonging to ProjectOmega is `all_lower_case`