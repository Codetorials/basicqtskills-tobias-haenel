#include "include/FunctionValueWorker.h"
#include "include/FunctionValueProducer.h"
#include "include/FunctionValues.h"
#include "include/MyApplication.h"

#include <QList>
#include <QSharedPointer>
#include <QMetaType>
#include <QObject>
#include <QVariant>
#include <QDebug>
#include <QTime>

using namespace basicQt;

FunctionValueWorker::FunctionValueWorker(function f, FunctionValueProducer *producer) :
        Worker(),
        m_producer {producer},
        m_f {f} {
}

void
FunctionValueWorker::run() {
    qDebug() << QTime::currentTime().msecsSinceStartOfDay() << "- running" << this;
    FunctionValues result {new QList<FunctionValue>()};
    result->reserve(m_pointAmount);

    for (unsigned i = 0; i < m_pointAmount; ++i) {
        double x = (double) i / (m_pointAmount - 1);
        result->append(FunctionValue(m_f, x));
    }

    if (m_producer) {
        MyApplication *app = qobject_cast<MyApplication *>(m_producer->parent());
        if (app) {
            app->addProduct(QVariant::fromValue(result));
            // producer has to be connected first, because the workerCount has to be updated before the application gets the signal
            QObject::connect(this, &FunctionValueWorker::signal_finished, m_producer, &FunctionValueProducer::slot_handleFinishedWorker, Qt::QueuedConnection);
            QObject::connect(this, &FunctionValueWorker::signal_finished, app, &MyApplication::slot_producerFinished, Qt::QueuedConnection);
            emit signal_finished();
            qDebug() << QTime::currentTime().msecsSinceStartOfDay() << \
                "- finished" << this << "of" << m_producer;
            QObject::disconnect(this);
        } else {
            qWarning() << "Warning: FunctionPointsWorker doesn't have MyApplication as grandparent";
        }
    } else {
        qWarning() << "Warning: FunctionPointsWorker doesn't have FunctionValueProducer as parent";
    }

}
