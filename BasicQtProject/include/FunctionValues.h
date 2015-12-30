#ifndef FUNCTIONPOINTS_H
#define FUNCTIONPOINTS_H

#include <QObject>
#include <QSharedPointer>
#include <QList>
#include <QPair>

namespace basicQt {

typedef double (*function) (double);

struct FunctionValue {
    double x = 0;
    double y = 0;

    FunctionValue(function f, double x) : x{x}, y{f(x)} {}
    FunctionValue(double x, double y) : x(x), y(y) {}
};

typedef QSharedPointer<QList<FunctionValue>> FunctionValues;

}

Q_DECLARE_METATYPE(basicQt::FunctionValues)

#endif // FUNCTIONPOINTS_H
