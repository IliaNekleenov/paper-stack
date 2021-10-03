#ifndef POSITIONSFACTORY_H
#define POSITIONSFACTORY_H

#include "positionedpaperobject.h"
#include "papersheet.h"
#include "paperplate.h"

class PositionsFactory
{
public:
    PositionsFactory() = delete;
    static std::shared_ptr<PositionedPaperObject> fromJsonObject(const QJsonObject& jsonObject);
};

#endif // POSITIONSFACTORY_H
