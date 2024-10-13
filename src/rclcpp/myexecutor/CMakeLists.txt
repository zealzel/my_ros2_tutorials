cmake_minimum_required(VERSION 3.8)
project(myexecutor)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)

add_executable(simple_node src/simple_node.cpp)
ament_target_dependencies(simple_node rclcpp std_msgs)

add_executable(simple_node_single_executor src/simple_node_single_executor.cpp)
ament_target_dependencies(simple_node_single_executor rclcpp std_msgs)

install(TARGETS simple_node_single_executor simple_node
        DESTINATION lib/${PROJECT_NAME}
)

ament_package()
