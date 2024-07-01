from launch.launch_description import DeclareLaunchArgument, LaunchDescription
from launch.substitutions import LaunchConfiguration
from launch.actions import LogInfo


def generate_launch_description():
    width_arg = DeclareLaunchArgument("width", default_value="20")
    ld = LaunchDescription(
        [
            width_arg,
            LogInfo(msg=LaunchConfiguration("width")),
            LogInfo(msg=["width: ", LaunchConfiguration("width")]),
        ]
    )
    return ld

