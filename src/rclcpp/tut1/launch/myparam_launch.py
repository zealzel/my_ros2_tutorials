import os
import launch
import launch_ros.actions

from ament_index_python.packages import get_package_share_directory


def generate_launch_description():
    param_file = os.path.join(
        get_package_share_directory("tut1"), "params/parameters1.yaml"
    )
    myparam_node = launch_ros.actions.Node(
        package="tut1",
        executable="myparam",
        name="myparam_node",
        output="screen",
        parameters=[
            param_file,
            {"name": "Marry"},
            {"is_ok": False},
        ],
    )
    return launch.LaunchDescription([myparam_node])
