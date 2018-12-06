#!/usr/bin/env python
# -*- coding: utf-8 -*-

import pigpio
import rospy
from std_srvs.srv import SetBool

class Controller():
    def __init__(self):
        self.pin = 17
        self.pi = pigpio.pi()
        self.pi.set_mode(self.pin, pigpio.OUTPUT)

        rospy.Service('control_pin', SetBool, self.callback)

    def callback(self, req):
        self.pi.write(self.pin, req.data)
        return [True, "%s"%req.data]

def main():
    rospy.init_node('pigpio_controller', anonymous = False)
    pigpio_controller = Controller()

    rospy.spin()

if __name__ == '__main__':
    main()