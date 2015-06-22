
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
    switch(car.turn){
    case NONE:
        moveForward();
        continue;
    case LEFT:
        turnLeft();
        continue;
    case RIGHT:
        turnRight();
        continue;
    case BACK:
        moveBackward();
        continue;
    default:
        stop();
    }
    switch(car.direction){
        case UP:    car.y++;continue;
        case DOWN:  car.y--;continue;
        case LEFT:  car.x--;continue;
        case RIGHT: car.x++;
        
    }
}
