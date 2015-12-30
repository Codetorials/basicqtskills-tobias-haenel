/*
 * TODO:
 * More auto-generated code...
 *
 * 1) Fix formatting and namespacing
 * 2) Make sure the application is the consumers parent
 * 3) Listen for signal_dataAvailable
 * 4) If new data is available create a new consumer worker and let it handle the data
 *      Hint: QThreadPool
 *
 * Restictions:
 * Do not have just one worker idling around, waiting for data.
 * Once the workers are done, they shall perish.
 */

#ifndef CONSUMER_H
#define CONSUMER_H

#include <QObject>
#include <QThreadPool>
#include <QVariant>

namespace basicQt {

class FunctionValueConsumer :
        public QObject {
    Q_OBJECT

private:
    QThreadPool m_workerPool;

public:
    explicit FunctionValueConsumer(QObject *parent = 0);

public slots:
    void slot_consume(QVariant product);
};

}


#endif // CONSUMER_H
