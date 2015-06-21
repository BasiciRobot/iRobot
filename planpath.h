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
