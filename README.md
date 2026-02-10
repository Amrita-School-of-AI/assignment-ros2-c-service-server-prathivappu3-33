[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/feD56fij)
# Assignment: ROS2 C++ Service Server

**Course:** ROS2 Fundamentals  
**Build System:** ament_cmake

## Objective

The goal of this assignment is to verify your understanding of:

1. How to create a ROS2 Service Server.
2. How to handle service requests and send responses.
3. Using the `example_interfaces/srv/AddTwoInts` service type.

## Problem Statement

You must complete the provided skeleton code to create a ROS2 service server that adds two integers.

### Requirements

1. **Source Code (`src/add_two_ints_server.cpp`)**:
   - Implement a class `AddTwoIntsServer` that inherits from `rclcpp::Node`.
   - Initialize the node with the name `"add_two_ints_server"`.
   - Create a service named `"add_two_ints"` using `example_interfaces::srv::AddTwoInts`.
   - The service callback should:
     - Add the two integers from the request (`request->a` and `request->b`).
     - Store the result in `response->sum`.
     - Log the incoming request and the result using `RCLCPP_INFO`.

2. **Build Configuration (`CMakeLists.txt`)**:
   - Add an executable target named `add_two_ints_server`.
   - Link dependencies for `rclcpp` and `example_interfaces`.
   - Install the target.

3. **Package Metadata (`package.xml`)**:
   - Add the missing dependency tags.

## How to Test Locally

```bash
# Terminal 1: Build and run the server
colcon build --packages-select ros2_service_server
source install/setup.bash
ros2 run ros2_service_server add_two_ints_server

# Terminal 2: Call the service
ros2 service call /add_two_ints example_interfaces/srv/AddTwoInts "{a: 5, b: 3}"
```

#### Expected Output (in server terminal):

```shell
[INFO] [1700000000.123456789] [add_two_ints_server]: Incoming request: a=5, b=3
[INFO] [1700000000.123456789] [add_two_ints_server]: Sending response: sum=8
```

#### Expected Service Response:

```
sum: 8
```
