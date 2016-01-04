#ifndef FUNCTIONSTATSWORKER_H
#define FUNCTIONSTATSWORKER_H

#include "include/FunctionSample.h"
#include "include/FunctionValueConsumer.h"
#include "include/Worker.h"

#include <QObject>


namespace basicQt {

/**
 * @brief The FunctionStatWorker class is a worker that consumes
 * function values and calculates some statistics of them.
 */
class FunctionStatWorker :
        public Worker {
    Q_OBJECT

private:
    /**
     * @brief m_consumer points to the consumer that spawned this worker
     */
    FunctionValueConsumer *m_consumer = nullptr;
    /**
     * @brief m_funcValues are the function values that are used for the
     * statistical calculations.
     */
    FunctionValues m_funcValues;
    /**
     * @brief m_funcSample is the function sample that was the origin of
     * the function values.
     */
    FunctionSample m_funcSample;

public:
    /**
     * @brief FunctionStatWorker is the only constructor of this class.
     * @param product will be consumed
     * @param funcSample is the source/origin of the product
     * @param consumer points to the consumer who spawned this thread
     */
    explicit FunctionStatWorker(FunctionValues product,
                                FunctionSample funcSample,
                                FunctionValueConsumer *consumer);

    /**
     * @brief run is the method that does the statistical calculations
     * and prints it result to stdout.
     */
    void run() override;

signals:
    /**
     * @brief signal_finished will be send to the application when the
     * calculations of run are done and printed to stdout.
     */
    void signal_finished();
};

}


#endif // FUNCTIONSTATSWORKER_H
