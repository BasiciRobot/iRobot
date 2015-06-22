
#define UNKNOWN 0
#define UPFREE    0x01
#define DOWNFREE  0x02
#define LEFTFREE  0x04
#define RIGHTFREE 0x08
#define UPWALL    ~UPFREE
#define DOWNWALL  ~DOWNFREE
#define LEFTWALL  ~LEFTFREE
#define RIGHTWALL ~RIGHTFREE
#define FREE      0x10
#define NOFREE    ~FREE
#define FULL      ~(0x20)
#define VISITED   0x40
enum{
    NONE,
    UP,
    DOWN,
    LEFT,
    RIGHT,
    BACK
};
enum{
    FIRSTSWEEP,
    SECONDSWEEP,
    CLEAN
};
typedef struct CAR{
    int x;   // car position
    int y;
    //const float sizeX;  // car size
    //const float sizeY;
    char mode;          // running mode,0:first run
    char direction;     // 0:North 1:East 2:South 3:West
    char turn;          
    char map[256][256]; //static declartion for only convenience, change to dynamic one later
}CAR;

static CAR car;

const unsigned int unit = 360;

void init();
void detect();
void updatemap();
void planpath();
void outputmap(){
    FILE *fptr;
    fptr = fopen("carmap", "w");
    if(!fptr){
        return;
    }
    int i,j;
    for(i=0;i<256;i++)for(j=0;j<256;j++)fprintf(fptr,"%c\n",car.map[i][j]);
    exit(1);
}
