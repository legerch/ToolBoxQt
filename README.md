Custom [_toolbox_][repo-home] containing multiple classes that can be useful when using [Qt framework][qt-official]

> [!TIP]
> Latest development/pull requests will be committed into `main` branch.  
> Each stable release have their dedicated branch:
> - `1.0.x`: branch `dev/1.0`
> - `1.1.x`: branch `dev/1.1`
> - etc...

**Table of contents :**
- [1. Library details](#1-library-details)
  - [1.1. Features](#11-features)
- [2. Requirements](#2-requirements)
  - [2.1. C++ Standards](#21-c-standards)
  - [2.2. Dependencies](#22-dependencies)
- [3. How to build](#3-how-to-build)
  - [3.1. CMake Usage](#31-cmake-usage)
  - [3.2. CMake options](#32-cmake-options)
- [4. How to use](#4-how-to-use)
  - [4.1. Usage](#41-usage)
  - [4.2. Library version](#42-library-version)
    - [4.2.1. Compatibility](#421-compatibility)
    - [4.2.2. Compilation time](#422-compilation-time)
    - [4.2.3. Runtime](#423-runtime)
- [5. Documentation](#5-documentation)
- [6. License](#6-license)

# 1. Library details
## 1.1. Features

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
  - Table:
    - _tbq::TableWidgetItemLink:_ Qt widget item allowing to store link informations
  - _tbq::DialogAbout:_ Allow to easily create an "about" dialog window
  - _tbq::FileChooser:_ Used to choose a file from user-space
  - _tbq::LabelScl:_ Custom class which inherit from _QLabel_ class and properly scale image or animations to the label size.
  - _tbq::WidgetHelper:_ Group multiple methods that are simple enough to not have to create an inherited object

# 2. Requirements
## 2.1. C++ Standards

This library requires at least **C++ 17** standard

## 2.2. Dependencies

Below, list of required dependencies:

| Dependencies | VCPKG package | Comments |
|:-:|:-:|:-:|
| [Qt][qt-official] | / | Compatible with **Qt6.x**<br>Compatible with **Qt5.15.x** |

> [!NOTE]
> Dependency manager [VCPKG][vcpkg-tutorial] is not mandatory, this is only a note to be able to list needed packages

# 3. How to build
## 3.1. CMake Usage

This library can be use as an _embedded library_ in a subdirectory of your project (like a _git submodule_ for example) :
1. In the **root** CMakeLists, add instructions :
```cmake
add_subdirectory(toolboxqt) # Or if library is put in a folder "dependencies" : add_subdirectory(dependencies/toolboxqt)
```

2. In the **application/library** CMakeLists, add instructions :
```cmake
# Link needed libraries
target_link_libraries(${PROJECT_NAME} PRIVATE toolboxqt)
```

## 3.2. CMake options

This library provide some **CMake** build options:
- _No CMake options currently available_

# 4. How to use
## 4.1. Usage

To use a class, simply use the proper include:
```cpp
#include "toolboxqt/widgets/labelscl.h"
```

All classes are defined inside namespace `tbq` (for _ToolBoxQt_).

## 4.2. Library version
### 4.2.1. Compatibility

This library follow [semantic versioning][semver-home] for **API**. **ABI** is not preserved between versions, so software using this library will have to recompile it to update the version of the library.

### 4.2.2. Compilation time

In order to easily check at compilation time library version (to manage compatibility between multiple versions for example), macro `TOOLBOXQT_VERSION_ENCODE` (defined inside _toolboxqt_global.h_ file) can be used:
```cpp
#if TOOLBOXQT_VERSION >= TOOLBOXQT_VERSION_ENCODE(2,0,0)
    // Do stuff for version 2.0.0 or higher
#else
    // Do stuff for earlier versions
#endif
```

### 4.2.3. Runtime

Since library header used during final application build could differ from the actual library version, it is recommended to use the method:
```cpp
#include "toolboxqt/toolboxtypes.h"

const QVersionNumber libSemver = tbq::getLibraryVersion();
```

# 5. Documentation

All classes/methods has been documented with [Doxygen][doxygen-official] utility and automatically generated at [online website documentation][repo-doc-web].

> [!NOTE]
> This repository contains two kinds of documentation:
> - **Public API:** Available via [online website documentation][repo-doc-web] or locally via Doxyfile `docs/fragments/Doxyfile-public-api.in`
> - **Internal:** Available locally only via `docs/fragments/Doxyfile-internal.in`

To generate documentation locally, we can use:
```shell
doxygen ./docs/fragments/Doxyfile-name
```
> [!TIP]
> You can also load the _Doxyfile_ into _Doxywizard_ (Doxygen GUI) and run generation.

# 6. License

This library is licensed under [MIT license][repo-license-url].

<!-- Anchor of this page -->
[anchor-platforms]: #12-supported-platforms
[anchor-cmake-opts]: #32-cmake-options

<!-- Links of this repository -->
[repo-home]: https://github.com/legerch/ToolBoxQt
[repo-doc-web]: https://lecherch.github.io/ToolBoxQt/
[repo-license]: LICENSE.md
[repo-license-url]: https://github.com/legerch/ToolBoxQt/LICENSE.md

<!-- External links -->
[doxygen-official]: https://www.doxygen.nl/index.html

[gtest-repo]: https://github.com/google/googletest

[qt-official]: https://www.qt.io/

[vcpkg-tutorial]: https://github.com/legerch/develop-memo/tree/master/Toolchains/Build%20systems/VCPKG

[semver-home]: https://semver.org
[pimpl-doc-cpp]: https://en.cppreference.com/w/cpp/language/pimpl
[pimpl-doc-qt]: https://wiki.qt.io/D-Pointer