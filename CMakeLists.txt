cmake_minimum_required(VERSION 3.5.1)
project(LinuxForms)

# Add sources
file(GLOB SOURCES
    "${PROJECT_SOURCE_DIR}/src/*.cpp"
    "${PROJECT_SOURCE_DIR}/src/LinuxForms/*.cpp"
    "${PROJECT_SOURCE_DIR}/src/LinuxForms/Input/*.cpp"
    "${PROJECT_SOURCE_DIR}/src/LinuxForms/Utility/*.cpp"
)

# Use the package PkgConfig to detect GTK+ headers/library files
FIND_PACKAGE(PkgConfig REQUIRED)
PKG_CHECK_MODULES(GTK3 REQUIRED gtk+-3.0)
pkg_check_modules(GTK3_SOURCE_VIEW REQUIRED gtksourceview-3.0)

# Setup CMake to use GTK+, tell the compiler where to look for headers
# and to the linker where to look for libraries
INCLUDE_DIRECTORIES(${GTK3_INCLUDE_DIRS} ${GTK3_SOURCE_VIEW_INCLUDE_DIRS})
LINK_DIRECTORIES(${GTK3_LIBRARY_DIRS})

# Add other flags to the compiler
ADD_DEFINITIONS(${GTK3_CFLAGS_OTHER})

# Will add __FILENAME__ macros for all source files, which is the filename without full find_path
# Courtesy of SO
function(define_file_basename_for_sources targetname)
    get_target_property(source_files "${targetname}" SOURCES)
    foreach(sourcefile ${source_files})
        # Get source file's current list of compile definitions.
        get_property(defs SOURCE "${sourcefile}"
            PROPERTY COMPILE_DEFINITIONS)
        # Add the FILE_BASENAME=filename compile definition to the list.
        get_filename_component(basename "${sourcefile}" NAME)
        list(APPEND defs "__FILENAME__=\"${basename}\"")
        # Set the updated compile definitions on the source file.
        set_property(
            SOURCE "${sourcefile}"
            PROPERTY COMPILE_DEFINITIONS ${defs})
    endforeach()
endfunction()


# Specify include Directory
include_directories(
    "${PROJECT_SOURCE_DIR}/include"
    "${PROJECT_SOURCE_DIR}/include/LinuxForms"
    "${PROJECT_SOURCE_DIR}/include/LinuxForms/Input"
    "${PROJECT_SOURCE_DIR}/include/LinuxForms/Utility"
)




add_library(${PROJECT_NAME} SHARED ${SOURCES})

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 14)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)

define_file_basename_for_sources(${PROJECT_NAME})

install(TARGETS ${PROJECT_NAME} DESTINATION /usr/local/lib)
