from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='encryption_system',
            executable='publisher_node',
            name='publisher_node',
            output='screen',
        ),
        Node(
            package='encryption_system',
            executable='encryption_node',
            name='encryption_node',
            output='screen',
        ),
        Node(
            package='encryption_system',
            executable='decryption_node',
            name='decryption_node',
            output='screen',
        ),
    ])
