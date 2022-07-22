#include <chrono>
#include <cstdio>
#include <iostream>
#include <memory>
#include <string>

#include "geometry_msgs/msg/point.hpp"
#include "rclcpp/rclcpp.hpp"

class Publisher_: public rclcpp::Node
{
  public:
	Publisher_()
	: Node("key")
	{
		initialize();
	}

	~Publisher_()
	{
	}

  private:
	//function
	void initialize()
	{
		auto qos = rclcpp::QoS(rclcpp::KeepLast(10));
		pub_ = this->create_publisher<geometry_msgs::msg::Point>(
				topic_, qos);
		timer_ = this->create_wall_timer(
				std::chrono::milliseconds(static_cast<int>(100)),
				std::bind(&Publisher_::get_key_and_publish, this));
	}

	void get_key_and_publish()
	{
		auto pos = geometry_msgs::msg::Point();
		char input;

		pos.x = 0;
		pos.y = 0;

		std::cin >> input;

		switch (input) {
			case 'a':
				pos.x = 5; // -90
				break;
			case 'd':
				pos.x = 24; // +90
				break;
			case 's':
				pos.y = 5; // -90
				break;
			case 'w':
				pos.y = 24; // 90
				break;
			default:
				pos.x = 5;
				pos.y = 5;
				break;
		}

		pub_->publish(pos);
	}

	//vars
	std::string topic_ = "/control/position";

	rclcpp::Publisher<geometry_msgs::msg::Point>::SharedPtr pub_;
	rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char* argv[])
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<Publisher_>();
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}

