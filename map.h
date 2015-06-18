
#define UNKNOWN 0
#define FREE  1
#define UPFREE    FREE << 0
#define DOWNFREE  FREE << 1
#define LEFTFREE  FREE << 2
#define RIGHTFREE FREE << 3
#define WALL      FREE << 4
#define FULL      FREE << 5

enum{
    UP,
    DOWN,
    LEFT,
    RIGHT,
    NONE
}
struct CAR{
    volatile float x;// car position
    volatile float y;
    const float sizeX;// car size
    const float sizeY;
    char mode;          // running mode,0:first run
    char direction; // 0:North 1:East 2:South 3:West
    char turn;
    char map[256][256];//static declartion for only convenience, change to dynamic one later
};

typedef struct{
    char *row;
    int fill;
}COL;

COL *col;
CAR car;

void init();
void detect();
void updatemap();
void planpath();

int map[32][32];

void init(){
    car.x=1;
    car.y=1;
    sizeX=0.4;
    sizeY=0.4;
    mode=0;
    car.direction = UP;
    car.turn = NONE;
    int i,j;
    for(i=0;i<32;i++){
        for(j=0;j<32;j++){
            map[i][j] = FREE;
            if(j==0||i==0||i==31||j==31||(5 < j && j < 15 && 0<=i && i<=10)||(9<=j && j<=10 && 13<=i && i<=31)||(26<=j && j<=30 && 23<=i && i<=30))
                map[i][j] = WALL; 
        }
    }
    for(i=0;i<256;i++)
        for(j=0;j<256;j++)car.map[i][j]=UNKNOWN;
}


void planpath(){
    if(car.mode == FIRSTSWEEP)
        if(car.direction == UP) { 
            if(!(car.map[car.x][car.y+1] & UPFREE)) {
                car.turn = RIGHT;    
            }
        }
        else if(car.direction == DOWN) { 
            if(!(car.map[car.x][car.y-1] & DOWNFREE)) {
                car.turn = RIGHT;        
            }   
        }
        else if(car.direction == RIGHT) {
            if(!(car.map[car.x][car.y+1] & UPFREE) && !(car.map[car.x][car.y-1] & DOWNFREE) ) 
                car.turn = DOWN; 
            else if ( !(car.map[car.x][car.y-1] & DOWNFREE) && !(car.map[car.x][car.y+1] & UPFREE) )
                car.turn = UP;     
        }    
    else if(car.mode == SECONDSWEEP){}
    else if(car.mode == CLEAN){}

}    
