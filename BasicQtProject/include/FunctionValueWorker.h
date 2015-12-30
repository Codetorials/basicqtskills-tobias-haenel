#ifndef FUNCTIONPOINTSWORKER_H
#define FUNCTIONPOINTSWORKER_H

#include "include/Worker.h"
#include "include/FunctionValues.h"
#include "include/FunctionValueProducer.h"

#include <QObject>
#include <QVariant>

namespace basicQt {

class FunctionValueWorker :
        public Worker {
    Q_OBJECT

private:
    FunctionValueProducer *m_producer = nullptr;
    function m_f;
    unsigned m_pointAmount = 10000000;

public:
    explicit FunctionValueWorker(function f, FunctionValueProducer *producer = 0);

    void run() override;

signals:
    void signal_finished();
};

}


#endif // FUNCTIONPOINTSWORKER_H
