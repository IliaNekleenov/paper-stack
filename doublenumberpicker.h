#ifndef DOUBLENUMBERPICKER_H
#define DOUBLENUMBERPICKER_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>

#define FONT_POINT_SIZE 9

class DoubleNumberPicker : public QWidget
{
    Q_OBJECT
public:
    explicit DoubleNumberPicker(const QString& name, QWidget *parent = nullptr, bool onlyPositiveNumbers = false);
    double getValue() const;
    bool hasValue() const;

signals:

private:
    QLabel* label;
    QLineEdit* lineEdit;
};

#endif // DOUBLENUMBERPICKER_H
