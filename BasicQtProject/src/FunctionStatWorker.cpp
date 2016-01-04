#include "include/FunctionStatWorker.h"
#include "include/MyApplication.h"

#include <QDebug>
#include <QMutexLocker>
#include <QTextStream>
#include <QTime>
#include <QtGlobal>
#include <QtMath>


using namespace basicQt;

FunctionStatWorker::FunctionStatWorker(FunctionValues product,
                                       FunctionSample funcSample,
                                       FunctionValueConsumer *consumer) :
        Worker(),
        m_consumer {consumer},
        m_funcValues {product},
        m_funcSample {funcSample} {}

// statistical helper functions
static inline double abs(double x) {
    return (x < 0) ? -x : x;
}

static inline double min(double a, double b) {
    return (a < b) ? a : b;
}

static inline double max(double a, double b) {
    return (a > b) ? a : b;
}

void
FunctionStatWorker::run() {
    qDebug() << QTime::currentTime().msecsSinceStartOfDay() << "- running" << this;

    /* calculation */
    double average = 0;
    double absAverage = 0;
    double length = 0;
    double absArea = 0;
    for (int i = 0; i < m_funcValues->size(); ++i) {
        double x_curr = (*m_funcValues)[i].x;
        double y_curr = (*m_funcValues)[i].y;
        average += y_curr;
        absAverage += abs(y_curr);

        if (i == 0) {
            continue;
        }

        double x_prev = (*m_funcValues)[i - 1].x;
        double y_prev = (*m_funcValues)[i - 1].y;

        length += qSqrt((x_prev - x_curr) * (x_prev - x_curr) + \
                        (y_prev - y_curr) * (y_prev - y_curr));

        absArea += (x_curr - x_prev) * 0.5 * (max(abs(y_prev), abs(y_curr)) + \
                                              min(abs(y_prev), abs(y_curr)));
    }
    average /= (double) m_funcValues->size();
    absAverage /= (double) m_funcValues->size();

    /* notification */
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
              "    mean      : " << average << endl << \
              "    mean (abs): " << absAverage << endl << \
              "    length    : " << length << endl << \
              "    area (abs): " << absArea << endl;


    QObject::disconnect(this);
}
