#include "include/FunctionStatWorker.h"
#include "include/MyApplication.h"

#include <QDebug>
#include <QMutexLocker>
#include <QTextStream>
#include <QTime>
#include <QtGlobal>


using namespace basicQt;

FunctionStatWorker::FunctionStatWorker(FunctionValues product,
                                       FunctionSample funcSample,
                                       FunctionValueConsumer *consumer) :
        Worker(),
        m_consumer {consumer},
        m_funcValues {product},
        m_funcSample {funcSample} {}

void
FunctionStatWorker::run() {
    qDebug() << QTime::currentTime().msecsSinceStartOfDay() << "- running" << this;

    double average = 0;
    for (auto point = m_funcValues->begin(); point != m_funcValues->end(); ++point) {
        average += point->y;
    }
    average /= (double) m_funcValues->size();

    // get the app (parent of the consumer that created this worker)
    Q_ASSERT(m_consumer != nullptr);
    MyApplication *app = qobject_cast<MyApplication *>(m_consumer->parent());
    Q_ASSERT(app != nullptr);

    QObject::connect(this, &FunctionStatWorker::signal_finished,
                     app, &MyApplication::slot_consumerFinished,
                     Qt::QueuedConnection);
    emit signal_finished();
    qDebug() << QTime::currentTime().msecsSinceStartOfDay() << \
                "- finished" << this << "of" << m_consumer;

    // protect output since concurrent writting to stdout could overlap
    static QMutex outputMutex;
    QMutexLocker ml {&outputMutex};
    QTextStream output {stdout};
    output << m_funcSample << " - results:" << endl << \
              "    arithmetic mean: " << average << endl;

    QObject::disconnect(this);

}
