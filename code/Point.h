#pragma once
#ifndef POINTE_H
#define POINTE_H
class Point{
    int x;
    int y;
public:
    Point();
    Point(int x, int y);
    int getX();
    int getY();
    void setX(int x);
    void setY(int y);
    bool operator==(const Point& other) const;
    bool operator!=(const Point& other) const;
};
#endif
