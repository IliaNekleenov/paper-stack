#include "tests.h"
#include <assert.h>
#include "positionedpaperobject.h"
#include "papersheet.h"
#include "paperplate.h"
#include "paperstack.h"
#include <iostream>
#include <QFile>

void assertDoubleEquals(double expected, double actual) {
    assert(expected - actual < 1e-6);
}


// PaperSheet tests

void testPaperSheetDefaultConstructor() {
    PaperSheet defaultPaper;
    assert(defaultPaper.getType() == PositionedPaperObjectType::PAPER_SHEET);
    assertDoubleEquals(0, defaultPaper.getX());
    assertDoubleEquals(0, defaultPaper.getY());
    assertDoubleEquals(0.01, defaultPaper.getThickness());
    assertDoubleEquals(29.7, defaultPaper.getWidth());
    assertDoubleEquals(21, defaultPaper.getHeight());
}

void testPaperSheetParametrizedConstructor(double x, double y, double thickness, double width, double height) {
    PaperSheet initializedPaper(x, y, thickness, width, height);
    assert(initializedPaper.getType() == PositionedPaperObjectType::PAPER_SHEET);
    assertDoubleEquals(x, initializedPaper.getX());
    assertDoubleEquals(y, initializedPaper.getY());
    assertDoubleEquals(thickness, initializedPaper.getThickness());
    assertDoubleEquals(width, initializedPaper.getWidth());
    assertDoubleEquals(height, initializedPaper.getHeight());
}

void testPaperSheetCopyConstructor(double x, double y, double thickness, double width, double height) {
    PaperSheet paper(x, y, thickness, width, height);
    PaperSheet copy(paper);
    assert(copy.getType() == PositionedPaperObjectType::PAPER_SHEET);
    assertDoubleEquals(x, copy.getX());
    assertDoubleEquals(y, copy.getY());
    assertDoubleEquals(thickness, copy.getThickness());
    assertDoubleEquals(width, copy.getWidth());
    assertDoubleEquals(height, copy.getHeight());
    assert(copy == paper);
}

void testPaperSheetModificators() {
    PaperSheet paper;
    double newValue = 32;
    paper.setX(newValue);
    assertDoubleEquals(newValue, paper.getX());
    newValue = -12.2;
    paper.setY(newValue);
    assertDoubleEquals(newValue, paper.getY());
    newValue = 233.2;
    paper.setWidth(newValue);
    assertDoubleEquals(newValue, paper.getWidth());
    newValue = 0.05;
    paper.setHeight(newValue);
    assertDoubleEquals(newValue, paper.getHeight());
    newValue = 0.543;
    paper.setThickness(newValue);
    assertDoubleEquals(newValue, paper.getThickness());
}

void testPaperSheetClass() {
    testPaperSheetDefaultConstructor();
    testPaperSheetParametrizedConstructor(324.3, -93.1, 10, 123, 321.09);
    testPaperSheetCopyConstructor(934.5, 858.3, 102, 195.5, 48);
    testPaperSheetModificators();
}


// PaperPlate tests

void testPaperPlateDefaultConstructor() {
    PaperPlate defaultPlate;
    assert(defaultPlate.getType() == PositionedPaperObjectType::PAPER_PLATE);
    assertDoubleEquals(0, defaultPlate.getX());
    assertDoubleEquals(0, defaultPlate.getY());
    assertDoubleEquals(1, defaultPlate.getThickness());
    assertDoubleEquals(25, defaultPlate.getRadius());
}

void testPaperPlateParametrizedConstructor(double x, double y, double thickness, double radius) {
    PaperPlate initializedPlate(x, y, thickness, radius);
    assert(initializedPlate.getType() == PositionedPaperObjectType::PAPER_PLATE);
    assertDoubleEquals(x, initializedPlate.getX());
    assertDoubleEquals(y, initializedPlate.getY());
    assertDoubleEquals(thickness, initializedPlate.getThickness());
    assertDoubleEquals(radius, initializedPlate.getRadius());
}

void testPaperPlateCopyConstructor(double x, double y, double thickness, double radius) {
    PaperPlate plate(x, y, thickness, radius);
    PaperPlate copy(plate);
    assert(copy.getType() == PositionedPaperObjectType::PAPER_PLATE);
    assertDoubleEquals(x, copy.getX());
    assertDoubleEquals(y, copy.getY());
    assertDoubleEquals(thickness, copy.getThickness());
    assertDoubleEquals(radius, copy.getRadius());
    assert(copy == plate);
}

void testPaperPlateModificators() {
    PaperPlate plate;
    double newValue = 32;
    plate.setX(newValue);
    assertDoubleEquals(newValue, plate.getX());
    newValue = -12.2;
    plate.setY(newValue);
    assertDoubleEquals(newValue, plate.getY());
    newValue = 98.54;
    plate.setRadius(newValue);
    assertDoubleEquals(newValue, plate.getRadius());
    newValue = 0.05;
    plate.setThickness(newValue);
    assertDoubleEquals(newValue, plate.getThickness());
}

void testPaperPlateClass() {
    testPaperPlateDefaultConstructor();
    testPaperPlateParametrizedConstructor(324.3, -93.1, 10, 123);
    testPaperPlateCopyConstructor(934.5, 858.3, 102, 195.5);
    testPaperPlateModificators();
}


// PaperStack tests

void testPaperStackClass() {
    PaperStack stack;
    auto bottom = std::make_shared<PaperPlate>();
    auto middle = std::make_shared<PaperSheet>();
    auto top = std::make_shared<PaperPlate>(10, -10, 1, 21.1);
    stack.add(bottom);
    stack.add(middle);
    stack.add(top);
    assert(3 == stack.getSize());
    std::cout << stack;

    auto topElement = stack.topElement();
    auto topIterator = stack.iterator();
    assert(topElement.get()->operator==(*top.get()));
    assert(topIterator->getValue().get()->operator==(*top.get()));

    PaperStack copy(stack);
    assert(copy == stack);
    auto topFromCopy = copy.topElement();
    assert(topFromCopy.get()->operator==(*top.get()));

    QString fileName = "tmp.txt";
    stack.writeToFile(fileName);
    PaperStack fromFile = PaperStack::readFromFile(fileName);
    assert(fromFile == stack);
    assert(fromFile == copy);
    auto topFromFile = fromFile.topElement();
    assert(topFromFile.get()->operator==(*top.get()));
    QFile(fileName).remove();

    auto middleElement = stack.iterator()->lowerElement();
    assert(middleElement->getValue().get()->operator==(*middle.get()));
    stack.pop();
    assert(2 == stack.getSize());
    auto newTopElement = stack.topElement();
    assert(newTopElement.get()->operator==(*middle.get()));
    stack.pop();
    assert(1 == stack.getSize());
    auto bottomElement = stack.topElement();
    assert(bottomElement.get()->operator==(*bottom.get()));
    stack.pop();
    assert(0 == stack.getSize());
}

void testAllClasses() {
    testPaperSheetClass();
    testPaperPlateClass();
    testPaperStackClass();
}














