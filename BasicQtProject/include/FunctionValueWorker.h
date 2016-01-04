#ifndef FUNCTIONPOINTSWORKER_H
#define FUNCTIONPOINTSWORKER_H

#include "include/FunctionSample.h"
#include "include/FunctionValueProducer.h"
#include "include/Worker.h"

#include <QObject>
#include <QVariant>


namespace basicQt {

/**
 * @brief The FunctionValueWorker class is a worker that produces function
 * values.
 */
class FunctionValueWorker :
        public Worker {
    Q_OBJECT

private:
    /**
     * @brief m_producer points to the producer who spawned this worker.
     * This has to be set to inform the producer if this worker finished
     */
    FunctionValueProducer *m_producer = nullptr;
    /**
     * @brief m_sample is the FunctionSample that has the information about
     * the function and how the function values should be created.
     */
    FunctionSample m_sample;

public:
    /**
     * @brief FunctionValueWorker is the only constructor of this class
     * @param m_sample the FunctionSample used for creating the function values
     * This sample will later be used to identify the product (function values)
     * @param producer
     */
    explicit FunctionValueWorker(FunctionSample m_sample, FunctionValueProducer *producer);

    /**
     * @brief run is the method that does the calculations and passes the
     * calculated data to the application.
     */
    void run() override;

signals:
    /**
     * @brief signal_finished will be send if the calculations of run are done
     * and data is registered to the application.
     */
    void signal_finished();
};

}


#endif // FUNCTIONPOINTSWORKER_H
