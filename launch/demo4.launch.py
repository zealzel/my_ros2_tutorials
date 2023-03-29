from launch.launch_description import DeclareLaunchArgument, LaunchDescription
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node


def generate_launch_description():
    """
    Minimal demenstration of how DecalreLaunchArgument and LaunchConfiguration work.
    ex:
    ros2 launch my_ros2_tutorials demo4.launch.py node_name:=changed_talker
    """
    node_name_arg = DeclareLaunchArgument("node_name", default_value="my_talker")
    node_name = LaunchConfiguration("node_name")
    talker_node = Node(
        package="demo_nodes_cpp",
        executable="talker",
        name=node_name,
    )
    ld = LaunchDescription()
    ld.add_action(node_name_arg)
    ld.add_action(talker_node)
    return ld
