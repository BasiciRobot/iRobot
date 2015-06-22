void planpath(){
    if(car.mode == FIRSTSWEEP)
        if(car.direction == UP) { 
            if(!(car.map[car.x][car.y] & UPFREE)) {
                if(car.map[car.x][car.y] & RIGHTFREE){
                    car.turn = RIGHT;    
                    car.direction = RIGHT;
                }
                else 
                    car.mode = SECONDSWEEP;
            }
        }
        else if(car.direction == DOWN) { 
            if(!(car.map[car.x][car.y] & DOWNFREE)) {
                if(car.map[car.x][car.y] & RIGHTFREE){
                    car.turn = LEFT;        
                    car.direction = RIGHT;
                }
                else
                    car.mode = SECONDSWEEP;
            }   
        }
        else if(car.direction == RIGHT) {
            if(!(car.map[car.x][car.y] & UPFREE) && !(car.map[car.x][car.y] & DOWNFREE)){ 
                if(car.map[car.x][car.y] & RIGHTFREE)
                    car.turn = NONE;
                else
                    car.mode = SECONDSWEEP;
            }
            else if(car.map[car.x][car.y] & UPFREE){
                car.turn = LEFT; 
                car.direction = UP;
            }
            else if(car.map[car.x][car.y] & DOWNFREE){
                car.turn = RIGHT;
                car.direction = DOWN;
            }
       }    
    else if(car.mode == SECONDSWEEP){
        outputmap();
    }
    else if(car.mode == CLEAN){}

}
/*
struct CAR{
    volatile float x;// car position
    volatile float y;
    const float sizeX;// car size
    const float sizeY;
    Node* tmpNode, Unknown_Head, Unknown_Tail;
    char mode;          
    // running mode,0:bottom-left corner, 1:top-right corner
    short PreTopY, PreDownY;
    char tmpX, tmpY, tmpType;
    char PreUpDown; //0:UP 1:DOWN
    char direction; // 0:North 1:East 2:South 3:West
    char turn;
    char map[256][256];//static declartion for only convenience, change to dynamic one later
};
void init(){
    car.x=1;
    car.y=1;
    sizeX=0.4;
    sizeY=0.4;
    mode=0;
    car.direction = UP;
    car.turn = NONE;
    car.PreUpDown = UP;
    car.PreTopY = 255;
    car.PreDownY = 255;
    Node FirstNode;
    FirstNode.type = 255;
    FirstNode.Next = NULL;
    Unknown_Head = &FirstNode;
    Unknown_Tail = &FirstNode;
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
typedef struct {
    short type = 0; //0:normal 1:bot-left unknown 2:top-right unknown 255:Record first node
    int x, y;
    Node* Next;
    Node* Prev;
}Node;

void planpath(){
    if(car.mode == 0) //Start from bottom-left corner
    {
        if(car.direction == UP) {  
            if(!(car.map[car.x][car.y] & UPFREE)) {
                car.turn = RIGHT;
                if( (car.map[car.x+1][car.y] == WALL) || (car.map[car.x+1][car.y] == FULL) ) //到底了
                {
                    car.mode = ROUTE;
                } 
                car.PreUpDown = UP; 
                if( (car.PreTopY != 255) && (car.PreTopY != car.y) ) //if 不齊
                {
                    car.tmpY = car.y;
                    while((car.map[car.x-1][car.PreTopY] == (!WALL)&&(!FULL)&&(!DONE)) && (tmpY > PreTopY))
                    {
                        car.tmpY--;
                        car.tmpType = 2;          
                    }
                    while((car.map[car.x-1][car.PreTopY] == (!WALL)&&(!FULL)&&(!DO  NE)) && (tmpY < PreTopY))
                    {
                        car.tmpY++;
                        car.tmpType = 1;
                    }    
                    if ( car.tmpY != PreTopY )
                    {
                        car.tmpNode = malloc(sizeof(Node));
                        car.tmpNode->x = car.x-1;
                        car.tmpNode->y = car.tmpY;
                        car.tmpNode->type = car.tmpType;
                        car.tmpNode->Next = NULL;
                        car.tmpNode->Prev = car.Unknown_Tail;
                        car.Unknown_Tail->Next = car.tmpNode;
                    }
                }
            }
        }
        else if(car.direction == DOWN) { 
            if(!(car.map[car.x][car.y] & DOWNFREE)) {
                car.turn = RIGHT;
                if( (car.map[car.x+1][car.y] == WALL) || (car.map[car.x+1][car.y] == FULL) ) //到底了
                {
                    car.mode = ROUTE;
                }        
                car.PreUpDown = DOWN;
                if( (car.PreDownY != 255) && (car.PreDownY < car.y) ) //if y不齊
                {
                    car.tmpY = car.y;
                    while((car.map[car.x-1][car.PreDownY] == (!WALL)&&(!FULL)&&(!DONE)) && (tmpY < PreDownY))
                    {
                        car.tmpY++;
                        car.tmpType = 1;          
                    }
                    while((car.map[car.x-1][car.PreDownY] == (!WALL)&&(!FULL)&&(!DONE)) && (tmpY > PreDownY))
                    {
                        car.tmpY--i;
                        car.tmpType = 2;
                    }
                    if ( car.tmpY != PreDownY )
                    {
                        car.tmpNode = malloc(sizeof(Node));
                        car.tmpNode->x = car.x-1;
                        car.tmpNode->y = car.tmpY;
                        car.tmpNode->type = car.tmpType;
                        car.tmpNode->Next = NULL;
                        car.tmpNode->Prev = car.Unknown_Tail;
                        car.Unknown_Tail->Next = car.tmpNode;
                    }
                }
            }   
        }
        else if(car.direction == RIGHT) {
            if((car.map[car.x][car.y] & UPFREE) && !(car.map[car.x][car.y] & DOWNFREE) ) 
                car.turn = DOWN; 
            else if ( (car.map[car.x][car.y] & DOWNFREE) && !(car.map[car.x][car.y] & UPFREE) )
                car.turn = UP; 
            else if ((car.map[car.x][car.y] & DOWNFREE) && (car.map[car.x][      car.y] & UPFREE) )   
            {   
                if (PreUpDown == UP)
                    car.turn = Down;
                else
                    car.turn = UP;
            }    
        }    
        if(car.mode == ROUTE)
        {
            Node PATH;
            PATH.type = 0;
            PATH.Next = NULL;
            PATH.Prev = NULL; 
            //Search the nearest unknown coordinate
            Search(&PATH);
            //Use Hadlock's Algorithm to find an optimal path
            Hadlock(&PATH);
            //Go to (X,Y) of PATH from (car.x,car.y)
            car.mode = GOTOPATH;
        } 
    }

    else if(car.mode == SECONDSWEEP){}
    else if(car.mode == CLEAN){}
    else if(car.mode == GOTOPATH){} //設結束點
    else if(car.mode == END){}
}
void Search(Node* path)
{
    if(car.Unknown_Tail->type != 255) //從最後一個點開始找 
    { 
        //找上一個Unknown點
        path->x = car.Unknown_Tail->x;
        path->y = car.Unknown_Tail->y;
        //並從Unknown List中刪除
        car.Unknown_Tail = car.Unknown_Tail->Prev;
        car.Unknown_Tail->Next = NULL;
        return;
    }
    else
        //回原點
    {
        path->x = 0;
        path->y = 0;
        return; 
    }
} 
void Hadlock(Node* path)
{

} 
*/   
