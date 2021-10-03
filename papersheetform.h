#ifndef PAPERSHEETFORM_H
#define PAPERSHEETFORM_H

#include "positionedpaperobjectform.h"

class PaperSheetForm : public PositionedPaperObjectForm
{
public:
    explicit PaperSheetForm(const QString& name, QWidget *parent = nullptr);

    std::shared_ptr<PositionedPaperObject> getValue() const override;
    bool isFilledCorrectly() const override;

    double getWidth() const;
    double getHeight() const;

private:
    DoubleNumberPicker* widthPicker;
    DoubleNumberPicker* heightPicker;
};

#endif // PAPERSHEETFORM_H
