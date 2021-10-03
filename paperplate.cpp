#include "paperplate.h"
#include <stdexcept>

#define _USE_MATH_DEFINES
#include <math.h>

PaperPlate::PaperPlate(): PositionedPaperObject(0, 0, 1), radius(25) {}

PaperPlate::PaperPlate(double _x, double _y, double _thickness, double _radius): PositionedPaperObject(_x, _y, _thickness) {
    setRadius(_radius);
}

PaperPlate::PaperPlate(const PaperPlate &other): PositionedPaperObject(other.getX(), other.getY(), other.getThickness()), radius(other.radius) {}

PaperPlate::~PaperPlate() {}

double PaperPlate::getRadius() const {
    return radius;
}

void PaperPlate::setRadius(double newRadius) {
    if(newRadius <= 0) {
        throw std::invalid_argument("radius of plate must be positive");
    }
    radius = newRadius;
}

bool PaperPlate::operator==(const PaperPlate &rhs) {
    return PositionedPaperObject::operator==(rhs) && radius == rhs.radius;
}

bool PaperPlate::operator!=(const PaperPlate &rhs) {
    return !(*this == rhs);
}

QString PaperPlate::description() const {
    return PositionedPaperObject::description() + ", radius=" + QString::number(radius);
}

PositionedElementType PaperPlate::getType() const {
    return PositionedElementType::PAPER_PLATE;
}

QString PaperPlate::getStringType() const {
    return "PAPER_PLATE";
}

QJsonObject PaperPlate::toJsonObject() const {
    auto json = PositionedPaperObject::toJsonObject();
    json.insert("radius", radius);
    return json;
}

double PaperPlate::calculateVolume() const {
    return getThickness() * M_PI * radius * radius;
}

bool PaperPlate::isPointInside(double xPoint, double yPoint) const {
    double squareXDistanceFromCenter = getX() - xPoint;
    squareXDistanceFromCenter *= squareXDistanceFromCenter;
    double squareYDistanceFromCenter = getY() - yPoint;
    squareYDistanceFromCenter *= squareYDistanceFromCenter;
    return radius >= sqrt(squareXDistanceFromCenter + squareYDistanceFromCenter);
}
