project(3d_recon_test_tool)
cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 11)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

MESSAGE("Build type: " ${CMAKE_BUILD_TYPE})
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}  -Wall   -O3")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall   -O3")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -march=native")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -march=native")


find_package(Eigen3 REQUIRED)
find_package(OpenCV 3 REQUIRED)
find_package(Pangolin REQUIRED)
find_package(GeographicLib REQUIRED)

include_directories(
        ${EIGEN3_INCLUDE_DIRS}
        ${Pangolin_INCLUDE_DIRS}
        ${OpenCV_INCLUDE_DIRS}
        include
        src
)

set(SRC_FILES
        src/parameters.cpp
        src/Data.cpp
        src/Draw.cpp
        src/tools.cpp
        src/UDPServer.cpp
        src/coordinate_transform.cpp)

# 接收深度图
add_executable(receive apps/receive.cpp ${SRC_FILES} )
target_link_libraries(receive
        ${OpenCV_LIBS}
        ${GeographicLib_LIBRARIES}
        ${Pangolin_LIBRARIES})

add_executable(sendImuInfo apps/sendImuInfo.cpp src/UDPClient.cpp src/parameters.cpp)
target_link_libraries(sendImuInfo
        ${OpenCV_LIBS})

add_executable(test1 apps/test1.cpp)