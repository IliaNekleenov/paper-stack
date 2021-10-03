#include "papersheetform.h"
#include "papersheet.h"

PaperSheetForm::PaperSheetForm(const QString& name, QWidget *parent): PositionedPaperObjectForm(name, parent) {
    widthPicker = new DoubleNumberPicker("Width", this, true);
    heightPicker = new DoubleNumberPicker("Height", this, true);

    formLayout->addWidget(widthPicker, 1, 0);
    formLayout->addWidget(heightPicker, 1, 1);
}

std::shared_ptr<PositionedPaperObject> PaperSheetForm::getValue() const {
    return std::make_shared<PaperSheet>(getX(), getY(), getThickness(), getWidth(), getHeight());
}

bool PaperSheetForm::isFilledCorrectly() const {
    return PositionedPaperObjectForm::isFilledCorrectly() && widthPicker->hasValue() && heightPicker->hasValue();
}

double PaperSheetForm::getWidth() const {
    return widthPicker->getValue();
}

double PaperSheetForm::getHeight() const {
    return heightPicker->getValue();
}
