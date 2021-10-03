#include "positionedpaperobjectform.h"
#include <QMessageBox>

PositionedPaperObjectForm::PositionedPaperObjectForm(const QString& name, QWidget *parent) : QWidget(parent) {
    mainLayout = new QVBoxLayout(this);
    formLayout = new QGridLayout(this);
    xPicker = new DoubleNumberPicker("X", this);
    yPicker = new DoubleNumberPicker("Y", this);
    thicknessPicker = new DoubleNumberPicker("Thickness", this, true);
    submitButton = new QPushButton("Add " + name, this);

    formLayout->addWidget(xPicker, 0, 0);
    formLayout->addWidget(yPicker, 0, 1);
    formLayout->addWidget(thicknessPicker, 0, 2);

    auto label = new QLabel(name, this);
    auto font = label->font();
    font.setPointSize(FONT_POINT_SIZE);
    label->setFont(font);
    submitButton->setFont(font);
    QObject::connect(submitButton, &QPushButton::clicked, this, &PositionedPaperObjectForm::onSubmitButtonClicked);
    mainLayout->addWidget(label);
    mainLayout->addLayout(formLayout);
    mainLayout->addWidget(submitButton);
}

double PositionedPaperObjectForm::getX() const {
    return xPicker->getValue();
}

double PositionedPaperObjectForm::getY() const {
    return yPicker->getValue();
}

double PositionedPaperObjectForm::getThickness() const {
    return thicknessPicker->getValue();
}

void PositionedPaperObjectForm::onSubmitButtonClicked() {
    if(isFilledCorrectly()) {
        emit objectSubmitted(getValue());
        return;
    }
    QMessageBox::warning(this, "Some fields are empty", "Specify all the fields in form to add item to stack");
}

bool PositionedPaperObjectForm::isFilledCorrectly() const {
    return xPicker->hasValue() && yPicker->hasValue() && thicknessPicker->hasValue();
}
