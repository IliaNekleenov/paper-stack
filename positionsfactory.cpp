#include "positionsfactory.h"

std::shared_ptr<PositionedPaperObject> PositionsFactory::fromJsonObject(const QJsonObject &jsonObject) {
    std::shared_ptr<PositionedPaperObject> result;
    auto type = static_cast<PositionedPaperObjectType>(jsonObject.value("type").toInt());
    switch (type) {
    case PAPER_SHEET: {
        auto paper = std::make_shared<PaperSheet>();
        paper->setThickness(jsonObject.value("thickness").toDouble());
        paper->setWidth(jsonObject.value("width").toDouble());
        paper->setHeight(jsonObject.value("height").toDouble());
        result = paper;
        break;
    }
    case PAPER_PLATE: {
        auto plate = std::make_shared<PaperPlate>();
        plate->setThickness(jsonObject.value("thickness").toDouble());
        plate->setRadius(jsonObject.value("radius").toDouble());
        result = plate;
        break;
    }
    }
    result->setX(jsonObject.value("x").toDouble());
    result->setY(jsonObject.value("y").toDouble());
    result->setThickness(jsonObject.value("thickness").toDouble());
    return result;
}
