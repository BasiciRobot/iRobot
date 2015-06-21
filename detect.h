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

    unsigned int timeLFront,timeRFront,timeLeft,timeRight;
    trigger(0);
    timeLFront = pulseIn(1,50000);
    currentLFront = distance(timeLFront);

    trigger(2);
    timeRFront = pulseIn(3,50000);
    currentRFront = distance(timeRFront);

    trigger(4);
    timeLeft = pulseIn(5,50000);
    currentLeft = distance(timeLeft);

    trigger(6);
    timeRight = pulseIn(7,50000);
    currentRight = distance(timeRight);
}


