/*
 * TODO TASK:
 * Properly subclass this into producer and consumer worker classes.
 * Each of these can have different strategies how to do stuff.
 *
 * All data passed between workers are by convention of the type QVariant.
 *
 * Producer worker examples:
 * - ConstantStringProducer (just produces --- you guessed it...)
 * - CounterProducer (counts up a number and issues it as data)
 * - JsonProducer (produces a QJsonObject)
 *
 * Consumer worker examples:
 * - PrintConsumer (Just prints, what it gets)
 * - FileConsumer (Appends everything it gets to a file)
 * - SumConsumer (Filters out the numbers and sums them up)
 *
 * General consideration:
 * How to set up signals and slots?
 * How to deal with different content types of QVariant?
 * How to keep information alive over multiple runs of the same consumer?
 * (Multiple solutions are possible)
 */

#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QRunnable>

namespace basicQt {

class Worker :
        public QObject,
        public QRunnable {
    Q_OBJECT

public:
    explicit Worker();

    /*
     * This method is inherited from QRunnable and will be executed in a seperate thread.
     * Override this to achieve some actual results.
     * Remember to use some proper locking if necessary.
     */
    virtual void run();
};

}
#endif // WORKER_H
