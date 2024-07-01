import os
from launch.launch_description import LaunchDescription
from launch.actions import IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource
from ament_index_python.packages import get_package_share_directory


def generate_launch_description():
    min_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            os.path.join(
                get_package_share_directory("tut1"),
                "launch",
                "min.launch.py",
            )
        )
    )
    ld = LaunchDescription()
    ld.add_action(min_launch)
    return ld

