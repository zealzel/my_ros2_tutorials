cmake_minimum_required(VERSION 3.8)
project(my_ros2_tutorials)

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)

add_executable(mytalker src/mytalker.cpp)
ament_target_dependencies(mytalker rclcpp std_msgs)

add_executable(mylistener src/mylistener.cpp)
ament_target_dependencies(mylistener rclcpp std_msgs)

add_executable(mytalker_with_parameter src/mytalker_with_parameter.cpp)
ament_target_dependencies(mytalker_with_parameter rclcpp std_msgs)

install(DIRECTORY launch
  DESTINATION share/${PROJECT_NAME}
)

install(TARGETS
  mytalker mylistener mytalker_with_parameter
  DESTINATION lib/${PROJECT_NAME})

ament_package()
