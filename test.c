#include <wiringPi.h>
#include <stdlib.h>
#include "map.h"
#include "move.h"
#define DISTANCE 360

unsigned int count=0, direction=0;
unsigned int currentRight, currentRFront, currentLeft, currentLFront;
/*dimension
Width: 16 cm
Length: 24 cm
ratio 2:3
*/


void init(){
    car.x=1;
    car.y=1;
    mode=0;
    car.direction = UP;
    car.turn = NONE;
    for(i=0;i<256;i++)
        for(j=0;j<256;j++)car.map[i][j]=UNKNOWN;
}

int main (void)
{
    wiringPiSetup();
    init();
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

    for(;;)
    {
        
        detect();
        //updatemap();
        //planpath();
        //move();
        if(car.turn!=NONE){}
        else{
            if (currentLFront > DISTANCE && currentRFront > DISTANCE)
            {
                car.map[car.x][car.y] |= UPFREE;   
            }
            else if(currentLFront <= DISTANCE && currentRFront <= DISTANCE)
            {
                if (currentLeft > DISTANCE && currentRight > DISTANCE)
                {
                        switch (car.turn)
                        {
                            case RIGHT:
                            turnLeft();                    
                            break;
                            case LEFT:
                            turnRight();
                            break;
                            default:
                            turnRight();
                        }
                }
                else if(currentLeft <= DISTANCE && currentRight <= DISTANCE)
                {
                    moveBackward();
                }
                else if (currentLeft <= DISTANCE && currentRight > DISTANCE)
                {
                    turnRight();
                }
                else
                {
                    turnLeft();
                }
            }
            else if (currentLFront <= DISTANCE && currentRFront > DISTANCE)
            {
                if (currentLeft > DISTANCE && currentRight > DISTANCE)
                {
                        switch (car.turn)
                        {
                            case RIGHT:
                            turnLeft();
                            break;
                            case LEFT:
                            turnRight();
                            break;
                            default:
                            turnRight();
                        }
                }
                else if(currentLeft <= DISTANCE && currentRight <= DISTANCE)
                {
                    moveBackward();   
                }
                else if (currentLeft <= DISTANCE && currentRight > DISTANCE)
                {
                    turnRight();
                }
                else
                {
                    turnLeft();
                }
            }
            else
            {
                if (currentLeft > DISTANCE && currentRight > DISTANCE)
                {
                        switch (car.turn)
                        {
                            case RIGHT:
                            turnLeft();
                            break;
                            case LEFT:
                            turnRight();
                            break;
                            default:
                            turnRight();
                        }
                }
                else if(currentLeft <= DISTANCE && currentRight <= DISTANCE)
                {
                    moveBackward();
                }
                else if (currentLeft <= DISTANCE && currentRight > DISTANCE)
                {
                    turnRight();
                }
                else
                {
                    turnLeft();
                }
            }
        }
        printf("distLFront: %d distRFront: %d distLeft: %d distRight: %d count zero: %d\n",distLFront,distRFront,distLeft,distRight,count);
        delay(100); 
    }
    return 0 ;
}
