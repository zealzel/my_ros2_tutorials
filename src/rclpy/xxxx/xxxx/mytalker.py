import rclpy
from rclpy.node import Node
from std_msgs.msg import String


class MyTalker(Node):
    def __init__(self):
        super().__init__("mytalker_node")
        self.pub_ = self.create_publisher(String, "mytopic", 10)
        self.timer = self.create_timer(0.5, self.timer_callback)
        self.counter = 0

    def timer_callback(self):
        msg = String()
        msg.data = "Hello, world!"
        self.pub_.publish(msg)
        self.get_logger().info("Publishing: '%s'" % msg.data)
        self.counter += 1


def main(args=None):
    print("main")
    rclpy.init(args=args)
    mytalker_node = MyTalker()
    try:
        rclpy.spin(mytalker_node)
    except KeyboardInterrupt:
        pass
    finally:
        mytalker_node.destroy_timer(mytalker_node.timer)
        mytalker_node.destroy_node()
        rclpy.shutdown()


if __name__ == "__main__":
    print("hello ros2")
    main()
