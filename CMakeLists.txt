cmake_minimum_required(VERSION 3.22.1)

project(QEMU_Manager LANGUAGES C ASM)

find_package(PkgConfig REQUIRED)

pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
pkg_check_modules(GLIB REQUIRED glib-2.0)
pkg_check_modules(GIO REQUIRED gio-2.0)


set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(MGR_TARGET "qmgr" CACHE STRING "")




add_executable(${MGR_TARGET})

target_include_directories(${MGR_TARGET} PRIVATE
    ${GTK3_INCLUDE_DIRS}
    ${GLIB_INCLUDE_DIRS}
    ${GIO_INCLUDE_PATHS}
    ${CMAKE_SOURCE_DIR}/include
)

target_compile_options(${MGR_TARGET} PRIVATE
    -Wall
    -Wextra
    -Wno-unused-parameter
    -Wno-unused-variable
    -Wno-unused-function
    -Wno-unused-but-set-variable
    ${GLIB_CFLAGS_OTHER}
    ${GIO_CFLAGS_OTHER}
)

target_link_directories(${MGR_TARGET} PRIVATE
    ${GTK3_LIBRARY_DIRS}
)

target_link_libraries(${MGR_TARGET} PRIVATE
    json-c
    ${GLIB_LIBBRARIES}
    ${GIO_LIBRARIES}
    ${GTK3_LIBRARIES}
)

add_subdirectory(src)