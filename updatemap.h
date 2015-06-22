void updatemap(){
	
	
	unsigned int Leftunit = currentLeft/unit;
	unsigned int Rightunit = currentRight/unit;
	unsigned int LFrontunit = currentLFront/unit;
	unsigned int RFrontunit = currentRFront/unit;
	unsigned int Frontunit;

	if(currentRFront > currentLFront)		
		Frontunit = LFrontunit;
	else 
		Frontunit = RFrontunit;
    
        

if(car.direction == UP){	
	
	if(Leftunit==0 && currentLeft!=0)
		car.map[car.x][car.y] &= LEFTWALL;
                car.map[car.x-1][car.y] &= NOFREE; 
	else
		car.map[car.x][car.y] |= LERTFREE;
                car.map[car.x-1][car.y] |= FREE;
	
	if(Rightunit==0 && currentRight!=0)
		car.map[car.x][car.y] &= RIGHTWALL;
                car.map[car.x+1][car.y] &= NOFREE
	else
		car.map[car.x][car.y] |= RIGHTFREE;
                car.map[car.x+1][car.y] |= FREE; 
	
	if(Frontunit==0 && (currentLFront!=0 || currentRFront!=0))
		car.map[car.x][car.y] &= UPWALL;
                car.map[car.x][car.y+1] &= NOFREE;
	else
		car.map[car.x][car.y] |= UPFREE;I

    if(car.map[car.x][car.y-1] &= FREE != 0)	
	    car.map[car.x][car.y] |= DWONFREE;
    else
        car.map[car.x][car.y] &= DOWNWALL;
}

if(car.direction == DOWN){	
	
	if(Leftunit==0 && currentLeft!=0)
		car.map[car.x][car.y] &= RIGHTWALL;
	else
		car.map[car.x][car.y] |= RIGHTFREE;
	
	if(Rightunit==0 && currentRight!=0)
		car.map[car.x][car.y] &= LEFTWALL;
	else
		car.map[car.x][car.y] |= LRFTFREE;
	
	if(Frontunit==0 && (currentLFront!=0 || currentRFront!=0))
		car.map[car.x][car.y] &= DOWNWALL;
	else
		car.map[car.x][car.y] |= DOWNFREE;
	
    if(car.map[car.x][car.y+1] &= FREE != 0)	
	    car.map[car.x][car.y] |= UPFREE;
    else
        car.map[car.x][car.y] &= UPWALL;
    
}

if(car.direction == LEFT){	
	
	if(Leftunit==0 && currentLeft!=0)
		car.map[car.x][car.y] &= DOWNWALL;
	else
		car.map[car.x][car.y] |= DOWNFREE;
	
	if(Rightunit==0 && currentRight!=0)
		car.map[car.x][car.y] &= UPWALL;
	else
		car.map[car.x][car.y] |= UPFREE;
	
	if(Frontunit==0 && (currentLFront!=0 || currentRFront!=0))
		car.map[car.x][car.y] &= LEFTWALL;
	else
		car.map[car.x][car.y] |= LEFTFREE;
	
    if(car.map[car.x+1][car.y] &= FREE != 0)	
	    car.map[car.x][car.y] |= RIGHTFREE;
    else
        car.map[car.x][car.y] &= RIGHTWALL;
	
}

if(car.direction == RIGHT){	
	
	if(Leftunit==0 && currentLeft!=0)
		car.map[car.x][car.y] &= UPWALL;
	else
		car.map[car.x][car.y] |= UPFREE;
	
	if(Rightunit==0 && currentRight!=0)
		car.map[car.x][car.y] &= DOWNWALL;
	else
		car.map[car.x][car.y] |= DOWNFREE;
	
	if(Frontunit==0 && (currentLFront!=0 || currentRFront!=0))
		car.map[car.x][car.y] &= RIGHTWALL;
	else
		car.map[car.x][car.y] |= RIGHTFREE;
	
    if(car.map[car.x-1][car.y] &= FREE != 0)	
	    car.map[car.x][car.y] |= LEFTFREE;
    else
        car.map[car.x][car.y] &= LEFTWALL;
	
}


}

