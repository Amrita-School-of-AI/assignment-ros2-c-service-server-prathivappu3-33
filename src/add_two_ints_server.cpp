#include <memory>
#include <chrono>

#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/srv/add_two_ints.hpp"

using namespace std::chrono_literals;

class AddTwoIntsClient : public rclcpp::Node
{
public:
  AddTwoIntsClient()
  : Node("add_two_ints_client")
  {
    client_ = this->create_client<example_interfaces::srv::AddTwoInts>("add_two_ints");
  }

  rclcpp::Client<example_interfaces::srv::AddTwoInts>::SharedFuture
  send_request(int64_t a, int64_t b)
  {
    // Wait for service with 1-second timeout
    while (!client_->wait_for_service(1s)) {
      if (!rclcpp::ok()) {
        RCLCPP_ERROR(this->get_logger(), "Interrupted while waiting for the service.");
        return nullptr;
      }
      RCLCPP_INFO(this->get_logger(), "Waiting for service to appear...");
    }

    RCLCPP_INFO(this->get_logger(), "Service available, sending request...");

    auto request = std::make_shared<example_interfaces::srv::AddTwoInts::Request>();
    request->a = a;
    request->b = b;

    return client_->async_send_request(request);
  }

private:
  rclcpp::Client<example_interfaces::srv::AddTwoInts>::SharedPtr client_;
};

int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);

  auto node = std::make_shared<AddTwoIntsClient>();

  auto future = node->send_request(41, 1);

  // Wait for response
  if (rclcpp::spin_until_future_complete(node, future) ==
      rclcpp::FutureReturnCode::SUCCESS)
  {
    auto response = future.get();
    RCLCPP_INFO(
      node->get_logger(),
      "Result: %ld + %ld = %ld",
      response->sum - 1,
      1L,
      response->sum
    );
  }
  else
  {
    RCLCPP_ERROR(node->get_logger(), "Failed to call service add_two_ints");
  }

  rclcpp::shutdown();
  return 0;
}