import sys
import rclpy
from rclpy.node import Node
from example_interfaces.srv import AddTwoInts


class MyServiceClient(Node):
    def __init__(self):
        super().__init__("my_service_client_node")
        self.cli = self.create_client(AddTwoInts, "add_two_ints")
        while not self.cli.wait_for_service(timeout_sec=1.0):
            self.get_logger().info("service not available, waiting again...")
        self.req = AddTwoInts.Request()

    def send_request(self, a, b):
        self.req.a = a
        self.req.b = b
        return self.cli.call_async(self.req)


def main():
    rclpy.init()
    my_client = MyServiceClient()
    a = sys.argv[1]
    b = sys.argv[2]
    print("a: ", a, "b: ", b)
    future = my_client.send_request(int(sys.argv[1]), int(sys.argv[2]))
    rclpy.spin_until_future_complete(my_client, future)
    response = future.result()
    my_client.get_logger().info(
        f"Result of addition: for {sys.argv[1]} + {sys.argv[2]} = {response.sum}"
    )
    my_client.destroy_node()
    rclpy.shutdown()


if __name__ == "__main__":
    main()
