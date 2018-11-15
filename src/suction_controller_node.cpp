#include "suction_controller_node.hpp"

SuctionController::SuctionController() :
    private_nh("~"), 
    gpio_pin(17), 
    rasp_addr(""), 
    rasp_port("")
{
    this->set_port_srv = this->nh.advertiseService("control_suction", &SuctionController::setAirPort, this);
    this->private_nh.getParam("gpio_pin", this->gpio_pin);

    char* char_addr = this->rasp_addr.length() > 0 ? const_cast<char*>(this->rasp_addr.c_str()) : NULL;
    char* char_port = this->rasp_port.length() > 0 ? const_cast<char*>(this->rasp_port.c_str()) : NULL;
    ROS_INFO("IP address: %s, Port: %s\n", char_addr, char_port);
    this->pi = pigpio_start(char_addr, char_port);

    if (this->pi < 0)
    {
        ROS_ERROR("GPIO error");
        ros::shutdown();
    }

    set_mode(this->pi, this->gpio_pin, PI_OUTPUT);
}

SuctionController::~SuctionController() 
{
}

bool SuctionController::setAirPort(std_srvs::SetBool::Request &req, 
                                   std_srvs::SetBool::Response &res)
{
    try 
    {
        gpio_write(this->pi, this->gpio_pin, static_cast<int>(req.data));
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

void SuctionController::clear()
{
    set_mode(this->pi, this->gpio_pin, PI_INPUT);
    pigpio_stop(this->pi);
}

int main(int argc, char **argv) 
{
    ros::init(argc, argv, "suction_controller_node");

    SuctionController my_controller;

    ros::spin();

    return 0;
}