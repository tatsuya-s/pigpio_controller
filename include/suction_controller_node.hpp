#ifndef SUCTION_CONTROLLER_NODE_HPP
#define SUCTION_CONTROLLER_NODE_HPP

#include <ros/ros.h>
#include <std_srvs/SetBool.h>
#include "pigpiod_if2.h"

class SuctionController 
{
    public:
        SuctionController();
        ~SuctionController();
        bool setAirPort(std_srvs::SetBool::Request &req, 
                        std_srvs::SetBool::Response &res);
        void clear();

    private:
        ros::NodeHandle nh, private_nh;
        ros::ServiceServer set_port_srv;
        int pi;
        int gpio_pin;
        std::string rasp_addr;
        std::string rasp_port;
};

#endif // SUCTION_CONTROLLER_NODE_HPP