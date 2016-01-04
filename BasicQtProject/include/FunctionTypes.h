#ifndef FUNCTIONPOINTS_H
#define FUNCTIONPOINTS_H

#include <QList>
#include <QObject>
#include <QSharedPointer>


namespace basicQt {

typedef double (*mathFunction) (double);

/**
 * @brief The FunctionValue struct represents a point on a function
 * This is a struct (all members public) because there are no
 * restricions on all members
 */
struct FunctionValue {
    double x = 0;
    double y = 0;

    /**
     * @brief FunctionValue is a constructor that creates a point
     * based on the evaluation of a function
     * @param f is the function used to calculated y
     * @param x is argument of f
     */
    FunctionValue(mathFunction f, double x) :
        x{x},
        y{f(x)} {}

    FunctionValue(double x, double y) :
        x(x),
        y(y) {}
};

typedef QSharedPointer<QList<FunctionValue>> FunctionValues;

}

Q_DECLARE_METATYPE(basicQt::FunctionValues)


#endif // FUNCTIONPOINTS_H
