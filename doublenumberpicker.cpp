#include "doublenumberpicker.h"
#include <QHBoxLayout>
#include <QDoubleValidator>
#include <float.h>

DoubleNumberPicker::DoubleNumberPicker(const QString& name, QWidget *parent, bool onlyPositiveNumbers) : QWidget(parent) {
    label = new QLabel(name, this);
    auto font = label->font();
    font.setPointSize(FONT_POINT_SIZE);
    label->setFont(font);
    label->adjustSize();
    label->setAlignment(Qt::AlignCenter);

    lineEdit = new QLineEdit(this);
    lineEdit->setFont(font);
    double minValue = onlyPositiveNumbers ? 0 : -10e10;
    auto validator = new QDoubleValidator(minValue, 10e10, 3, this);
    lineEdit->setValidator(validator);
    lineEdit->setMaximumWidth(80);

    this->setLayout(new QHBoxLayout(this));
    this->layout()->setSpacing(5);
    this->layout()->addWidget(label);
    this->layout()->addWidget(lineEdit);
    this->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
}

double DoubleNumberPicker::getValue() const {
    return lineEdit->text().toDouble();
}

bool DoubleNumberPicker::hasValue() const {
    return lineEdit->text() != "";
}
