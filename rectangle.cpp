#include "rectangle.h"

Rectangle::Rectangle() {

    x = 0;
    y = 0;

}

Rectangle::Rectangle(float a, float b) {

    x = a;
    y = b;

}

const Rectangle Rectangle::operator=(const Rectangle &temp) {

    this->x = temp.x;
    this->y = temp.y;

    return *this;

}

void Rectangle::draw(QGraphicsScene* scene, QPen pen) {

    scene->addLine(-x, y, -x, -y, pen);
    scene->addLine(-x, -y, x, -y, pen);
    scene->addLine(x, -y, x, y, pen);
    scene->addLine(x, y, -x, y, pen);

}

float Rectangle::getX() {

    return x;

}

float Rectangle::getY() {

    return y;

}
