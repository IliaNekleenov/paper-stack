#ifndef PAPERPLATEFORM_H
#define PAPERPLATEFORM_H

#include "positionedpaperobjectform.h"


class PaperPlateForm : public PositionedPaperObjectForm
{
public:
    PaperPlateForm(const QString& name, QWidget *parent = nullptr);

    std::shared_ptr<PositionedPaperObject> getValue() const override;
    bool isFilledCorrectly() const override;

    double getRadius() const;

private:
    DoubleNumberPicker* radiusPicker;
};

#endif // PAPERPLATEFORM_H
