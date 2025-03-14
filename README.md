Custom [_toolbox_][toolboxqt-repo] containing multiple classes that can be useful when using [Qt framework][qt-official]

**Table of contents :**
- [1. Requirements](#1-requirements)
  - [1.1. C++ Standards](#11-c-standards)
  - [1.2. Dependencies](#12-dependencies)
- [2. How to build](#2-how-to-build)
- [3. How to use](#3-how-to-use)
  - [3.1. Available utilities](#31-available-utilities)
  - [3.2. Library version](#32-library-version)
- [4. Documentation](#4-documentation)
- [5. License](#5-license)

# 1. Requirements
## 1.1. C++ Standards

This library requires at least **C++ 11** standard

## 1.2. Dependencies

Below, list of required dependencies:

| Dependencies | VCPKG package | Comments |
|:-:|:-:|:-:|
| [Qt][qt-official] | / | Library built with **Qt framework** and compatible with series `5.15.x` and `6.x` |

> Dependency manager [VCPKG][vcpkg-tutorial] is not mandatory, this is only a note to be able to list needed packages

# 2. How to build

This library can be use as an _embedded library_ in a subdirectory of your project (like a _git submodule_ for example) :
1. In the **root** CMakeLists, add instructions :
```cmake
add_subdirectory(toolboxqt) # Or if library is put in a folder "deps" : add_subdirectory(deps/toolboxqt)
```

2. In the **application/library** CMakeLists, add instructions :
```cmake
# Link needed libraries
target_link_libraries(${PROJECT_NAME} PRIVATE toolboxqt)
```

# 3. How to use
## 3.1. Available utilities

Library is separated according to _Qt modules_, current modules and classes are (for each classes, more details can be found in their own documentation):
- **containers:**
  - _tbq::Array2D:_ Used to manage a 2-dimensional array
- **core:**
  - _tbq::CoreHelper:_ Contains static utilities that can't be associated with proper classes
  - _tbq::RichLink:_ Used to manage an URL with a custom display
  - _tbq::SettingsIni:_ Used to manage INI configuration file
- **qml:**
  - _tbq::QmlHelper:_ Class containing multiple helpful methods that can be used in QML
- **widgets:**
  - Buttons:
    - _tbq::BtnAbstractWordWrap:_ Virtual class which define an interface allowing to properly wrap text of a button
    - _tbq::BtnTool:_ Inherit from _QToolButton_ and _BtnAbstractWordWrap_
    - _tbq::BtnPush:_ Inherit from _QPushButton_ and _BtnAbstractWordWrap_. Also add _double-click_ event support.
  - _tbq::FileChooser:_ Used to choose a file from user-space
  - _tbq::LabelScl:_ Custom class which inherit from _QLabel_ class and properly scale image or animations to the label size.
  - _tbq::WidgetHelper:_ Group multiple methods that are simple enough to not have to create an inherited object

To use a class, simply use the proper include:
```cpp
#include "toolboxqt/widgets/labelscl.h"
```

All classes are defined inside namespace `tbq` (for _ToolBoxQt_).

## 3.2. Library version

In order to easily check at compilation time library version (to manage compatibility between multiple versions for example), macro `TOOLBOXQT_VERSION_ENCODE` (defined inside _toolboxqt_global.h_ file) can be used:
```cpp
#if TOOLBOXQT_VERSION >= TOOLBOXQT_VERSION_ENCODE(2,0,0)
    // Do stuff for version 2.0.0 or higher
#else
    // Do stuff for earlier versions
#endif
```

# 4. Documentation

All classes has been documented with [Doxygen][doxygen-official] utility and automatically generated at [online website documentation][gh-pages-doc]

To generate documentation locally, we can use:
```shell
# Run documentation generation
doxygen ./Doxyfile

# Under Windows OS, maybe doxygen is not added to the $PATH
"C:\Program Files\doxygen\bin\doxygen.exe" ./Doxyfile
```
> **Note:** You can also load the _Doxyfile_ into _Doxywizard_ (Doxygen GUI) and run generation.

# 5. License

This library is licensed under [MIT license][repo-license].

<!-- Links of this repository -->
[repo-license]: LICENSE.md

<!-- External links -->
[gh-pages-doc]: https://lecherch.github.io/ToolBoxQt/

[doxygen-official]: https://www.doxygen.nl/index.html
[gtest-repo]: https://github.com/google/googletest

[qt-official]: https://www.qt.io/
[qt-installer]: https://www.qt.io/download-qt-installer

[toolboxqt-repo]: https://github.com/legerch/ToolBoxQt

[vcpkg-tutorial]: https://github.com/legerch/develop-memo/tree/master/Toolchains/Build%20systems/VCPKG