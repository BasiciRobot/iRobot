void updatemap(){

    if(car.turn!=NONE){}
    else{
        if (currentLFront > DISTANCE && currentRFront > DISTANCE)
        {
            car.map[car.x][car.y] |= UPFREE;   
        }
        else if(currentLFront <= DISTANCE && currentRFront <= DISTANCE)
        {
            if (currentLeft > DISTANCE && currentRight > DISTANCE)
            {
                    switch (car.turn)
                    {
                        case RIGHT:
                        turnLeft();                    
                        break;
                        case LEFT:
                        turnRight();
                        break;
                        default:
                        turnRight();
                    }
            }
            else if(currentLeft <= DISTANCE && currentRight <= DISTANCE)
            {
                moveBackward();
            }
            else if (currentLeft <= DISTANCE && currentRight > DISTANCE)
            {
                turnRight();
            }
            else
            {
                turnLeft();
            }
        }
        else if (currentLFront <= DISTANCE && currentRFront > DISTANCE)
        {
            if (currentLeft > DISTANCE && currentRight > DISTANCE)
            {
                    switch (car.turn)
                    {
                        case RIGHT:
                        turnLeft();
                        break;
                        case LEFT:
                        turnRight();
                        break;
                        default:
                        turnRight();
                    }
            }
            else if(currentLeft <= DISTANCE && currentRight <= DISTANCE)
            {
                moveBackward();   
            }
            else if (currentLeft <= DISTANCE && currentRight > DISTANCE)
            {
                turnRight();
            }
            else
            {
                turnLeft();
            }
        }
        else
        {
            if (currentLeft > DISTANCE && currentRight > DISTANCE)
            {
                    switch (car.turn)
                    {
                        case RIGHT:
                        turnLeft();
                        break;
                        case LEFT:
                        turnRight();
                        break;
                        default:
                        turnRight();
                    }
            }
            else if(currentLeft <= DISTANCE && currentRight <= DISTANCE)
            {
                moveBackward();
            }
            else if (currentLeft <= DISTANCE && currentRight > DISTANCE)
            {
                turnRight();
            }
            else
            {
                turnLeft();
            }
        }
    }




}

void updatemap(){
	
    unsigned int unit = 1;
	//¶ZÂ÷´«ºâ¦¨³æ¦ì
	unsigned int Leftunit = currentLeft/unit;
	unsigned int Rightunit = currentRight/unit;
	unsigned int LFrontunit = currentLFront/unit;
	unsigned int RFrontunit = currentRFront/unit;
	unsigned int Frontunit;

	if(RFrontunit > LFrontunit)		
		Frontunit = LFrontunit;
	else 
		Frontunit = RFrontunit;
	
	//®Ú¾Ú³æ¦ì¡A¨M©w«e«á¥ª¥kstate
	if(LFrontunit==0 && currentLeft!=0)	//currentLLeft=0 ¶W¹L¥i´ú¶ZÂ÷½d³ò¡Aªí¥Ü¤U­Ó³æ¦ìµL»ÙÃªª«
		map[car.x][car.y].left = 2;
	else
		map[car.x][car.y].left = 1;
	
	if(RFrontunit==0 && currentRight!=0)
		map[car.x][car.y].right = 2;
	else
		map[car.x][car.y].right = 1;
	
	if(Frontunit==0 && (currentLFront!=0 || currentRFront!=0))
		map[car.x][car.y].up = 2;
	else
		map[car.x][car.y].up = 1;
	
	if(car.direction==UP)
		map[car.x][car.y].back = map[car.x][car.y-1].state;
	else if(car.direction==DOWN)
		map[car.x][car.y].back = map[car.x][car.y+1].state;
	
}

