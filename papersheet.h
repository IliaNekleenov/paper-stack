#ifndef PAPER_H
#define PAPER_H

#include "positionedpaperobject.h"
#include <string>

class PaperSheet : public PositionedPaperObject
{
    double width;
    double height;
public:
    PaperSheet();
    PaperSheet(double x, double y, double thickness, double width, double height);
    PaperSheet(const PaperSheet &other);

    ~PaperSheet() override;

    double getWidth() const;
    void setWidth(double newWidth);
    double getHeight() const;
    void setHeight(double newHeight);
    bool operator==(const PaperSheet& rhs);
    bool operator!=(const PaperSheet& rhs);

    QString description() const override;
    PositionedPaperObjectType getType() const override;
    QString getStringType() const override;
    QJsonObject toJsonObject() const override;
    double calculateVolume() const override;
    bool isPointInside(double xPoint, double yPoint) const override;
};

#endif // PAPER_H
