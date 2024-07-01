cmake_minimum_required(VERSION 3.8)
project(mixed)

# if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
#     add_compile_options(-Wall -Wextra -Wpedantic)
# endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(std_msgs REQUIRED)
find_package(rclcpp REQUIRED)
find_package(ament_cmake_python REQUIRED)
find_package(rclpy REQUIRED)

add_executable(cppnode src/cppnode.cpp)
ament_target_dependencies(cppnode rclcpp std_msgs geometry_msgs)

install(DIRECTORY launch DESTINATION share/${PROJECT_NAME})

install(TARGETS
  cppnode
  DESTINATION lib/${PROJECT_NAME}
)

install(PROGRAMS
  scripts/pnode.py
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()

