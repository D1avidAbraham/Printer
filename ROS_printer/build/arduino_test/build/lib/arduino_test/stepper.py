import rclpy
from rclpy.node import Node
import serial
from std_msgs.msg import Int32

class StepperController(Node):
    def __init__(self):
        super().__init__('stepper_controller')
        self.subscription = self.create_subscription(
            Int32, 'stepper_speed', self.listener_callback, 10)
        self.serial_conn = serial.Serial('/dev/ttyUSB0', 115200, timeout=1)

    def listener_callback(self, msg):
        speed_str = str(msg.data) + '\n'
        self.serial_conn.write(speed_str.encode('utf-8'))

def main(args=None):
    rclpy.init(args=args)
    node = StepperController()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()