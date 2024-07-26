import rclpy
from rclpy.node import Node
from my_interfaces.msg import Num, Sphere


class MyCustomSub(Node):
    def __init__(self):
        super().__init__("custom_sub_node")
        self.sub_ = self.create_subscription(Num, "my_int64", self.num_callback, 10)
        self.sub_sphere = self.create_subscription(
            Sphere, "my_sphere", self.sphere_callback, 10
        )

    def num_callback(self, msg):
        self.get_logger().info(f"Received num: {msg.num}")

    def sphere_callback(self, msg):
        self.get_logger().info(
            f"Received sphere: {msg.center.x}, {msg.center.y}, {msg.center.z}, {msg.radius}"
        )


def main():
    rclpy.init()
    my_custom_sub = MyCustomSub()
    rclpy.spin(my_custom_sub)
    rclpy.shutdown()


if __name__ == "__main__":
    main()
