
void moveForward()
{
    digitalWrite(8,HIGH);
    digitalWrite(9,LOW);
    digitalWrite(10,HIGH);
    digitalWrite(11,LOW);
    digitalWrite(12,HIGH);
    digitalWrite(13,LOW);
    digitalWrite(14,HIGH);
    digitalWrite(15,LOW);
}

void moveBackward()
{
    digitalWrite(8,LOW);
    digitalWrite(9,HIGH);
    digitalWrite(10,LOW);
    digitalWrite(11,HIGH);
    digitalWrite(12,LOW);
    digitalWrite(13,HIGH);
    digitalWrite(14,LOW);
    digitalWrite(15,HIGH);
}

void turnRight()
{
    digitalWrite(8,LOW);
    digitalWrite(9,HIGH);
    digitalWrite(10,HIGH);//LEFT TIRE
    digitalWrite(11,LOW);
    digitalWrite(12,HIGH);
    digitalWrite(13,LOW);
    digitalWrite(14,HIGH);//LEFT TIRE
    digitalWrite(15,LOW);
}

void turnLeft()
{
    digitalWrite(8,HIGH);//RIGHT TIRE
    digitalWrite(9,LOW);
    digitalWrite(10,LOW);
    digitalWrite(11,HIGH);
    digitalWrite(12,HIGH);//RIGHT TIRE
    digitalWrite(13,LOW);
    digitalWrite(14,HIGH);
    digitalWrite(15,LOW);
}

void stop()
{
    digitalWrite(8,LOW);
    digitalWrite(9,LOW);
    digitalWrite(10,LOW);
    digitalWrite(11,LOW);
    digitalWrite(12,LOW);
    digitalWrite(13,LOW);
    digitalWrite(14,LOW);
    digitalWrite(15,LOW);
}

void move(){

        if(car.turn!=NONE){}
        else{
            if (currentLFront > DISTANCE && currentRFront > DISTANCE)
            {
                
                car.map[car.x][car.y] |= UPFREE;
                if (currentLeft > DISTANCE && currentRight > DISTANCE)
                {
                    moveForward();            
                }
                else if(currentLeft <= DISTANCE && currentRight <= DISTANCE)
                {
                    moveForward();            
                }
                else if (currentLeft <= DISTANCE && currentRight > DISTANCE)
                {
                    turnRight();            
                    car.turn = RIGHT;
                }
                else
                {
                    turnLeft();            
                    car.turn = LEFT;
                }
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
