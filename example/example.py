#!/usr/bin/python
# -*- coding: utf-8 -*-

""" Alexandre Coninx
    ISIR CNRS/UPMC
    04/06/2019
""" 

# Port of the Fastsim example


from pyfastsim import *
import sys
import time

if(len(sys.argv) < 2):
	print("This program cannot run: you need to provide a XML file (e.g.,%s worlds/example.xml)" % sys.argv[0])
	sys.exit(1)


settings = Settings(sys.argv[1])

env_map = settings.map()
robot = settings.robot()


d = Display(env_map, robot)

for i in range(10000):
	d.update()
	pos = robot.get_pos()
	print("Step %d robot pos: x = %f    y = %f    theta = %f" % (i, pos.x(), pos.y(), pos.theta()))
	robot.move(1.0, 1.1, env_map)
	time.sleep(0.001)





