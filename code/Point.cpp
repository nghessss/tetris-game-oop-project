#include "Point.h"
Point::Point(): x(0), y(0) {}

Point::Point(int x, int y){
    this->x = x;
    this->y = y;
}
int Point::getX(){
    return x;
}
int Point::getY(){
    return y;
}
void Point::setX(int x){
    this->x = x;
}
void Point::setY(int y){
    this->y = y;
}
bool Point::operator==(const Point& other) const {
    return this->x == other.x && this->y == other.y;
}
bool Point::operator!=(const Point& other) const {
    return !(this->x == other.x && this->y == other.y);
}