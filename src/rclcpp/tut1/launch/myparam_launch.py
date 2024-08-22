import os
import launch
from launch_ros.actions import Node

from launch.substitutions import LaunchConfiguration
from launch.actions import DeclareLaunchArgument
from nav2_common.launch import RewrittenYaml
from launch_ros.descriptions import ParameterFile


from ament_index_python.packages import get_package_share_directory


def generate_launch_description():
    default_params_file = os.path.join(
        get_package_share_directory("tut1"), "params/parameters1.yaml"
    )
    namespace_arg = DeclareLaunchArgument(
        "namespace", default_value="", description="ROS2 node namespace"
    )
    params_file_arg = DeclareLaunchArgument(
        "params_file", default_value=default_params_file, description="params file"
    )

    param_substitutions = {
        "name": "Holy",
        "x_pos": "100",
        "y_pos": "200",
    }

    configured_params = ParameterFile(
        param_file=RewrittenYaml(
            source_file=LaunchConfiguration("params_file"),
            root_key=LaunchConfiguration("namespace"),
            param_rewrites=param_substitutions,
            # param_rewrites={},
            convert_types=True,
        ),
        allow_substs=True,
    )

    myparam_node = Node(
        package="tut1",
        executable="myparam",
        name="myparam_node",
        namespace=LaunchConfiguration("namespace"),
        output="screen",
        parameters=[
            configured_params,
            {"name": "Marry"},
            {"z_pos": 123},
            {"is_ok": False},
        ],
    )
    return launch.LaunchDescription(
        [
            #
            params_file_arg,
            namespace_arg,
            # configured_params,
            myparam_node,
        ]
    )
