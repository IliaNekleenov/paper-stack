#ifndef POSITION_H
#define POSITION_H

#include <QJsonObject>

enum PositionedPaperObjectType {
    PAPER_SHEET = 0, PAPER_PLATE = 1
};

class PositionedPaperObject
{
    double x;
    double y;
    double thickness;
public:
    PositionedPaperObject() = default;
    PositionedPaperObject(double x, double y, double thickness);
    PositionedPaperObject(const PositionedPaperObject &other);

    double getX() const;
    double getY() const;
    double getThickness() const;
    void setX(double newX);
    void setY(double newY);
    void setThickness(double newThickness);
    bool operator==(const PositionedPaperObject& rhs);
    bool operator!=(const PositionedPaperObject& rhs);

    virtual QString description() const;
    virtual ~PositionedPaperObject() {}
    virtual PositionedPaperObjectType getType() const = 0;
    virtual QString getStringType() const = 0;
    virtual QJsonObject toJsonObject() const;
    virtual double calculateVolume() const = 0;
    virtual bool isPointInside(double xPoint, double yPoint) const = 0;
};

#endif // POSITION_H
