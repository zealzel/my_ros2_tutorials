cmake_minimum_required(VERSION 3.8)
project(tut1)

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
find_package(rclcpp_components REQUIRED)

add_executable(mytalker src/mytalker.cpp)
ament_target_dependencies(mytalker rclcpp std_msgs)

add_executable(mylistener src/mylistener.cpp)
ament_target_dependencies(mylistener rclcpp std_msgs)

add_executable(mytalker_with_parameter src/mytalker_with_parameter.cpp)
ament_target_dependencies(mytalker_with_parameter rclcpp std_msgs)

add_executable(myparam src/myparam.cpp)
ament_target_dependencies(myparam rclcpp std_msgs)

add_library(mytalker_comp SHARED src/mytalkerComp.cpp)
ament_target_dependencies(mytalker_comp rclcpp rclcpp_components std_msgs)
rclcpp_components_register_nodes(mytalker_comp "MyTalkerComp")

add_library(mylistener_comp SHARED src/mylistenerComp.cpp)
ament_target_dependencies(mylistener_comp rclcpp rclcpp_components std_msgs)
rclcpp_components_register_nodes(mylistener_comp "MyListenerComp")

install(DIRECTORY launch params DESTINATION share/${PROJECT_NAME})

install(TARGETS mytalker mylistener mytalker_with_parameter myparam
        DESTINATION lib/${PROJECT_NAME}
)

ament_export_targets(export_mytalker_comp)
install(TARGETS mytalker_comp
        EXPORT export_mytalker_comp
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin
)

ament_export_targets(export_mylistener_comp)
install(TARGETS mylistener_comp
        EXPORT export_mylistener_comp
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin
)

ament_package()
