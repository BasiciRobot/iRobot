#include <wiringPi.h>
#include <stdlib.h>
#include "map.h"
#include "move.h"
unsigned int count=0;
unsigned int currentLeft,currentRight,currentLLeft,currentRRight;

/*dimension
Width: 16 cm
Length: 24 cm
ratio 2:3
*/

void trigger(int pin)
{
    digitalWrite (pin, HIGH) ;
    delayMicroseconds (20) ;
    digitalWrite (pin,  LOW) ;
}

unsigned int pulseIn(int pin, unsigned int timeout)
{
    unsigned int wait=micros();
    for(;;)
    {
        if (micros() - wait >= timeout)
        {
            count++;
            return 0;
        }
        else if (digitalRead(pin) == HIGH)
        {
            unsigned int start=micros();
            for(;;)
            {
                if (digitalRead(pin) != HIGH)
                {
                    return micros()-start;
                }
            }
        }
    }
}

unsigned int distance(unsigned int t)
{
    return t*34/200;
}


int main (void)
{
    wiringPiSetup () ;
    pinMode (0, OUTPUT) ;//Ultrasonic 1
    pinMode (1, INPUT) ;
    pinMode (2, OUTPUT) ;//Ultrasonic 2
    pinMode (3, INPUT) ;
    pinMode (4, OUTPUT) ;//Ultrasonic 3
    pinMode (5, INPUT) ;
    pinMode (6, OUTPUT) ;//Ultrasonic 4
    pinMode (7, INPUT) ;

    pinMode (8,OUTPUT);//RightMotor 1
    pinMode (9,OUTPUT);
    pinMode (10,OUTPUT);//Left Motor 2
    pinMode (11,OUTPUT);
    pinMode (12,OUTPUT);//Right Motor 3
    pinMode (13,OUTPUT);
    pinMode (14,OUTPUT);//Left Motor 4
    pinMode (15,OUTPUT);
    move(NONE);

    for(;;)
    {
        unsigned int timeLeft,timeRight,timeLLeft,timeRRight;
        unsigned int distLeft,distRight,distLLeft,distRRight;

        trigger(0);
        timeLeft = pulseIn(1,500000);
        distLeft = distance(timeLeft);
        if(distLeft >0)
        {
            currentLeft=distLeft;
        }

        trigger(2);  
        timeRight = pulseIn(3,500000);
        distRight = distance(timeRight);
        if(distRRight >0)
        {
            currentRight=distRight;
        }

        trigger(4);
        timeLLeft = pulseIn(5,500000);
        distLLeft = distance(timeLLeft);
        if(distLLeft >0)
        {
            currentLLeft=distLLeft;
        }

        trigger(6);  
        timeRRight = pulseIn(7,500000);
        distRRight = distance(timeRRight);
        if(distRRight >0)
        {
            currentRRight=distRRight;
        }
        else()//need to deal with this situation

        if(currentLeft<=240 && currentRight <=240 && currentRFront <=240 && currentLFront <=240)
        {
            move(DOWN);
        }
        else if (currentLFront>240 && currentRFront >240)
        {
            move(UP);         
        }
        else if (currentLFront<=240 && currentRight >240)
        {
            move(RIGHT);
        }
        else if (currentRFront<=240 && currentLeft >240)
        {
            move(LEFT);
        }
        printf("distLeft: %d distRight: %d count zero: %d\n",distLeft,distRight,count);
        delay (1000);
    }
    return 0 ;
}
