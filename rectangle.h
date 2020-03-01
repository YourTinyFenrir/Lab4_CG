#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "QGraphicsScene"

class Rectangle {
private:
    float x;
    float y;
public:
    Rectangle();
    Rectangle(float, float);
    const Rectangle operator = (const Rectangle&);
    void draw(QGraphicsScene*, QPen);
    float getX();
    float getY();
};
// comment
#endif // RECTANGLE_H

//comment 1
