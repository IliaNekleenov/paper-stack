#include "papersheet.h"
#include <assert.h>

PaperSheet::PaperSheet(): PositionedPaperObject(0, 0, 0.01), width(29.7), height(21) {} // default characteristics of A4 (centimeters)

PaperSheet::PaperSheet(double _x, double _y, double _thickness, double _width, double _height): PositionedPaperObject(_x, _y, _thickness) {
    setWidth(_width);
    setHeight(_height);
}

PaperSheet::PaperSheet(const PaperSheet &other):
    PositionedPaperObject(other.getX(), other.getY(), other.getThickness()), width(other.width), height(other.height) {}

PaperSheet::~PaperSheet() {}

double PaperSheet::getWidth() const {
    return width;
}

void PaperSheet::setWidth(double newWidth) {
    if(newWidth <= 0) {
        throw std::invalid_argument("width of paper must be positive");
    }
    width = newWidth;
}

double PaperSheet::getHeight() const {
    return height;
}

void PaperSheet::setHeight(double newHeight) {
    if(newHeight <= 0) {
        throw std::invalid_argument("height of paper must be positive");
    }
    height = newHeight;
}

bool PaperSheet::operator==(const PaperSheet &rhs) {
    return PositionedPaperObject::operator==(rhs) && width == rhs.width && height == rhs.height;
}

bool PaperSheet::operator!=(const PaperSheet &rhs) {
    return !(*this == rhs);
}

QString PaperSheet::description() const {
    return PositionedPaperObject::description() + ", width=" + QString::number(width) + ", height=" + QString::number(height);
}

PositionedPaperObjectType PaperSheet::getType() const {
    return PositionedPaperObjectType::PAPER_SHEET;
}

QString PaperSheet::getStringType() const {
    return "PAPER_SHEET";
}

QJsonObject PaperSheet::toJsonObject() const {
    auto json = PositionedPaperObject::toJsonObject();
    json.insert("width", height);
    json.insert("height", height);
    return json;
}

double PaperSheet::calculateVolume() const {
    return getThickness() * width * height;
}

bool PaperSheet::isPointInside(double xPoint, double yPoint) const {
    double halfWidth = width / 2;
    double halfHeight = height / 2;
    return xPoint >= (getX() - halfWidth) && xPoint <= (getX() + halfWidth) &&
           yPoint >= (getY() - halfHeight) && yPoint <= (getY() + halfHeight);
}
