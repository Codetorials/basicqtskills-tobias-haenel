#ifndef FUNCTIONSTATSWORKER_H
#define FUNCTIONSTATSWORKER_H

#include "include/Worker.h"
#include "include/FunctionValues.h"
#include "include/FunctionValueConsumer.h"

#include <QObject>
#include <QVariant>
#include <QMutex>

namespace basicQt {

class FunctionStatWorker :
        public Worker {
    Q_OBJECT

private:
    FunctionValueConsumer *m_consumer = nullptr;
    FunctionValues m_fp;

public:
    explicit FunctionStatWorker(FunctionValues p, FunctionValueConsumer *consumer = 0);

    void run() override;

signals:
    void signal_finished();
};

}


#endif // FUNCTIONSTATSWORKER_H
