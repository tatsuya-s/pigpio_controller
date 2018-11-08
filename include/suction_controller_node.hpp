#ifndef SUCTION_CONTROLLER_NODE_HPP
#define SUCTION_CONTROLLER_NODE_HPP

#include <ros/ros.h>
#include <std_srvs/SetBool.h>
#include <wiringPi.h>

class SuctionController 
{
    public:
        SuctionController();
        ~SuctionController();
        bool setAirPort(std_srvs::SetBool::Request &req, 
                        std_srvs::SetBool::Response &res);

    private:
        ros::NodeHandle nh, private_nh;
        ros::ServiceServer set_port_srv;
        int gpio_pin;
};

#endif // SUCTION_CONTROLLER_NODE_HPP