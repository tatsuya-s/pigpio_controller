#ifndef PIGPIO_CONTROLLER_NODE_HPP
#define PIGPIO_CONTROLLER_NODE_HPP

#include <ros/ros.h>
#include <std_srvs/SetBool.h>
#include "pigpiod_if2.h"

class GPIOController 
{
    public:
        GPIOController();
        ~GPIOController();
        bool setPin(std_srvs::SetBool::Request &req, 
                    std_srvs::SetBool::Response &res);
        void clear();

    private:
        ros::NodeHandle nh, private_nh;
        ros::ServiceServer set_pin_srv;
        int pi;
        int gpio_pin;
        std::string rasp_addr;
        std::string rasp_port;
};

#endif // PIGPIO_CONTROLLER_NODE_HPP