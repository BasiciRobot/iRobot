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

void detect(){

    unsigned int timeLFront,timeRFront,timeLeft,timeRight,temp,temp1,temp2,temp3;
    trigger(0);
    timeLFront = pulseIn(1,50000);
    temp = distance(timeLFront);
    if(temp >0)
     {
         currentLFront=temp;
     }

    trigger(2);
    timeRFront = pulseIn(3,50000);
    temp1 = distance(timeRFront);
     if(temp1 >0)
     {
         currentRFront=temp1;
     }

    trigger(4);
    timeLeft = pulseIn(5,50000);
    temp2 = distance(timeLeft);
    if(temp2 >0)
     {
         currentLeft=temp2;
     }

    trigger(6);
    timeRight = pulseIn(7,50000);
    temp3 = distance(timeRight);
    if(temp3 >0)
     {
         currentRight=temp3;
     }
}


