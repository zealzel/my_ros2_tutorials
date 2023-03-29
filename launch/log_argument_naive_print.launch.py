from launch.launch_description import DeclareLaunchArgument, LaunchDescription
from launch.substitutions import LaunchConfiguration
from launch.actions import LogInfo


def generate_launch_description():
    width_arg = DeclareLaunchArgument("width", default_value="20")
    print("width", LaunchConfiguration("width"))
    ld = LaunchDescription()
    ld.add_action(width_arg)
    return ld

