import os
from launch.launch_description import DeclareLaunchArgument, LaunchDescription
from launch_ros.actions import Node
from launch.actions import IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource
from ament_index_python.packages import get_package_share_directory

def generate_launch_description():
    node_name_arg = DeclareLaunchArgument("node_name", default_value="my_talker")

    min_demo1 = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            os.path.join(
                get_package_share_directory("tut1"),
                "launch",
                "min.launch.py",
            )
        )
    )
    ld = LaunchDescription()
    ld.add_action(node_name_arg)
    ld.add_action(min_demo1)
    return ld

