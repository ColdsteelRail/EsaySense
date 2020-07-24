# CMakeList.txt: 顶层 CMake 项目文件，在此处执行全局配置
# 并包含子项目。
#
cmake_minimum_required (VERSION 3.5)

project ("AlgorithmicIntegration")


if(WIN32)
	SET(CMAKE_BUILD_TYPE "Debug")
	#SET(CMAKE_BUILD_TYPE "Release")
	message(STATUS "dir" ${PROJECT_SOURCE_DIR})
	if(CMAKE_BUILD_TYPE STREQUAL "Debug")
		message(STATUS "debug")
		add_definitions(-D_Debug_)
		set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/Bin/win64/Debug)
		set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/Libs/win64/Debug)
	else()
		message(STATUS "release")
		set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/Bin/win64/Release)
		set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/Libs/win64/Release)
	endif()
else()
	add_compile_options(-std=c++11)
	SET(CMAKE_EXE_LINKER_FLAGS "-export-dynamic -Xlinker")
	link_directories(../libs) #包含库链接文件
	SET(CMAKE_BUILD_TYPE "Debug")
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/../Bin/)
endif()

# 包含子项目。
add_subdirectory ("AlgorithmicIntegration")
