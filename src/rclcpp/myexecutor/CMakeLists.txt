cmake_minimum_required(VERSION 3.8)
project(myexecutor)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(std_srvs REQUIRED)

add_executable(simple_node_raw src/simple_node_raw.cpp)
ament_target_dependencies(simple_node_raw rclcpp std_msgs std_srvs)

add_executable(simple_node_class src/simple_node_class.cpp)
ament_target_dependencies(simple_node_class rclcpp std_msgs std_srvs)

add_executable(simple_node_single_executor src/simple_node_single_executor.cpp)
ament_target_dependencies(simple_node_single_executor rclcpp std_msgs std_srvs)

add_executable(
  simple_node_multiple_executor src/simple_node_multiple_executor.cpp
)
ament_target_dependencies(
  simple_node_multiple_executor rclcpp std_msgs std_srvs
)

install(TARGETS simple_node_single_executor simple_node_raw simple_node_class
                simple_node_multiple_executor DESTINATION lib/${PROJECT_NAME}
)

ament_package()
