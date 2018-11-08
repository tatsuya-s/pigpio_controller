#include "suction_controller_node.hpp"

SuctionController::SuctionController() :
    private_nh("~"), 
    gpio_pin(0)
{
    this->set_port_srv = this->nh.advertiseService("control_suction", &SuctionController::setAirPort, this);
    this->private_nh.getParam("gpio_pin", this->gpio_pin);

    if (wiringPiSetup() == -1)
    {
        ROS_ERROR("GPIO error");
        ros::shutdown();
    }

    pinMode(this->gpio_pin, OUTPUT);
}

SuctionController::~SuctionController() 
{
}

bool SuctionController::setAirPort(std_srvs::SetBool::Request &req, 
                                   std_srvs::SetBool::Response &res)
{
    try 
    {
        digitalWrite(this->gpio_pin, static_cast<int>(req.data));
        res.success = true;
    }
    catch(...)
    {
        ROS_ERROR("Couldn't set port");
        ros::Duration(1.0).sleep();
        res.success = false;
    }

    ROS_INFO_STREAM("Air port request : " << req.data ? "true" : "false");
    ROS_INFO_STREAM("Air port response: " << res.success ? "true" : "false");

    return true;
}

int main(int argc, char **argv) 
{
    ros::init(argc, argv, "suction_controller_node");

    SuctionController my_controller;

    ros::spin();

    return 0;
}