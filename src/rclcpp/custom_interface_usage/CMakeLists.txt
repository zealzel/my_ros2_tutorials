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


install(TARGETS
  my_pub
  DESTINATION lib/${PROJECT_NAME}
)


ament_package()
