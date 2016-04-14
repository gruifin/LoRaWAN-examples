//This is an example for the MMA7660 1.5 G Accelerometer
//Download the library on https://github.com/Seeed-Studio/Accelerometer_MMA7660/archive/master.zip

#include <Wire.h>
#include "MMA7660.h"

MMA7660 accelemeter;

void setup(){
    accelemeter.init();
}

void loop(){
    
    float ax,ay,az;
	accelemeter.getXYZ(&x,&y,&z);
    
    accelemeter.getAcceleration(&ax,&ay,&az);
}