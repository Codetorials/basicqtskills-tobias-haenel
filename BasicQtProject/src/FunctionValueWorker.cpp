#include "include/FunctionValueWorker.h"
#include "include/MyApplication.h"

#include <QDebug>
#include <QList>
#include <QTime>
#include <QtGlobal>


using namespace basicQt;

FunctionValueWorker::FunctionValueWorker(FunctionSample sample, FunctionValueProducer *producer) :
        Worker(),
        m_producer {producer},
        m_sample {sample} {}

void
FunctionValueWorker::run() {
    qDebug() << QTime::currentTime().msecsSinceStartOfDay() << "- running" << this;
    FunctionValues result {new QList<FunctionValue>()};
    result->reserve(m_sample.pointAmount());

    for (unsigned i = 0; i < m_sample.pointAmount(); ++i) {
        double x = m_sample.rangeBegin() + (m_sample.rangeEnd() - m_sample.rangeBegin()) * \
                   (double) i / (m_sample.pointAmount() - 1);
        result->append(FunctionValue(m_sample.function(), x));
    }

    Q_ASSERT(m_producer != nullptr);
    MyApplication *app = qobject_cast<MyApplication *>(m_producer->parent());
    Q_ASSERT(app != nullptr);

    app->addProduct(QVariant::fromValue(result), m_sample);

    // producer has to be connected first, because
    // the workerCount has to be updated before the application gets the signal
    QObject::connect(this, &FunctionValueWorker::signal_finished,
                     m_producer, &FunctionValueProducer::slot_handleFinishedWorker,
                     Qt::QueuedConnection);
    QObject::connect(this, &FunctionValueWorker::signal_finished,
                     app, &MyApplication::slot_producerFinished,
                     Qt::QueuedConnection);
    emit signal_finished();
    qDebug() << QTime::currentTime().msecsSinceStartOfDay() << \
                "- finished" << this << "of" << m_producer;

    QObject::disconnect(this);

}
