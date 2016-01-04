#ifndef CONSUMER_H
#define CONSUMER_H

#include "include/FunctionSample.h"

#include <QObject>
#include <QThreadPool>
#include <QVariant>


namespace basicQt {

class FunctionValueConsumer :
        public QObject {
    Q_OBJECT

private:
    /**
     * @brief m_threadPool manages the workers that consume function values
     */
    QThreadPool m_threadPool;

public:
    explicit FunctionValueConsumer(QObject *parent = 0);

public slots:
    /**
     * @brief slot_consume will spawn a worker that consumes a given product
     * @param product will be consumed
     * In the current implementation only FunctionValues can be handled
     * @param funcSample is the FunctionSample that created the product
     * In the current implementation this is only used for result output
     * @see FunctionValues
     */
    void slot_consume(QVariant product, FunctionSample funcSample);
};

}


#endif // CONSUMER_H
