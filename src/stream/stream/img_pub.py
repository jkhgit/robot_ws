import cv2
from cv_bridge import CvBridge # convert ros2 msg < --- > opencv img
import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Image

class ImagePublisher(Node):

    def __init__(self):
        super().__init__('image_publisher')
        self.image_publisher = self.create_publisher(Image, 'frames', 10) # queue size: 10
        timer_period = 0.1  # default: 0.1s
        self.timer = self.create_timer(timer_period, self.timer_callback)
        self.cap = cv2.VideoCapture(0)
        self.cap.set(3,640)
        self.cap.set(4,640)
        # convert between ros and cv images
        self.br = CvBridge()

    def timer_callback(self):
        ret, frame = self.cap.read()

        if ret == True:
            self.image_publisher.publish(self.br.cv2_to_imgmsg(frame))
            self.get_logger().info('Publishing frames')

def main(args=None):
    rclpy.init(args=args)
    image_publisher = ImagePublisher()

    rclpy.spin(image_publisher)
    image_publisher.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
