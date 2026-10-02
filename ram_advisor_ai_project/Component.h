// Component.h
// TCS307 Unit 3: Inheritance (base class), access specifiers
// TCS307 Unit 1: data types, user-defined functions
#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>

// ---- Base class for every hardware component in the system ----
class Component {
protected:
    std::string name;
    static int totalComponentsCreated;   // TCS307 Unit 2: static data member

public:
    Component(const std::string& n) : name(n) {
        totalComponentsCreated++;
    }

    virtual ~Component() {}   // TCS307 Unit 4: virtual destructor (base of a polymorphic hierarchy)

    std::string getName() const { return name; }

    static int getTotalComponents() { return totalComponentsCreated; }

    virtual void describe() const = 0;   // TCS307 Unit 4: pure virtual -> Component is abstract
};

inline int Component::totalComponentsCreated = 0;   // inline (C++17) avoids multiple-definition across .cpp files

// ---- Mixin-style interface used for multiple inheritance (TCS307 Unit 3) ----
class Loggable {
public:
    virtual std::string logTag() const = 0;
    virtual ~Loggable() {}
};

#endif
