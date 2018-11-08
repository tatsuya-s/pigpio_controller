cmake_minimum_required(VERSION 2.8.3)
project(suction_controller)

cmake_policy(SET CMP0046 OLD)
add_compile_options(-std=c++11)

find_package(
  catkin REQUIRED COMPONENTS
    roscpp
    rospy
    std_srvs
#    message_generation
#    actionlib_msgs
)

find_library(
  WIRINGPI_LIBRARY wiringPi 
    /home/pi/libraries/wiringPi
)

## Generate services in the 'srv' folder
# add_service_files(
#   FILES
#   Service1.srv
#   Service2.srv
# )

## Generate actions in the 'action' folder
# add_action_files(
#   FILES
#   Action1.action
#   Action2.action
# )

#generate_messages(
#  DEPENDENCIES
#    std_srvs
#    actionlib_msgs
#)

catkin_package(
  INCLUDE_DIRS
    include
  LIBRARIES
    suction_controller
  CATKIN_DEPENDS
    roscpp
    rospy
    std_srvs
#    message_runtime
#    actionlib_msgs
#  DEPENDS system_lib
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

add_executable(suction_controller_node src/suction_controller_node.cpp)
add_dependencies(suction_controller_node ${catkin_EXPORTED_TARGETS} wiringPi)
target_link_libraries(suction_controller_node ${catkin_LIBRARIES} ${WIRINGPI_LIBRARY})