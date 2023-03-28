import launch
from launch.launch_description import LaunchDescription
from launch_ros.actions import Node


def generate_launch_description():
    ld = LaunchDescription(
        [
            Node(
                package="turtlesim",
                executable="turtlesim_node",
                output="screen",
                name="sim",
                namespace="AAA",
                remappings=[("/AAA/turtle1/cmd_vel", "/AAA/turtle1/my_cmd_vel")],
            )
        ]
    )
    return ld
