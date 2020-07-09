cmake_minimum_required(VERSION 3.10)

set(PROJECT wxopenglcube)

project(${PROJECT} LANGUAGES CXX)

# Check a platform
if(WIN32)
	message("Platform: WIN32")
else()
	message("Unsupported platform yet")
	return()
endif()

# Set a default build type if none was specified by option -DCMAKE_BUILD_TYPE=Release
set(default_build_type "Release")

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
	message(STATUS "Setting build type to '${default_build_type}' as none was specified.")
	set(CMAKE_BUILD_TYPE "${default_build_type}" CACHE STRING "Choose the type of build." FORCE)
	set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release")
else()
	message("Configuration: ${CMAKE_BUILD_TYPE}")
endif()

set(SOURCES
	cube.cpp
	testglcanvas.cpp
	testglcontext.cpp
	)

add_executable(${PROJECT} ${SOURCES})

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
	set(WXLIBS wxmsw31ud_core wxbase31ud wxmsw31ud_gl)
	# target_compile_options(protopuddlepp PRIVATE -Wall -g)
	target_link_options(${PROJECT} PRIVATE -mwindows)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
	set(WXLIBS wxmsw31u_core wxbase31u wxmsw31u_gl)
	# target_compile_options(protopuddlepp PRIVATE -Wall)
	# -s - Remove all symbol table and relocation information from the executable
	target_link_options(${PROJECT} PRIVATE -s -mwindows)
else()
	message("Unknown configuration name ${CMAKE_BUILD_TYPE}. Stop")
	return()
endif()

# Enable c++17
target_compile_features(${PROJECT} PRIVATE cxx_std_17)

# Define wxWidgets' root directory
set(WXDIR "d:/Development/Cpp/MyExamples/wx/wx/")

# Additional directories that contain header files
target_include_directories(${PROJECT} PRIVATE ${WXDIR}/include)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
	target_include_directories(${PROJECT} PRIVATE ${WXDIR}/lib/mswud)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
	target_include_directories(${PROJECT} PRIVATE ${WXDIR}/lib/mswu)
else()
	message("Unknown configuration name ${CMAKE_BUILD_TYPE}. Stop")
	return()
endif()

# Additional directories that contain libraries
target_link_directories(${PROJECT} PRIVATE ${WXDIR}/lib)

target_link_libraries(${PROJECT} ${WXLIBS})
