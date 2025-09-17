# CMakeLists file based on project template repository: https://github.com/legerch/projects-template
## Template file version: 2025-08-20

cmake_minimum_required(VERSION 3.20)

# Set project properties
set(PRJ_COMPANY_ID          legerch)
set(PRJ_COMPANY_NAME        "Leger Charlie")
set(PRJ_ID                  toolboxqt)
set(PRJ_READABLE_NAME       "ToolboxQt")
set(PRJ_VERSION_SEMANTIC    0.0.1)
set(PRJ_DESCRIPTION         "Custom toolbox containing multiple classes that can be useful when using Qt framework.")
set(PRJ_LICENSE             "MIT")
set(PRJ_COPYRIGHT           "Copyright (c) 2024-2025 ${PRJ_COMPANY_NAME} (${PRJ_LICENSE} License)")
set(PRJ_HOMEPAGE_URL        "https://github.com/legerch/ToolBoxQt")

set(PROJECT_NAME ${PRJ_ID})
set(PROJECT_VERSION_CPP_MIN 17)

# Set project configuration
## Generic properties
project(${PROJECT_NAME}
    LANGUAGES       CXX
    VERSION         "${PRJ_VERSION_SEMANTIC}"
    DESCRIPTION     ${PRJ_DESCRIPTION}
    HOMEPAGE_URL    ${PRJ_HOMEPAGE_URL}
)

## Qt specific properties
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# Define project options
# Example: option(TOOLBOXQT_BUILD_TESTS "Use to enable/disable build of unit-tests." ON)

# Manage global compiler options
## For MSVC: force to read source code as UTF-8 file (already default behaviour on GCC/Clang)
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

# Set C++ standard to use
if(DEFINED CMAKE_CXX_STANDARD)
    if(${CMAKE_CXX_STANDARD} LESS ${PROJECT_VERSION_CPP_MIN})
        message(FATAL_ERROR "Project ${PROJECT_NAME} require at least C++ standard ${PROJECT_VERSION_CPP_MIN}")
    endif()
endif()
set(CMAKE_CXX_STANDARD_REQUIRED ON)
message(STATUS "Project \"${PROJECT_NAME}\" compiled with C++ standard ${CMAKE_CXX_STANDARD}")

# Set needed packages
## Qt packages
set(PROJECT_QT_PACKAGES
    Core
    Widgets
)

find_package(QT NAMES Qt6 Qt5 COMPONENTS ${PROJECT_QT_PACKAGES} REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS ${PROJECT_QT_PACKAGES} REQUIRED)

list(TRANSFORM PROJECT_QT_PACKAGES PREPEND "Qt${QT_VERSION_MAJOR}::")

## Other library packages
### Example: find_package(nlohmann_json 3.11.3 REQUIRED)

# Defines useful path variables for easier CMake configuration
set(PROJECT_DIR_PUBLIC_HEADERS_ROOT "${PROJECT_SOURCE_DIR}/include")
set(PROJECT_DIR_PUBLIC_HEADERS      "${PROJECT_DIR_PUBLIC_HEADERS_ROOT}/${PROJECT_NAME}")
set(PROJECT_DIR_PRIV_SOURCES        "${PROJECT_SOURCE_DIR}/src")

set(PROJECT_FILE_GLOBAL             "${PROJECT_DIR_PUBLIC_HEADERS}/toolboxqt_global.h")

set(PROJECT_FILE_OS_METADATA_WINDOWS "${PROJECT_SOURCE_DIR}/metadata/windows/infos.rc")

# Manage library files
## Configure file project - File containing macros that can be used in project
configure_file("${PROJECT_FILE_GLOBAL}.in" "${PROJECT_FILE_GLOBAL}")
configure_file("${PROJECT_FILE_OS_METADATA_WINDOWS}.in" "${PROJECT_FILE_OS_METADATA_WINDOWS}")

## Set library compilation definitions
set(PROJECT_DEFS_PRIV
    "TOOLBOXQT_LIBRARY_BUILD"
)

set(PROJECT_DEFS_PUB

)

## Set library linking
### Linking dirs
set(PROJECT_LINKING_DIR

)

### Linking libs
set(PROJECT_LINKING_LIB
    ${PROJECT_QT_PACKAGES}
    # Example: nlohmann_json::nlohmann_json
)

