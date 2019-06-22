# Sets the minimum version of CMake required to build your native library.
# This ensures that a certain set of CMake features is available to
# your build.

cmake_minimum_required(VERSION 3.4.1)

# Specifies a library name, specifies whether the library is STATIC or
# SHARED, and provides relative paths to the source code. You can
# define multiple libraries by adding multiple add_library() commands,
# and CMake builds them for you. When you build your app, Gradle
# automatically packages shared libraries with your APK.

# Set the path to the Oboe directory.
set (OBOE_DIR ../../oboe)

# Add the Oboe library as a subdirectory in your project.
add_subdirectory (${OBOE_DIR} ./oboe)

# Specify the path to the Oboe header files.
include_directories (${OBOE_DIR}/include)

set (APP_DIR src/main/cpp)
file (GLOB_RECURSE APP_SOURCES
        ${APP_DIR}/jni-bridge.cpp
        ${APP_DIR}/AudioEngine.cpp
        ${APP_DIR}/Oscillator.cpp
        ${APP_DIR}/Mixer.cpp
        ${APP_DIR}/AudioNodes/AudioNode.cpp
        )

add_library(native-lib
        SHARED
        ${APP_SOURCES}
        )
include_directories(src/main/cpp/includes/)

target_link_libraries(native-lib android log oboe)
#target_compile_options(native-lib PRIVATE -Wall -Werror "$<$<CONFIG:RELEASE>:-Ofast>")