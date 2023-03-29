import os
from launch.launch_description import LaunchDescription
from launch_ros.actions import Node

from launch.actions import IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource
from ament_index_python.packages import get_package_share_directory


def generate_launch_description():
    launch_demo1 = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            os.path.join(
                get_package_share_directory("my_ros2_tutorials"),
                "launch",
                "demo1.launch.py",
            )
        )
    )
    ld = LaunchDescription(
        [
            launch_demo1,
        ]
    )
    return ld
