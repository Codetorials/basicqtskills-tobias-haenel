#ifndef PRODUCER_H
#define PRODUCER_H

#include "include/FunctionSample.h"

#include <QObject>
#include <QQueue>
#include <QThreadPool>


namespace basicQt {

class FunctionValueProducer :
        public QObject {
    Q_OBJECT

private:
    /**
     * @brief m_threadPool manages the workers that produce function values
     */
    QThreadPool m_threadPool;
    /**
     * @brief m_workerCount is the current amount of workers that are active
     */
    unsigned m_workerCount = 0;
    /**
     * @brief m_funcSamples contains the input of this producer
     */
    QQueue<FunctionSample> m_funcSamples;

public:
    explicit FunctionValueProducer(QObject *parent = 0);

    /**
     * @brief addFunctionSample adds new input to the end of the queue
     * This function sample will be used if slot_produce was activated enough
     * @param funcSample is the function sample that will be added and later
     * on used for calculation of function values
     */
    void addFunctionSample(FunctionSample funcSample);
    /**
     * @brief workerCount is the getter for m_workerCount
     * @return amount of workers active when this function was called
     */
    unsigned workerCount() {
        return m_workerCount;
    }

public slots:
    /**
     * @brief slot_produce will spawn a new FunctionValueWorker if the input
     * queue is not empty
     */
    void slot_produce();
    /**
     * @brief slot_handleFinishedWorker updates the workerCount if this slot
     * is activated.
     */
    void slot_handleFinishedWorker();
};

}


#endif // PRODUCER_H
