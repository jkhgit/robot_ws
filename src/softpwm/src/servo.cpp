#include <functional>
#include <memory>
#include <string>
#include <stdlib.h>

#include <wiringPi.h>
#include <softPwm.h>

#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/point.hpp"

#define MOTOR_1 8
#define MOTOR_2 9

class Subscriber_ : public rclcpp::Node
{
  public:
	Subscriber_()
	: Node("motor")
	{
		initialize();
	}

	~Subscriber_()
	{
	}

  private:
	//functions
	void initialize()
	{
		auto qos = rclcpp::QoS(rclcpp::KeepLast(10));
		auto callback =
			[this](const geometry_msgs::msg::Point::SharedPtr pos) {
				motor_write(pos);
			};

		// wiringPi set
		wiringPiSetup();
		pinMode(MOTOR_1, OUTPUT);
		pinMode(MOTOR_2, OUTPUT);
		softPwmCreate(MOTOR_1,0,200);
		softPwmCreate(MOTOR_2,0,200);

		// subscriber set
		sub_ = create_subscription<geometry_msgs::msg::Point>(topic_, qos, callback);
	}

	void motor_write(const geometry_msgs::msg::Point::SharedPtr pos)
	{
		softPwmWrite(MOTOR_1,pos->x);
		softPwmWrite(MOTOR_2,pos->y);
	}

	//vars
	std::string topic_ = "/control/position";

	rclcpp::Subscription<geometry_msgs::msg::Point>::SharedPtr sub_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<Subscriber_>();
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}

