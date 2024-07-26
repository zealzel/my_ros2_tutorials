import rclpy
from rclpy.node import Node
from example_interfaces.srv import AddTwoInts


class MyService(Node):
    def __init__(self):
        super().__init__("myservice_node")
        self.srv = self.create_service(AddTwoInts, "add_two_ints", self.callback)

    def callback(self, request, response):
        response.sum = request.a + request.b
        self.get_logger().info(f"Incoming request\na: {request.a}, b: {request.b}")
        self.get_logger().info(f"Sending response: {response.sum}")
        return response


def main(args=None):
    rclpy.init()
    myservice_node = MyService()
    rclpy.spin(myservice_node)
    rclpy.shutdown()


if __name__ == "__main__":
    main()
