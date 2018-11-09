#!/usr/bin/env python
#-*- coding:utf-8 -*-

import pigpio
import rospy
from std_srvs.srv import SetBool

pi = pigpio.pi()

def SetPort(req):
    print "%s"%req.data
    pi.write(17,req.data)
    return [True, "suction"]

def main():
    rospy.init_node('suction_controller', anonymous = False)
    pi.set_mode(17, pigpio.OUTPUT)
    rospy.Service('control_suction', SetBool, SetPort)
    rospy.spin()

if __name__ == '__main__':
    main()
