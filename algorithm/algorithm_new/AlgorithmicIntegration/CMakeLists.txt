# CMakeList.txt: AlgorithmicIntegration 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)


include_directories(../Libs/include)
# LibUtils
aux_source_directory(Utils/ UtilsSRCS)
add_library(LibUtils STATIC ${UtilsSRCS})

SET(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
SET(CMAKE_INSTALL_RPATH "\${ORIGIN}/")
#主程序
aux_source_directory(. MainSRCS)
add_executable (AlgorithmicIntegration ${MainSRCS})


if(WIN32)
	# LibJson
	aux_source_directory(Json/ JsonSRCS)
	add_library(LibJson STATIC ${JsonSRCS})

	message(STATUS "conda:" $ENV{CONDA_PREFIX})
	include_directories("$ENV{CONDA_PREFIX}/envs/tensorflow/include" /
						"$ENV{CONDA_PREFIX}/envs/tensorflow/Lib/site-packages/numpy/core/include/numpy")
	LINK_DIRECTORIES("$ENV{CONDA_PREFIX}/envs/tensorflow/libs" / 
					 "$ENV{CONDA_PREFIX}/envs/tensorflow/Lib" /
					 ${PROJECT_SOURCE_DIR}/Libs/win64)
	target_link_libraries(AlgorithmicIntegration ${PROJECT_SOURCE_DIR}/win64/NetDeviceSDK.lib 
												 ${PROJECT_SOURCE_DIR}/win64/transter.lib /
						                         ${PROJECT_SOURCE_DIR}/win64/LibRabbitMqSDK.lib /
												 ${PROJECT_SOURCE_DIR}/win64/hiredis.lib)
	target_link_libraries(AlgorithmicIntegration LibUtils LibJson)
	if(CMAKE_BUILD_TYPE STREQUAL "Debug")
		target_link_libraries(AlgorithmicIntegration $ENV{CONDA_PREFIX}/envs/tensorflow/libs/python37_d.lib)
	else()
		target_link_libraries(AlgorithmicIntegration $ENV{CONDA_PREFIX}/envs/tensorflow/libs/python37.lib)
	endif()
else()

	#find_package(OpenCV 3.4 EXACT)
	set(CONDA_PREFIX /root/miniconda3)
	set(CUR_LIB_DIR ${PROJECT_SOURCE_DIR}/AlgorithmicIntegration/lib)

	message(STATUS "PROJECT_SOURCE_DIR:" ${PROJECT_SOURCE_DIR})
	message(STATUS "conda:path" ${CONDA_PREFIX})
	include_directories(
		${CONDA_PREFIX}/include/python3.6m/ 
		${CONDA_PREFIX}/lib/python3.6/site-packages/numpy/core/include/numpy/
		${PROJECT_SOURCE_DIR}/AlgorithmicIntegration/include/
		${PROJECT_SOURCE_DIR}/../include
		${OpenCV_INCLUDE_DIR}/
	)
	LINK_DIRECTORIES(
		${CONDA_PREFIX}/lib/
		${CONDA_PREFIX}/python3.6
		/usr/local/lib/
	)
	
	target_link_libraries(AlgorithmicIntegration ${PROJECT_SOURCE_DIR}/../libs/libjsoncpp.a 
												 ${PROJECT_SOURCE_DIR}/../libs/libhiredis.a
												 ${CONDA_PREFIX}/lib/libpython3.6m.a
												 )
	target_link_libraries(AlgorithmicIntegration ${PROJECT_SOURCE_DIR}/../libs/libtranster.so
												 ${PROJECT_SOURCE_DIR}/../libs/libNetDeviceSDK.so
												 #${OpenCV_LIBS}
												 #${CUR_LIB_DIR}/libcjson.so
												 #${CUR_LIB_DIR}/libSmokeDetectAlgorithm.so
												 #${CUR_LIB_DIR}/libLiquidLevelDetect.so
												 )
											


	target_link_libraries(AlgorithmicIntegration LibUtils)
	target_link_libraries(AlgorithmicIntegration ${CMAKE_DL_LIBS})
	find_package(Threads)
	target_link_libraries(AlgorithmicIntegration ${CMAKE_THREAD_LIBS_INIT} -luuid -lutil -lrt -ldl -lpthread)
endif()
