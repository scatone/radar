cmake_minimum_required(VERSION 3.10)
project(ProcessPicture) # Rename the project to a valid name without spaces
find_package(OpenCV REQUIRED)

set(CMAKE_BUILD_TYPE "Debug")
set(set(CMAKE_CXX_STANDARD 17)
        set(CMAKE_CXX_FLAGS "-std=c++11"))
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -O0  -Wall -fopenmp")
set(CUDA_GEN_CODE "-gencode=arch=compute_86,code=sm_86")
set(CUDA_NVCC_FLAGS "${CUDA_NVCC_FLAGS}  -std=c++17 -O0 -Xcompiler -fPIC -g -w ${CUDA_GEN_CODE}")
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -Ofast -Wfatal-errors -D_MWAITXINTRIN_H_INCLUDED")

include_directories(
        ${OpenCV_INCLUDE_DIRS}
        /usr/include
)

### Define output target ###
add_executable(${PROJECT_NAME} main.cpp) # Rename the target to a valid name without paths

target_include_directories(${PROJECT_NAME} PUBLIC ${OpenCV_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})
