
#define UNKNOWN 0
#define FREE  1
#define UPFREE    FREE << 0
#define DOWNFREE  FREE << 1
#define LEFTFREE  FREE << 2
#define RIGHTFREE FREE << 3
#define WALL      FREE << 4
#define FULL      FREE << 5
#define VISITED   FREE << 6
enum{
    UP,
    DOWN,
    LEFT,
    RIGHT,
    NONE
}
struct CAR{
    int x;   // car position
    int y;
    //const float sizeX;  // car size
    //const float sizeY;
    char mode;          // running mode,0:first run
    char direction;     // 0:North 1:East 2:South 3:West
    char turn;          
    char map[256][256]; //static declartion for only convenience, change to dynamic one later
};

static CAR car;

void init();
void detect();
void updatemap();
void planpath();

void planpath(){
    if(car.mode == FIRSTSWEEP)
        if(car.direction == UP) { 
            if(!(car.map[car.x][car.y] & UPFREE)) {
                car.turn = RIGHT;    
            }
        }
        else if(car.direction == DOWN) { 
            if(!(car.map[car.x][car.y] & DOWNFREE)) {
                car.turn = LEFT;        
            }   
        }
        else if(car.direction == RIGHT) {
            if(!(car.map[car.x][car.y] & UPFREE) && !(car.map[car.x][car.y] & DOWNFREE)) 
                car.turn = NONE;
            else
                car.turn = LEFT; 
        }    
    else if(car.mode == SECONDSWEEP){}
    else if(car.mode == CLEAN){}

}    
