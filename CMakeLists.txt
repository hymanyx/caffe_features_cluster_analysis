cmake_minimum_required(VERSION 2.8)
project(caffe_features_cluster_analysis)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -O3")

set(OpenCV_DIR ${CMAKE_SOURCE_DIR}/opencv-2.4.11/share/OpenCV)
set(OpenCV_STATIC ON)
set(OpenCV_SHARED OFF)
find_package( OpenCV REQUIRED )

include_directories(
        ${CMAKE_SOURCE_DIR}/include/google
        ${CMAKE_SOURCE_DIR}/include/
        ${CMAKE_SOURCE_DIR}/opencv-2.4.11/include
        /usr/include
        /usr/local/cuda/include
)

link_directories(
        ${CMAKE_SOURCE_DIR}/lib/google/protobuf
        ${CMAKE_SOURCE_DIR}/lib/google/gflags-2.1.2
        ${CMAKE_SOURCE_DIR}/lib/google/glog-0.3.4
        ${CMAKE_SOURCE_DIR}/lib/caffe
        ${CMAKE_SOURCE_DIR}/opencv-2.4.11/lib
)

set(SOURCE_FILES src/main.cpp src/mat_util.h)

add_executable(caffe_features_cluster_analysis ${SOURCE_FILES})

target_link_libraries(
        caffe_features_cluster_analysis
        libcaffe-nv.a
        libglog.a libgflags.a libprotobuf.a
        liblmdb.a
        libleveldb.a libpthread.so
        libsnappy.a
        # opecv
        ${OpenCV_LIBS}
)
