#include "include/FunctionSample.h"

#include <QHash>


namespace basicQt {

    uint qHash(const FunctionSample & f) {
        // use a cast since pointer is unique and can't be casted by qHash
        return reinterpret_cast<ulong>(f.m_function) ^ \
           ::qHash(f.m_name) ^ \
           ::qHash(f.m_pointAmount) ^ \
           ::qHash(f.m_rangeBegin) ^ \
           ::qHash(f.m_rangeEnd);
    }

    bool operator==(const FunctionSample & f1, const FunctionSample & f2) {
        // function name is irrelevant for comparison
        return f1.m_function == f2.m_function and \
           f1.m_rangeBegin == f2.m_rangeBegin and \
           f1.m_rangeEnd == f2.m_rangeEnd and \
           f1.m_pointAmount == f2.m_pointAmount;
    }

    QTextStream & operator<<(QTextStream & stream, const FunctionSample & f) {
    return stream << f.m_name << "(x) [" << f.m_rangeBegin << ", " << \
         f.m_rangeEnd << "] ... sampled with " << f.m_pointAmount << " points";
    }

}

using namespace basicQt;

FunctionSample::FunctionSample(mathFunction function, QString name,
                               double rangeBegin, double rangeEnd,
                               unsigned pointAmount) :
    QObject(),
    m_function {function},
    m_name {name},
    m_rangeBegin {rangeBegin},
    m_rangeEnd {rangeEnd},
    m_pointAmount {pointAmount} {
        Q_ASSERT(rangeBegin < rangeEnd);
        Q_ASSERT(pointAmount > 1);
}

FunctionSample::FunctionSample(const FunctionSample & other) :
    QObject(),
    m_function {other.m_function},
    m_name {other.m_name},
    m_rangeBegin {other.m_rangeBegin},
    m_rangeEnd {other.m_rangeEnd},
    m_pointAmount {other.m_pointAmount} {}

FunctionSample& FunctionSample::operator=(const FunctionSample & other) {
    m_function = other.m_function;
    m_name = other.m_name;
    m_rangeBegin = other.m_rangeBegin;
    m_rangeEnd = other.m_rangeEnd;
    m_pointAmount = other.m_pointAmount;
    return *this;
}