## Set library files
### Public interface
set(PROJECT_HEADERS_PUBLIC
    toolboxtypes.h

    containers/array2d.h

    core/corehelper.h
    core/depinfos.h
    core/richlink.h
    core/settingsini.h

    qml/qmlhelper.h

    widgets/button.h
    widgets/dialogabout.h
    widgets/filechooser.h
    widgets/labelscl.h
    widgets/widgethelper.h

    widgets/table/tablewidgetitemlink.h
)

### Private
set(PROJECT_HEADERS_PRIVATE

)

set(PROJECT_SOURCES
    toolboxtypes.cpp

    core/corehelper.cpp
    core/depinfos.cpp
    core/richlink.cpp
    core/settingsini.cpp

    qml/qmlhelper.cpp

    widgets/button.cpp
    widgets/dialogabout.cpp
    widgets/filechooser.cpp
    widgets/labelscl.cpp
    widgets/widgethelper.cpp

    widgets/table/tablewidgetitemlink.cpp
)

set(PROJECT_RESSOURCES
    # No ressources to set
)

# Manage platform differences
## Refer to: https://cmake.org/cmake/help/latest/variable/CMAKE_SYSTEM_NAME.html
if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set(PROJECT_DEFS_PUB ${PROJECT_DEFS_PUB}
        "NOMINMAX"  # Needed because Windows define macros "min/max", better to not defined those and use "std::min/std::max" instead
        "WIN32_LEAN_AND_MEAN=1"
    )

    set(PROJECT_RESSOURCES ${PROJECT_RESSOURCES}
        ${PROJECT_FILE_OS_METADATA_WINDOWS}
    )
endif()

# Manage options
## Example: if(TOOLBOXQT_USE_CUSTOM_BEHAVIOUR)

### Prepend all files to proper directory
list(TRANSFORM PROJECT_HEADERS_PUBLIC PREPEND "${PROJECT_DIR_PUBLIC_HEADERS}/")
list(TRANSFORM PROJECT_HEADERS_PRIVATE PREPEND "${PROJECT_DIR_PRIV_SOURCES}/")
list(TRANSFORM PROJECT_SOURCES PREPEND "${PROJECT_DIR_PRIV_SOURCES}/")

set(PROJECT_FILES ${PROJECT_RESSOURCES} ${PROJECT_FILE_GLOBAL} ${PROJECT_HEADERS_PUBLIC} ${PROJECT_HEADERS_PRIVATE} ${PROJECT_SOURCES})

# Add files to the library
add_library(${PROJECT_NAME} SHARED ${PROJECT_FILES})

# Set version of library
set_target_properties(${PROJECT_NAME} PROPERTIES
                        VERSION ${PROJECT_VERSION}
                        SOVERSION ${PROJECT_VERSION_MAJOR})

# Link needed libraries
target_link_directories(${PROJECT_NAME} PUBLIC ${PROJECT_LINKING_DIR})
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC ${PROJECT_LINKING_LIB})

# Specify compiler options
target_compile_options(${PROJECT_NAME} PRIVATE
    $<$<CXX_COMPILER_ID:GNU>:-Wall -Wextra -Werror=return-type -Wshadow -Wlogical-op -Wduplicated-cond -Wduplicated-branches>
    $<$<CXX_COMPILER_ID:Clang>:-Wall -Wextra -Werror=return-type -Wshadow -Wlogical-op -Wduplicated-cond -Wduplicated-branches>
    $<$<CXX_COMPILER_ID:MSVC>:/W4 /wd4251>
)

# Compile needed definitions
## Library related
target_compile_definitions(${PROJECT_NAME} PUBLIC ${PROJECT_DEFS_PUB})
target_compile_definitions(${PROJECT_NAME} PRIVATE ${PROJECT_DEFS_PRIV})

# Specify include directories
target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${PROJECT_DIR_PUBLIC_HEADERS_ROOT}  # Only expose public headers
    PRIVATE
        ${PROJECT_DIR_PRIV_SOURCES}         # Internal headers, only for internal use
)

# Do we need to build tests ?
if(TOOLBOXQT_BUILD_TESTS)
    add_subdirectory(tests)
endif()
