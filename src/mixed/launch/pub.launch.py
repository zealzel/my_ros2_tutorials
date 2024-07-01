import launch
from launch.launch_description import LaunchDescription
from launch_ros.actions import Node


def generate_launch_description():
    package_name = "mixed"
    print("DSFSDFDFDSFD")
    print("AAA")
    ld = LaunchDescription(
        [
            Node(
                package=package_name,
                executable="pnode.py",
                output="screen",
            )
        ]
    )
    return ld
