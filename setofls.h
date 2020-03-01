#ifndef SETOFLS_H
#define SETOFLS_H

#include "QVector"
#include "QVector2D"
#include "QGraphicsScene"
#include "rectangle.h"

// LS - line segments
class SetOfLS {
private:
    QVector<QPair<QVector2D, QVector2D>> set;
public:
    SetOfLS();
    SetOfLS(QVector<QPair<QVector2D, QVector2D>>);
    SetOfLS(int);
    const SetOfLS operator = (const SetOfLS&);
    void draw(QGraphicsScene*, QPen);
    SetOfLS algorithmOfCohenSutherland(Rectangle);
};

#endif // SETOFLS_H
