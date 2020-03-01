#include "setofls.h"
#include "time.h"

SetOfLS::SetOfLS() {

    set.push_back(QPair<QVector2D, QVector2D>(QVector2D(0, 0), QVector2D(0, 0)));

}

SetOfLS::SetOfLS(QVector<QPair<QVector2D, QVector2D>> pts) {

    set = pts;

}

SetOfLS::SetOfLS(int size) {

    srand(time(0));

    for (int i = 0; i < size; ++i) {

        int quarter1 = rand() % 4;
        int quarter2;
        bool check = false;

        do {

            quarter2 = rand() % 4;
            if (quarter1 != quarter2)
                check = true;

        } while (!check);

        QVector2D newPoint1(0, 0);

        if (quarter1 == 0 || quarter1 == 3)
            newPoint1.setX(rand() % 250);
        else
            newPoint1.setX(-rand() % 250);

        if (quarter1 == 0 || quarter1 == 1)
            newPoint1.setY(rand() % 250);
        else
            newPoint1.setY(-rand() % 250);

        QVector2D newPoint2(0, 0);

        if (quarter2 == 0 || quarter2 == 3)
            newPoint2.setX(rand() % 250);
        else
            newPoint2.setX(-rand() % 250);

        if (quarter2 == 0 || quarter2 == 1)
            newPoint2.setY(rand() % 250);
        else
            newPoint2.setY(-rand() % 250);

        set.push_back(QPair<QVector2D, QVector2D>(newPoint1, newPoint2));

    }

}

const SetOfLS SetOfLS::operator=(const SetOfLS &temp) {

    this->set = temp.set;

    return *this;

}

void SetOfLS::draw(QGraphicsScene* scene, QPen pen) {

    for (int i = 0; i < set.size(); ++i)
        scene->addLine(set[i].first.x(), set[i].first.y(), set[i].second.x(), set[i].second.y(), pen);

}

