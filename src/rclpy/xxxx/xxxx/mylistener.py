import rclpy
from rclpy.node import Node
from std_msgs.msg import String


class MyListener(Node):
    def __init__(self):
        super().__init__("mylistener_node")
        self.my_listener = self.create_subscription(
            String,
            "mytopic",
            self.listener_callback,
            10,
        )

    def listener_callback(self, msg):
        self.get_logger().info("I heard: '%s'" % msg.data)


def main(args=None):
    rclpy.init(args=args)
    mylistener = MyListener()
    rclpy.spin(mylistener)
    mylistener.destroy_node()
    rclpy.shutdown()


if __name__ == "__main__":
    main()
