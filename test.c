#include <wiringPi.h>
#include <stdlib.h>

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
    digitalWrite(in2,LOW);
    digitalWrite(in3,HIGH);
    digitalWrite(in4,LOW);
    digitalWrite(in5,LOW);
    digitalWrite(in6,LOW);
    digitalWrite(in7,HIGH);
    digitalWrite(in8,LOW);
}

void turnLeft(int in1,int in2,int in3,int in4,int in5,int in6,int in7,int in8)
{
    digitalWrite(in1,HIGH);
    digitalWrite(in2,LOW);
    digitalWrite(in3,LOW);
    digitalWrite(in4,LOW);
    digitalWrite(in5,HIGH);
    digitalWrite(in6,LOW);
    digitalWrite(in7,LOW);
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

struct region{
	char up=0;
	char left=0;
	char right=0;
	char back=0;
	char state = 0;	//0=unknown 1=free 2=obstacle;
};

typedef struct car{
    volatile float x;// car position
    volatile float y;

    char mode;          // running mode,0:first run
    char direction; // 0:North 1:East 2:South 3:West
}CAR;

void detect(){
     unsigned int timeLeft,timeRight,timeLLeft,timeRRight;

     trigger(0);
     timeLeft = pulseIn(1,HIGH,500000);
     currentLeft = distance(timeLeft);
     
     trigger(2);  
     timeRight = pulseIn(3,HIGH,500000);
     currentRight = distance(timeRight);

     trigger(4);
     timeLLeft = pulseIn(5,HIGH,500000);
     currentLLeft = distance(timeLLeft);
     
     trigger(6);  
     timeRRight = pulseIn(7,HIGH,500000);
     currentRRight = distance(timeRRight);
     
}

void init(){
	car.x=1;
    	car.y=1;
	car.direction = 0;
	map[0][0].state = free;
	int i,j;
    	for(i=0;i<X;i++){
       		 for(j=0;j<Y;j++){
            		if(j==0||i==0||i==X||j==Y)
                		map[i][j] = 2; 
        	}
   	 }
}

void update_map(CAR car){
	
	//距離換算成單位
	unsigned int Leftunit = currentLeft/unit;
	unsigned int Rightunit = currentRight/unit;
	unsigned int LLeftunit = currentLLeft/unit;
	unsigned int RRightunit = currentRRight/unit;
	unsigned int Frontunit;

	//判斷前方左or右較近，取近的
	if(rightunit>leftunit)		
		Frontunit = Leftunit;
	else 
		Frontunit = Rightunit;
	
	//根據單位，決定前後左右state
	if(Leftunit==0 && currentLLeft!=0)	//currentLLeft=0 超過可測距離範圍，表示下個單位無障礙物
		map[car.x][car.y].left = 2;
	else
		map[car.x][car.y].left = 1;
	
	if(Rightunit==0 && currentRRight!=0)
		map[car.x][car.y].right = 2;
	else
		map[car.x][car.y].right = 1;
	
	if(Frontunit==0 && (currentLeft!=0 || currentRight!=0))
		map[car.x][car.y].up = 2;
	else
		map[car.x][car.y].up = 1;
	
	if(car.direction==0)
		map[car.x][car.y].back = map[car.x][car.y-1].state;
	else if(car.direction==2)
		map[car.x][car.y].back = map[car.x][car.y+1].state;
	
}

//global變數
unsigned int unit 1 ;			//單位大小
volatile unsigned int currentLeft,currentRight,currentLLeft,currentRRight;

CAR car;

int X 256;
int Y 128;	 
struct region map[X][Y];



int main(void){
	
}

