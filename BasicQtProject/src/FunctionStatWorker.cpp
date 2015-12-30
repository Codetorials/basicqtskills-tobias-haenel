#include "include/FunctionStatWorker.h"
#include "include/FunctionValueConsumer.h"
#include "include/MyApplication.h"
#include "include/FunctionValues.h"

#include <QMutex>
#include <QMutexLocker>
#include <QTextStream>
#include <QDebug>
#include <QTime>
#include <QObject>

using namespace basicQt;

FunctionStatWorker::FunctionStatWorker(FunctionValues fp, FunctionValueConsumer *consumer) :
        Worker(),
        m_consumer {consumer},
        m_fp {fp} {
}

void
FunctionStatWorker::run() {
    qDebug() << QTime::currentTime().msecsSinceStartOfDay() << "- running" << this;
    static QMutex outputMutex;
    double average = 0;

    for (auto point = m_fp->begin(); point != m_fp->end(); ++point) {
        average += point->y;
    }
    average /= (double) m_fp->size();

    //QMutexLocker ml {&outputMutex};
    if (m_consumer) {
        MyApplication *app = qobject_cast<MyApplication *>(m_consumer->parent());
        if (app) {
            // producer has to be connected first, because the workerCount has to be updated before the application gets the signal
            QObject::connect(this, &FunctionStatWorker::signal_finished, app, &MyApplication::slot_consumerFinished, Qt::QueuedConnection);
            emit signal_finished();
            qDebug() << QTime::currentTime().msecsSinceStartOfDay() << \
                "- finished" << this << "of" << m_consumer << "with result:" << average;
            QObject::disconnect(this);
        } else {
            qWarning() << "Warning:" << FunctionStatWorker::staticMetaObject.className() << "doesn't have" << \
                          MyApplication::staticMetaObject.className() << "as grandparent";
        }
    } else {
        qWarning() << "Warning:" << FunctionStatWorker::staticMetaObject.className() << "doesn't have" << \
                      FunctionValueConsumer::staticMetaObject.className() << "as parent";
    }

}
