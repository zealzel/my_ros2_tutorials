from launch_ros.actions import Node, ComposableNodeContainer
from launch_ros.descriptions import ComposableNode
from launch.launch_description import (
    DeclareLaunchArgument,
    LaunchDescription,
)
from launch.conditions import IfCondition, UnlessCondition
from launch.substitutions import LaunchConfiguration


def generate_launch_description():
    use_sim_time_arg = DeclareLaunchArgument(
        "use_sim_time",
        default_value="false",
        description="Use simulation (Gazebo) clock if true",
    )
    use_composition_arg = DeclareLaunchArgument(
        "use_composition",
        default_value="false",
        description="Use composition if true",
    )

    talker_node = Node(
        package="tut1",
        executable="mytalker",
        name="mytalker",
        condition=UnlessCondition(LaunchConfiguration("use_composition")),
    )
    listener_node = Node(
        package="tut1",
        executable="mylistener",
        name="mylistener",
        condition=UnlessCondition(LaunchConfiguration("use_composition")),
    )
    container = ComposableNodeContainer(
        name="my_container",
        namespace="",
        package="rclcpp_components",
        executable="component_container",
        composable_node_descriptions=[
            ComposableNode(
                package="tut1",
                plugin="MyTalkerComp",
                name="talker",
                extra_arguments=[{"use_intra_process_comms": True}],
            ),
            ComposableNode(
                package="tut1",
                plugin="MyListenerComp",
                name="listener",
                extra_arguments=[{"use_intra_process_comms": True}],
            ),
        ],
        condition=IfCondition(LaunchConfiguration("use_composition")),
    )

    ld = LaunchDescription()
    ld.add_action(use_sim_time_arg)
    ld.add_action(use_composition_arg)
    ld.add_action(talker_node)
    ld.add_action(listener_node)
    ld.add_action(container)

    return ld
