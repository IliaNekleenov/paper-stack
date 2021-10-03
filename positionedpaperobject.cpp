#include "positionedpaperobject.h"

PositionedPaperObject::PositionedPaperObject(double _x, double _y, double _thickness): x(_x), y(_y) {
    setThickness(_thickness);
}

PositionedPaperObject::PositionedPaperObject(const PositionedPaperObject &other): x(other.x), y(other.y), thickness(other.thickness) {}

double PositionedPaperObject::getX() const {
    return x;
}

double PositionedPaperObject::getY() const {
    return y;
}

double PositionedPaperObject::getThickness() const {
    return thickness;
}

void PositionedPaperObject::setX(double newX) {
    x = newX;
}

void PositionedPaperObject::setY(double newY) {
    y = newY;
}

void PositionedPaperObject::setThickness(double newThickness) {
    if(newThickness <= 0) {
        throw std::invalid_argument("thickness of paper must be positive");
    }
    thickness = newThickness;
}

bool PositionedPaperObject::operator==(const PositionedPaperObject &rhs) {
    return x == rhs.x && y == rhs.y && thickness == rhs.thickness;
}

bool PositionedPaperObject::operator!=(const PositionedPaperObject &rhs) {
    return !(*this == rhs);
}

QString PositionedPaperObject::description() const {
    return "type=" + getStringType() + ", x=" + QString::number(x) + ", y=" + QString::number(y) + ", thickness=" + QString::number(thickness);
}

QJsonObject PositionedPaperObject::toJsonObject() const {
    QJsonObject json;
    json.insert("x", x);
    json.insert("y", y);
    json.insert("thickness", thickness);
    json.insert("type", getType());
    return json;
}
