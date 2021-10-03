#ifndef PLATE_H
#define PLATE_H

#include "positionedpaperobject.h"

class PaperPlate : public PositionedPaperObject
{
    double radius;
public:
    PaperPlate();
    PaperPlate(double _x, double _y, double _thickness, double _radius);
    PaperPlate(const PaperPlate &other);

    ~PaperPlate() override;

    double getRadius() const;
    void setRadius(double newRadius);
    bool operator==(const PaperPlate& rhs);
    bool operator!=(const PaperPlate& rhs);

    QString description() const override;
    PositionedPaperObjectType getType() const override;
    QString getStringType() const override;
    QJsonObject toJsonObject() const override;
    double calculateVolume() const override;
    bool isPointInside(double xPoint, double yPoint) const override;
};

#endif // PLATE_H
