cmake_minimum_required(VERSION 3.8)
project(custom_interface_usage)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(my_interfaces REQUIRED)

add_executable(my_pub src/pub.cpp)
ament_target_dependencies(my_pub rclcpp my_interfaces)

add_executable(my_sub src/sub.cpp)
ament_target_dependencies(my_sub rclcpp my_interfaces)

include_directories(
  include ${fitrobot_interfaces_INCLUDE_DIRS} # This line should typically be
                                              # unnecessary
)

install(TARGETS my_pub my_sub DESTINATION lib/${PROJECT_NAME})

ament_package()
