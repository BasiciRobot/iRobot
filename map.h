
#define UNKNOWN 0
#define UPFREE    1 << 0
#define DOWNFREE  1 << 1
#define LEFTFREE  1 << 2
#define RIGHTFREE 1 << 3
#define UPWALL    ~UPFREE
#define DOWNWALL  ~DOWNFREE
#define LEFTWALL  ~LEFTFREE
#define RIGHTWALL ~RIGHTFREE
#define FREE      1 << 4
#define NOFREE    ~FREE
#define FULL      ~(1 << 5)
#define VISITED   1 << 6
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

const unsigned int unit = 240;

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
