cmake_minimum_required(VERSION 2.8.3)
project(suction_controller)

set(CMAKE_CXX_FLAGS "-std=c++11")

include(pigpio/util/Findpigpio.cmake)

find_package(
  catkin REQUIRED COMPONENTS
    roscpp
    rospy
    std_srvs
)

find_package(Threads REQUIRED)
find_package(pigpio QUIET)
if(NOT pigpio_FOUND)
  add_subdirectory(pigpio)
  set(pigpio_INCLUDE_DIR pigpio)
  set(pigpiod_if2_LIBRARY pigpiod_if2)
endif()

catkin_package(
  INCLUDE_DIRS
    include
  LIBRARIES
    suction_controller
  CATKIN_DEPENDS
    roscpp
    rospy
    std_srvs
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
  ${pigpio_INCLUDE_DIR}
)

add_executable(suction_controller_node src/suction_controller_node.cpp)
target_link_libraries(suction_controller_node ${catkin_LIBRARIES} ${pigpiod_if2_LIBRARY} ${CMAKE_THREAD_LIBS_INIT})