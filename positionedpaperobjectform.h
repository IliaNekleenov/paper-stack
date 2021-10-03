#ifndef POSITIONEDPAPEROBJECTFORM_H
#define POSITIONEDPAPEROBJECTFORM_H

#include <QWidget>
#include "doublenumberpicker.h"
#include "positionedpaperobject.h"
#include <QGridLayout>
#include <QPushButton>

class PositionedPaperObjectForm : public QWidget
{
    Q_OBJECT
public:
    explicit PositionedPaperObjectForm(const QString& name, QWidget *parent = nullptr);

    virtual std::shared_ptr<PositionedPaperObject> getValue() const = 0;
    double getX() const;
    double getY() const;
    double getThickness() const;

signals:
    void objectSubmitted(const std::shared_ptr<PositionedPaperObject>& object);

public slots:
    void onSubmitButtonClicked();

private:
    DoubleNumberPicker* xPicker;
    DoubleNumberPicker* yPicker;
    DoubleNumberPicker* thicknessPicker;
    QVBoxLayout* mainLayout;
    QPushButton* submitButton;

protected:
    QGridLayout* formLayout;

    virtual bool isFilledCorrectly() const;
};

#endif // POSITIONEDPAPEROBJECTFORM_H
