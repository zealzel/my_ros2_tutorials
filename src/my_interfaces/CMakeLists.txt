cmake_minimum_required(VERSION 3.8)
project(my_interfaces)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(rosidl_default_generators REQUIRED)

rosidl_generate_interfaces(
  ${PROJECT_NAME}
  "msg/Num.msg"
  "msg/Sphere.msg"
  "srv/AddThreeInts.srv"
  "msg/AprilTagDetectionArray.msg"
  "msg/AprilTagDetection.msg"
  DEPENDENCIES
  builtin_interfaces
  std_msgs
  geometry_msgs
)

ament_package()
