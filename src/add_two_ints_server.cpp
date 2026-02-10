#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/srv/add_two_ints.hpp"

using AddTwoInts = example_interfaces::srv::AddTwoInts;

class AddTwoIntsServer : public rclcpp::Node
{
public:
    AddTwoIntsServer() : Node("add_two_ints_server")
    {
        service_ = this->create_service<AddTwoInts>(
            "add_two_ints",
            std::bind(&AddTwoIntsServer::handle_service, this,
                      std::placeholders::_1, std::placeholders::_2)
        );
    }

private:
    void handle_service(
        const std::shared_ptr<AddTwoInts::Request> request,
        std::shared_ptr<AddTwoInts::Response> response)
    {
        response->sum = request->a + request->b;

        RCLCPP_INFO(this->get_logger(),
                    "Incoming request: a=%ld, b=%ld",
                    request->a, request->b);

        RCLCPP_INFO(this->get_logger(),
                    "Sending response: sum=%ld",
                    response->sum);
    }

    rclcpp::Service<AddTwoInts>::SharedPtr service_;
};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<AddTwoIntsServer>());
    rclcpp::shutdown();
    return 0;
}
