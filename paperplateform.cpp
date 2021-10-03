#include "paperplateform.h"
#include "paperplate.h"

PaperPlateForm::PaperPlateForm(const QString& name, QWidget *parent): PositionedPaperObjectForm(name, parent) {
    radiusPicker = new DoubleNumberPicker("Radius", this, true);

    formLayout->addWidget(radiusPicker, 1, 0);
}

std::shared_ptr<PositionedPaperObject> PaperPlateForm::getValue() const {
    return std::make_shared<PaperPlate>(getX(), getY(), getThickness(), getRadius());
}

bool PaperPlateForm::isFilledCorrectly() const {
    return PositionedPaperObjectForm::isFilledCorrectly() && radiusPicker->hasValue();
}

double PaperPlateForm::getRadius() const {
    return radiusPicker->getValue();
}
