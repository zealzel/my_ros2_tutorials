import os
from launch.launch_description import LaunchDescription
from launch.actions import IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource
from ament_index_python.packages import get_package_share_directory
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration


def generate_launch_description():
    width_arg = DeclareLaunchArgument("width", default_value="10")
    min_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            os.path.join(
                get_package_share_directory("tut1"),
                "launch",
                "min.launch.py",
            ),
        ),
        launch_arguments=[("width", LaunchConfiguration("width"))]
        # launch_arguments={"width": LaunchConfiguration("width")}.items(),
    )
    ld = LaunchDescription()
    ld.add_action(width_arg)
    ld.add_action(min_launch)
    return ld
