import random
import rclpy
from rclpy.node import Node
from geometry_msgs.msg import Point
from my_interfaces.msg import Num, Sphere
# from my_interfaces.srv import AddThreeInts


def random_float(a, b):
    while True:
        result = random.uniform(a, b)
        if a < result < b:
            return result


class CustomPub(Node):
    def __init__(self):
        super().__init__("custom_pub_node")
        self.create_timer(1, self.timer_num_callback)
        self.create_timer(0.1, self.timer_sphere_callback)
        self.pub_ = self.create_publisher(Num, "my_int64", 10)
        self.pub_sphere = self.create_publisher(Sphere, "my_sphere", 10)
        self.counter = 0

    def timer_num_callback(self):
        self.get_logger().info("Hello, num!,")
        msg = Num()
        msg.num = self.counter
        self.pub_.publish(msg)
        self.counter += 1

    def timer_sphere_callback(self):
        self.get_logger().info("Hello, sphere!,")
        msg_sphere = Sphere()
        msg_sphere.center.x = random_float(0.1, 0.3)
        msg_sphere.center.y = random_float(0.1, 0.3)
        msg_sphere.center.z = random_float(0.1, 0.3)
        msg_sphere.radius = random_float(0.055, 0.06)
        self.pub_sphere.publish(msg_sphere)


def main():
    rclpy.init()
    my_custom_pub = CustomPub()
    rclpy.spin(my_custom_pub)
    my_custom_pub.destroy_node()
    rclpy.shutdown()


if __name__ == "__main__":
    main()
