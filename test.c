#include <stdio.h>
unsigned int count=0, direction=0;
unsigned int currentRight, currentRFront, currentLeft, currentLFront;
unsigned int distLFront,distRFront,distLeft,distRight; 

#include <wiringPi.h>
#include <stdlib.h>
#include "map.h"
#include "move.h"
#include "planpath.h"
#include "detect.h"
#include "updatemap.h"
#define DISTANCE 360

/*dimension
Width: 16 cm
Length: 24 cm
ratio 2:3
*/


void init(){

    wiringPiSetup();
    pinMode (0, OUTPUT) ;//Ultrasonic 1
    pinMode (1, INPUT) ;
    pinMode (2, OUTPUT) ;//Ultrasonic 2
    pinMode (3, INPUT) ;
    pinMode (4, OUTPUT) ;//Ultrasonic 3
    pinMode (5, INPUT) ;
    pinMode (6, OUTPUT) ;//Ultrasonic 4
    pinMode (7, INPUT) ;

    pinMode (8,OUTPUT);//Motor 1
    pinMode (9,OUTPUT);
    pinMode (10,OUTPUT);//Motor 2
    pinMode (11,OUTPUT);
    pinMode (12,OUTPUT);//Motor 3
    pinMode (13,OUTPUT);
    pinMode (14,OUTPUT);//Motor 4
    pinMode (15,OUTPUT);
    stop();
    car.x=1;
    car.y=1;
    car.mode=0;
    car.direction = UP;
    car.turn = NONE;
    int i,j;
    for(i=0;i<256;i++)
        for(j=0;j<256;j++)car.map[i][j]=UNKNOWN;
}

int main (void)
{
    init();
    static unsigned char times = 0;
    for(;;)
    {
        unsigned int start = millis();
        detect();
        if(times == 0){
            updatemap();
            planpath();
            move();
        }
        else if(times == 4) times = 0;
        else times++;
        printf("distRight: %4d distRFront: %4d distLeft: %4d distLFront: %4d count zero: %4d\n",currentRight, currentRFront, currentLeft, currentLFront,count);
    }
    return 0 ;
}
