import rclpy
from rclpy.node import Node
from std_msgs.msg import Int32
import serial

class StepperCommander(Node):
    def __init__(self):
        super().__init__('stepper_commander')
        self.declare_parameter('port', '/dev/ttyACM0')
        self.declare_parameter('baud', 115200)

        port = self.get_parameter('port').get_parameter_value().string_value
        baud = self.get_parameter('baud').get_parameter_value().integer_value
        self.ser = serial.Serial(port, baud, timeout=0.1)

        # two topics: /stepper1/steps and /stepper2/steps
        self.create_subscription(Int32, 'stepper1/steps', self.cb1, 10)
        self.create_subscription(Int32, 'stepper2/steps', self.cb2, 10)

    def send(self, motor_id: int, steps: int):
        cmd = f"{motor_id}:{steps}\n"
        self.ser.write(cmd.encode())
        self.get_logger().info(f"→ {cmd.strip()}")

    def cb1(self, msg: Int32):
        self.send(1, msg.data)

    def cb2(self, msg: Int32):
        self.send(2, msg.data)

def main(args=None):
    rclpy.init(args=args)
    node = StepperCommander()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()