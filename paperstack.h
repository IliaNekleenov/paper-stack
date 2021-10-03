#ifndef POSITIONSSTACK_H
#define POSITIONSSTACK_H

#include "positionedpaperobject.h"
#include <ostream>

class PaperStack
{    
    class StackElement {
        std::shared_ptr<PositionedPaperObject> value;
        std::shared_ptr<StackElement> lower{nullptr};

    public:
        StackElement() = delete;
        StackElement(const std::shared_ptr<PositionedPaperObject> _value);
        StackElement(const std::shared_ptr<PositionedPaperObject> _value, const std::shared_ptr<StackElement> _lower);
        bool hasLowerElement() const;
        const std::shared_ptr<StackElement>& lowerElement() const;
        const std::shared_ptr<PositionedPaperObject>& getValue() const;
        std::shared_ptr<PositionedPaperObject>& getValue();
    };

    std::shared_ptr<StackElement> top{nullptr};
    size_t size{0};

    QJsonObject createJsonObject(const std::shared_ptr<PositionedPaperObject>& element);

public:
    PaperStack() = default;
    PaperStack(const PaperStack &other);

    ~PaperStack() = default;

    std::shared_ptr<PositionedPaperObject>& topElement();
    const std::shared_ptr<PositionedPaperObject>& topElement() const;

    std::shared_ptr<StackElement>& iterator();
    const std::shared_ptr<StackElement>& iterator() const;

    void add(const std::shared_ptr<PositionedPaperObject>& newElement);
    void emplace(std::shared_ptr<PositionedPaperObject>&& newElement);
    void pop();
    void addAll(const PaperStack& other);

    size_t getSize() const;

    void clear();

    void writeToFile(const QString& fileName) const;
    static PaperStack readFromFile(const QString& fileName);

    bool isInBalance() const;

    bool operator==(const PaperStack& rhs);
    bool operator!=(const PaperStack& rhs);
};

std::ostream& operator<<(std::ostream& out, const PaperStack& stack);

#endif // POSITIONSSTACK_H