void cutLS(QPair<QVector2D, QVector2D> *pts, bool change, int section, Rectangle rct) {

    if (change == true) {

        QPair<QVector2D, QVector2D> temp(*pts);
        pts->first = temp.second;
        pts->second = temp.first;

    }

    float temp;

    switch(section) {

    // Для первых четырех зон для расчета неизвестной координаты используем подобие треугольников
    case 1:

        temp = pts->first.y() + (pts->second.y() - pts->first.y()) * (-rct.getX() - pts->first.x()) / (pts->second.x() - pts->first.x());
        pts->first.setX(-rct.getX());
        pts->first.setY(temp);

        break;

    case 2:

        temp = pts->first.y() + (pts->second.y() - pts->first.y()) * (rct.getX() - pts->first.x()) / (pts->second.x() - pts->first.x());
        pts->first.setX(rct.getX());
        pts->first.setY(temp);

        break;

    case 4:

        temp = pts->first.x() + (pts->second.x() - pts->first.x()) * (-rct.getY() - pts->first.y()) / (pts->second.y() - pts->first.y());
        pts->first.setX(temp);
        pts->first.setY(-rct.getY());

        break;

    case 8:

        temp = pts->first.x() + (pts->second.x() - pts->first.x()) * (rct.getY() - pts->first.y()) / (pts->second.y() - pts->first.y());
        pts->first.setX(temp);
        pts->first.setY(rct.getY());

        break;

    // Для оставшихся зон добавляем условие определения ближайшей стороны (ее продолжения) прямоугольника
    case 5:

        if (abs(pts->first.y() - (-rct.getY())) > abs(pts->first.x() - (-rct.getX()))) {
            // Если ближе к стороне, параллельной OY, повторяем case 1
            temp = pts->first.y() + (pts->second.y() - pts->first.y()) * (-rct.getX() - pts->first.x()) / (pts->second.x() - pts->first.x());
            pts->first.setX(-rct.getX());
            pts->first.setY(temp);

        }
        else {
            // Иначе case 4
            temp = pts->first.x() + (pts->second.x() - pts->first.x()) * (-rct.getY() - pts->first.y()) / (pts->second.y() - pts->first.y());
            pts->first.setX(temp);
            pts->first.setY(-rct.getY());

        }

        break;

    case 6:

        if (abs(pts->first.y() - (-rct.getY())) > abs(pts->first.x() - rct.getX())) {
            // Если ближе к стороне, параллельной OY, повторяем case 2
            temp = pts->first.y() + (pts->second.y() - pts->first.y()) * (rct.getX() - pts->first.x()) / (pts->second.x() - pts->first.x());
            pts->first.setX(rct.getX());
            pts->first.setY(temp);

        }
        else {
            // Иначе case 4
            temp = pts->first.x() + (pts->second.x() - pts->first.x()) * (-rct.getY() - pts->first.y()) / (pts->second.y() - pts->first.y());
            pts->first.setX(temp);
            pts->first.setY(-rct.getY());

        }

        break;

    case 9:

        if (abs(pts->first.y() - rct.getY()) > abs(pts->first.x() - (-rct.getX()))) {
            // Если ближе к стороне, параллельной OY, повторяем case 1
            temp = pts->first.y() + (pts->second.y() - pts->first.y()) * (-rct.getX() - pts->first.x()) / (pts->second.x() - pts->first.x());
            pts->first.setX(-rct.getX());
            pts->first.setY(temp);

        }
        else {
            // Иначе case 8
            temp = pts->first.x() + (pts->second.x() - pts->first.x()) * (rct.getY() - pts->first.y()) / (pts->second.y() - pts->first.y());
            pts->first.setX(temp);
            pts->first.setY(rct.getY());

        }

        break;

    case 10:

        if (abs(pts->first.y() - rct.getY()) > abs(pts->first.x() - rct.getX())) {
            // Если ближе к стороне, параллельной OY, повторяем case 2
            temp = pts->first.y() + (pts->second.y() - pts->first.y()) * (rct.getX() - pts->first.x()) / (pts->second.x() - pts->first.x());
            pts->first.setX(rct.getX());
            pts->first.setY(temp);

        }
        else {
            // Иначе case 8
            temp = pts->first.x() + (pts->second.x() - pts->first.x()) * (rct.getY() - pts->first.y()) / (pts->second.y() - pts->first.y());
            pts->first.setX(temp);
            pts->first.setY(rct.getY());

        }

        break;

    }

}

SetOfLS SetOfLS::algorithmOfCohenSutherland(Rectangle rct) {

    QVector<QPair<QVector2D, QVector2D>> tempSet;

    for (int i = 0; i < set.size(); ++i) {

        int section1;
        int section2;

        QPair<QVector2D, QVector2D> tempPair(set[i]);

        do {

            section1 = 0;
            section2 = 0;

            if (tempPair.first.y() > rct.getY())
                section1 |= 8;
            if (tempPair.first.y() < -rct.getY())
                section1 |= 4;
            if (tempPair.first.x() > rct.getX())
                section1 |= 2;
            if (tempPair.first.x() < -rct.getX())
                section1 |= 1;

            if (tempPair.second.y() > rct.getY())
                section2 |= 8;
            if (tempPair.second.y() < -rct.getY())
                section2 |= 4;
            if (tempPair.second.x() > rct.getX())
                section2 |= 2;
            if (tempPair.second.x() < -rct.getX())
                section2 |= 1;

            if (section1 == 0 && section2 == 0)

                tempSet.push_back(tempPair);

            else if ((section1 & section2) == 0) {

                if (section1 != 0)
                    cutLS(&tempPair, false, section1, rct);
                else if (section2 != 0)
                    cutLS(&tempPair, true, section2, rct);

                if (section1 == section2)
                    tempSet.push_back(tempPair);

            }

        } while (section1 != section2 && (section1 & section2) == 0);

    }

    SetOfLS res(tempSet);

    return res;

}
