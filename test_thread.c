#include <wiringPi.h>
#include <pthread.h>

#define DISTANCE 360
#define NOTURN 0
#define AFTERRIGHT 1
#define AFTERLEFT 2

unsigned int count=0,direction=0;
unsigned int currentLeft,currentRight,currentLLeft,currentRRight;

struct data
{
   int pin_trig;
   int pin_echo;
   int value;
   unsigned int timeout;
   unsigned int *sensor;
};

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

unsigned int pulseIn(int pin, int value, unsigned int timeout)
{
   unsigned int wait=micros();
   for(;;)
   {
       if (micros() - wait >= timeout)
       {
            count++;
            return 0;
       }
       if (digitalRead(pin)==value)
       {
          unsigned int start=micros();
          for(;;)
          {
               if (digitalRead(pin)!=value)
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

void *SensorTask (void *d)
{
     unsigned int time, dist;
     struct data *in;
     in=(struct data *)d;
     trigger(in->pin_trig);
     time = pulseIn(in->pin_echo,in->value,in->timeout);
     dist = distance(time);
     if(dist >0)
     {
        *( in->sensor)=dist;
     }
     return 0;
}

void forward(int in1,int in2,int in3,int in4,int in5,int in6,int in7,int in8)
{
    digitalWrite(in1,HIGH);
    digitalWrite(in2,LOW);
    digitalWrite(in3,HIGH);
    digitalWrite(in4,LOW);
    digitalWrite(in5,HIGH);
    digitalWrite(in6,LOW);
    digitalWrite(in7,HIGH);
    digitalWrite(in8,LOW);
}

void backward(int in1,int in2,int in3,int in4,int in5,int in6,int in7,int in8)
{
    digitalWrite(in1,LOW);
    digitalWrite(in2,HIGH);
    digitalWrite(in3,LOW);
    digitalWrite(in4,HIGH);
    digitalWrite(in5,LOW);
    digitalWrite(in6,HIGH);
    digitalWrite(in7,LOW);
    digitalWrite(in8,HIGH);
}

void turnRight(int in1,int in2,int in3,int in4,int in5,int in6,int in7,int in8)
{
    digitalWrite(in1,LOW);
    digitalWrite(in2,HIGH);
    digitalWrite(in3,HIGH);
    digitalWrite(in4,LOW);
    digitalWrite(in5,HIGH);
    digitalWrite(in6,LOW);
    digitalWrite(in7,HIGH);
    digitalWrite(in8,LOW);
}

void turnLeft(int in1,int in2,int in3,int in4,int in5,int in6,int in7,int in8)
{
    digitalWrite(in1,HIGH);
    digitalWrite(in2,LOW);
    digitalWrite(in3,LOW);
    digitalWrite(in4,HIGH);
    digitalWrite(in5,HIGH);
    digitalWrite(in6,LOW);
    digitalWrite(in7,HIGH);
    digitalWrite(in8,LOW);
}

void stop(int in1,int in2,int in3,int in4,int in5,int in6,int in7,int in8)
{
    digitalWrite(in1,LOW);
    digitalWrite(in2,LOW);
    digitalWrite(in3,LOW);
    digitalWrite(in4,LOW);
    digitalWrite(in5,LOW);
    digitalWrite(in6,LOW);
    digitalWrite(in7,LOW);
    digitalWrite(in8,LOW);
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

  pinMode (8,OUTPUT);//Motor 1
  pinMode (9,OUTPUT);
  pinMode (10,OUTPUT);//Motor 2
  pinMode (11,OUTPUT);
  pinMode (12,OUTPUT);//Motor 3
  pinMode (13,OUTPUT);
  pinMode (14,OUTPUT);//Motor 4
  pinMode (15,OUTPUT);
  stop(8,9,10,11,12,13,14,15);

  for(;;)
  {
    
     struct data L={0,1, HIGH,20000, &currentLeft};
     struct data R={2,3, HIGH,20000, &currentRight};
     struct data LL={4,5, HIGH,20000, &currentLLeft};
     struct data RR={6,7, HIGH,20000, &currentRRight};

     pthread_t threadL, threadR, threadLL, threadRR;
     pthread_create (&threadL,NULL,&SensorTask,&L);
     pthread_create (&threadR,NULL,&SensorTask,&R);
     pthread_create (&threadLL,NULL,&SensorTask,&LL);
     pthread_create (&threadRR,NULL,&SensorTask ,&RR);

     pthread_join(threadL,NULL);
     pthread_join(threadR,NULL);
     pthread_join(threadLL,NULL);
     pthread_join(threadRR,NULL);

     if (currentLeft>DISTANCE && currentRight >DISTANCE)
     {
        if (currentLLeft>DISTANCE && currentRRight >DISTANCE)
        {
           forward(8,9,10,11,12,13,14,15);
        }
        else if(currentLLeft<=DISTANCE && currentRRight <=DISTANCE)
        {
            forward(8,9,10,11,12,13,14,15);
        }
        else if (currentLLeft<=DISTANCE && currentRRight >DISTANCE)
        {
            turnRight(8,9,10,11,12,13,14,15);
            direction=AFTERRIGHT;
        }
        else
        {
            turnLeft(8,9,10,11,12,13,14,15);
            direction=AFTERLEFT;
        }
     }
     else if(currentLeft<=DISTANCE && currentRight <=DISTANCE)
     {
        if (currentLLeft>DISTANCE && currentRRight >DISTANCE)
        {
             switch (direction)
             {
                 case AFTERRIGHT:
                    turnLeft(8,9,10,11,12,13,14,15);
                    break;
                 case AFTERLEFT:
                    turnRight(8,9,10,11,12,13,14,15);
                    break;
                 default:
                    turnRight(8,9,10,11,12,13,14,15);                    
             }
        }
        else if(currentLLeft<=DISTANCE && currentRRight <=DISTANCE)
        {
            backward(8,9,10,11,12,13,14,15);
        }
        else if (currentLLeft<=DISTANCE && currentRRight >DISTANCE)
        {
            turnRight(8,9,10,11,12,13,14,15);
        }
        else
        {
            turnLeft(8,9,10,11,12,13,14,15);
        }
     }
     else if (currentLeft<=DISTANCE && currentRight >DISTANCE)
     {
        if (currentLLeft>DISTANCE && currentRRight >DISTANCE)
        {
             switch (direction)
             {
                 case AFTERRIGHT:
                    turnLeft(8,9,10,11,12,13,14,15);
                    break;
                 case AFTERLEFT:
                    turnRight(8,9,10,11,12,13,14,15);
                    break;
                 default:
                    turnRight(8,9,10,11,12,13,14,15);                    
             }
        }
        else if(currentLLeft<=DISTANCE && currentRRight <=DISTANCE)
        {
            backward(8,9,10,11,12,13,14,15);
        }
        else if (currentLLeft<=DISTANCE && currentRRight >DISTANCE)
        {
            turnRight(8,9,10,11,12,13,14,15);
        }
        else
        {
            turnLeft(8,9,10,11,12,13,14,15);
        }
     }
     else
     {
        if (currentLLeft>DISTANCE && currentRRight >DISTANCE)
        {
              switch (direction)
             {
                 case AFTERRIGHT:
                    turnLeft(8,9,10,11,12,13,14,15);
                    break;
                 case AFTERLEFT:
                    turnRight(8,9,10,11,12,13,14,15);
                    break;
                 default:
                    turnRight(8,9,10,11,12,13,14,15);                    
             }
        }
        else if(currentLLeft<=DISTANCE && currentRRight <=DISTANCE)
        {
            backward(8,9,10,11,12,13,14,15);
        }
        else if (currentLLeft<=DISTANCE && currentRRight >DISTANCE)
        {
            turnRight(8,9,10,11,12,13,14,15);
        }
        else
        {
            turnLeft(8,9,10,11,12,13,14,15);
        }
     }
     printf("distLeft: %d distRight: %d distLLeft: %d distRRight: %d count zero: %d\n",currentLeft,currentRight,currentLLeft,currentRRight,count);
     delay(100); 
  }
  return 0 ;
}
