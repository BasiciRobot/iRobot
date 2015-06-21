
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
        break;
    case LEFT:
        turnLeft();
       break;
    case RIGHT:
        turnRight();
        break;
    case BACK:
        moveBackward();
        break;
    default:
        stop();
    }
    switch(car.direction){
        case UP:    car.y++;
        case DOWN:  car.y--;
        case LEFT:  car.x--;
        case RIGHT: car.x++;
    }
}
