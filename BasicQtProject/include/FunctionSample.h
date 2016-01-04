#ifndef FUNCTIONSAMPLE_H
#define FUNCTIONSAMPLE_H

#include "include/FunctionTypes.h"

#include <QObject>
#include <QString>
#include <QTextStream>


namespace basicQt {

/**
 * @brief The FunctionSample class contains information that is needed
 * for sampling a function.
 */
class FunctionSample :
        public QObject {
    Q_OBJECT

private:
    /**
     * @brief m_function points to the function that should be sampled.
     */
    mathFunction m_function;
    /**
     * @brief m_name is the name of the functoin to be sampled.
     */
    QString m_name;
    /**
     * @brief m_rangeBegin is the inclusive start point of the sampling.
     */
    double m_rangeBegin;
    /**
     * @brief m_rangeEnd is the inclusive end point of the sampling.
     */
    double m_rangeEnd;
    /**
     * @brief m_pointAmount is the amount of points that will be sampled
     * in equivalent distance to each other.
     */
    unsigned m_pointAmount;

public:
    /**
     * @brief FunctionSample is the only normal constructor of this class
     * @param function initialises m_function
     * @param name initialies m_name
     * @param rangeBegin initialises m_rangeBegin
     * Restriction: Must be smaller than rangeEnd
     * @param rangeEnd initialises m_rangeEnd
     * Restriction: Must be bigger than rangeBegin
     * @param pointAmount initialises m_pointAmount
     * Restriciont: Must be bigger than 1
     */
    FunctionSample(mathFunction function, QString name = "f",
                   double rangeBegin = 0, double rangeEnd = 1,
                   unsigned pointAmount = 1000000);
    /**
     * @brief FunctionSample is the copy constructor and is used by Qt
     * @param other is the function sample that should be copied
     */
    FunctionSample(const FunctionSample & other);
    /**
     * @brief operator = is the copy assignment operator and is used by Qt
     * @param other is the function sample that should be copied
     * @return new function sample
     */
    FunctionSample& operator=(const FunctionSample & other);

    /**
     * @brief function is the getter for m_function
     * @return m_function
     */
    mathFunction function() const {
        return m_function;
    }
    /**
     * @brief name is the getter for m_name
     * @return m_name
     */
    QString name() const {
        return m_name;
    }
    /**
     * @brief rangeBegin is the getter for m_rangeBegin
     * @return m_rangeBegin
     */
    double rangeBegin() const {
        return m_rangeBegin;
    }
    /**
     * @brief rangeEnd is the getter for m_rangeEnd
     * @return m_rangeEnd
     */
    double rangeEnd() const {
        return m_rangeEnd;
    }
    double pointAmount() const {
        return m_pointAmount;
    }

    /**
     * @brief qHash returns a hash of an instance of this class.
     * This is used by Qt for the QHash data structure
     * @param f is the function sample that should be hashed
     * @return a hash of f
     */
    friend uint qHash(const FunctionSample & f);
    /**
     * @brief operator == compares to FunctionSamples
     * @param f1 is the first function sample
     * @param f2 is the second function sample
     * @return true if the function samples are equal, false otherwise
     */
    friend bool operator==(const FunctionSample & f1, const FunctionSample & f2);
    /**
     * @brief operator << is the output operator for QTextStream
     * @param stream is the stream where the output should go.
     * This has to be an lvalue.
     * @param f is the function sample that should be written to stream.
     * @return the stream after it was written to it
     */
    friend QTextStream & operator<<(QTextStream & stream, const FunctionSample & f);
};

}


#endif // FUNCTIONSAMPLE_H
