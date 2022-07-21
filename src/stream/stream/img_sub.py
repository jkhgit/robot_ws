import cv2
from cv_bridge import CvBridge # convert ros2 msg < --- > opencv img
import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Image
import sys

class ImageSubscriber(Node):

    def __init__(self):
        super().__init__('image_subscriber')
        self.image_subscriber = self.create_subscription(Image, 'frames', self.listener_callback, 10) # queue size: 10
        self.image_subscriber # to avoid unuse Warning.
        # convert between ros and cv images
        self.br = CvBridge()

    def listener_callback(self, data):
        self.get_logger().info('Receving frames')
        current_frame = self.br.imgmsg_to_cv2(data)

        # display
        cv2.imshow("Live", current_frame)

        if cv2.waitKey(1) & 0xFF == ord('q'):
            cv2.destroyAllWindows()
            sys.exit(0)

def main(args=None):
    rclpy.init(args=args)
    image_subscriber = ImageSubscriber()

    rclpy.spin(image_subscriber)
    image_subscriber.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
