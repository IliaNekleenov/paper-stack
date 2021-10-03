#include "paperstack.h"
#include <cstdlib>
#include <stdexcept>
#include <QJsonArray>
#include <QJsonDocument>
#include <QFile>
#include "papersheet.h"
#include "paperplate.h"
#include "positionsfactory.h"

PaperStack::PaperStack(const PaperStack &other) {
    PaperStack buffer;
    buffer.addAll(other);
    addAll(buffer);
}

std::shared_ptr<PositionedPaperObject> &PaperStack::topElement() {
    return top->getValue();
}

const std::shared_ptr<PositionedPaperObject> &PaperStack::topElement() const {
    return top->getValue();
}

const std::shared_ptr<PaperStack::StackElement> &PaperStack::iterator() const {
    return top;
}

std::shared_ptr<PaperStack::StackElement> &PaperStack::iterator() {
    return top;
}

void PaperStack::add(const std::shared_ptr<PositionedPaperObject> &newElement) {
    if(top == nullptr) {
        top = std::make_shared<StackElement>(newElement);
    } else {
        auto previousTop = top;
        top = std::make_shared<StackElement>(newElement, previousTop);
    }
    size++;
}

void PaperStack::emplace(std::shared_ptr<PositionedPaperObject> &&newElement) {
    if(size == 0) {
        top = std::make_shared<StackElement>(std::move(newElement));
    } else {
        auto previousTop = top;
        top = std::make_shared<StackElement>(std::move(newElement), previousTop);
    }
    size++;
}

void PaperStack::pop() {
    if(size == 0) {
        throw std::out_of_range("pop from empty stack");
    }
    top = top->lowerElement();
    size--;
}

void PaperStack::addAll(const PaperStack &other) {
    auto current = other.iterator();
    while(current != nullptr) {
        add(current->getValue());
        current = current->lowerElement();
    }
}

size_t PaperStack::getSize() const {
    return size;
}

void PaperStack::clear() {
    top = nullptr;
    size = 0;
}

void PaperStack::writeToFile(const QString &fileName) const {
    QJsonArray jsonArray;
    auto element = iterator();
    while(element != nullptr) {
        jsonArray.append(element->getValue()->toJsonObject());
        element = element->lowerElement();
    }
    QJsonDocument jsonDocument(jsonArray);
    auto bytes = jsonDocument.toJson();
    QFile file(fileName);
    file.open(QFile::WriteOnly);
    file.write(bytes);
}

PaperStack PaperStack::readFromFile(const QString &fileName) {
    QFile file(fileName);
    file.open(QFile::ReadOnly);
    QJsonParseError parseError;
    auto jsonDocument = QJsonDocument::fromJson(file.readAll(), &parseError);
    if(parseError.error != QJsonParseError::NoError) {
        throw std::runtime_error("could not parse json");
    }
    auto jsonArray = jsonDocument.array();
    PaperStack stack;
    for(int i = jsonArray.size() - 1; i >= 0; i--) {
        stack.add(PositionsFactory::fromJsonObject(jsonArray.at(i).toObject()));
    }
    return stack;
}

bool PaperStack::isInBalance() const {
    if(size == 0) {
        return true;
    }
    auto element = iterator();
    auto previousElement = element;
    double xCenter = 0;
    double yCenter = 0;
    double totalVolume = 0;
    while(element != nullptr) {
        previousElement = element;
        auto paperObject = element->getValue();
        // no need to use density because all objects are made of paper
        // that's why mass can be replaced with volume
        auto volume = paperObject->calculateVolume();
        xCenter += volume * paperObject->getX();
        yCenter += volume * paperObject->getY();
        totalVolume += volume;
        element = element->lowerElement();
    }
    xCenter /= totalVolume;
    yCenter /= totalVolume;
    auto bottomElement = previousElement->getValue();
    return bottomElement->isPointInside(xCenter, yCenter);
}

bool PaperStack::operator==(const PaperStack &rhs) {
    if(size != rhs.size) {
        return false;
    }
    auto lhsElement = iterator();
    auto rhsElement = rhs.iterator();
    while(lhsElement != nullptr) {
        if(*(lhsElement->getValue().get()) != *(rhsElement->getValue().get())) {
            return false;
        }
        lhsElement = lhsElement->lowerElement();
        rhsElement = rhsElement->lowerElement();
    }
    return true;
}

bool PaperStack::operator!=(const PaperStack &rhs) {
    return !(*this == rhs);
}

PaperStack::StackElement::StackElement(const std::shared_ptr<PositionedPaperObject> _value): value(_value) {}

PaperStack::StackElement::StackElement(const std::shared_ptr<PositionedPaperObject> _value, const std::shared_ptr<PaperStack::StackElement> _lower):
    value(_value), lower(_lower) {}

bool PaperStack::StackElement::hasLowerElement() const {
    return lower != nullptr;
}

const std::shared_ptr<PaperStack::StackElement> &PaperStack::StackElement::lowerElement() const {
    return lower;
}

const std::shared_ptr<PositionedPaperObject> &PaperStack::StackElement::getValue() const {
    return value;
}

std::shared_ptr<PositionedPaperObject> &PaperStack::StackElement::getValue() {
    return value;
}

std::ostream &operator<<(std::ostream &out, const PaperStack &stack) {
    size_t level = stack.getSize();
    auto iterator = stack.iterator();
    while(iterator != nullptr) {
        out << level-- << ": [" << iterator->getValue()->description().toStdString() << "]\n";
        iterator = iterator->lowerElement();
    }
    return out;
}











