#ifndef MYAPPLICATION_H
#define MYAPPLICATION_H

#include "include/FunctionSample.h"
#include "include/FunctionValueConsumer.h"
#include "include/FunctionValueProducer.h"

#include <QCoreApplication>
#include <QHash>
#include <QMutex>
#include <QVariant>


namespace basicQt {

/**
 * @brief The MyApplication class is the main application that handles signals
 * and events in the main thread.
 */
class MyApplication :
        public QCoreApplication {
    Q_OBJECT

private:
    /**
     * @brief m_minProducerCount is the minimum amount of producers that should
     * work (if possible).
     */
    unsigned m_minProducerCount = 2;

    /**
     * @brief m_producer is a producer that generates function values from a
     * given FunctionSample
     * @see FunctionSample
     */
    FunctionValueProducer m_producer;
    /**
     * @brief m_consumer is a consumer that uses the function values created
     * from m_producer
     * @see m_producer
     */
    FunctionValueConsumer m_consumer;

    /**
     * @brief m_input is a list of FunctionSamples that the producer requires.
     * This is used to emulate asynchronous (user) input.
     * The current implementation just takes input from here if required.
     */
    QList<FunctionSample> m_input;
    /**
     * @brief m_products is a hash that maps input to its product.
     * If no product is avaible yet, the input isn't contained yet aswell.
     */
    QHash<FunctionSample, QVariant> m_products;
    /**
     * @brief m_productsMutex is a mutex for concurrent access to m_products
     */
    QMutex m_productsMutex;

    /**
     * @brief m_finishedConsumers is the amount of consumers that finished.
     * This is used to keep track, when the application can finish.
     */
    int m_finishedConsumers = 0;

    /**
     * @brief parseCommandLineArguments takes the command line arguments and
     * parses them. The current implementation just prints them to stderr in
     * a properly formatted fashion.
     * @param argc is the amount of arguments passed to the application.
     * Restiction: Should not be less then 1.
     * @param argv is the array of arguments actually given to the program as
     * c-style strings. Note: argv[0] is always the fully qualified path under
     * which the application was called.
     */
    void parseCommandLineArguments();

public:
    /**
     * @brief MyApplication is the only constructor of this class
     * This will connect the applications signals to all receivers.
     * @param argc is the amount of command line arguments given to the program
     * @param argv is a pointer to the c-style command line argument strings
     */
    MyApplication(int argc, char** argv);
    ~MyApplication() = default;

    /**
     * @brief addProduct registers a prodcut ot the application
     * This funciton is thread-safe.
     * @param product should be registered (and later consumed)
     * @param source is the input that was used to create the product
     */
    void addProduct(QVariant product, FunctionSample source);
    /**
     * @brief setup will configure the application properly before usage.
     * This function has to be called before exec can be called.
     * It registers all MetaTypes to Qt so that they can be used in signals and
     * It will make sure that there are enough producers spawned.
     */
    void setup();

signals:
    /**
     * @brief signal_producersRequired will be emitted once the application
     * decides that not enough producers are available.
     */
    void signal_producersRequired();

    /**
     * @brief signal_dataAvailable will be emitted once a producer worker has
     * created new data
     * @param data are the data to be handed to a consumer worker.
     * @param source is the input sample that created the data
     */
    void signal_dataAvailable(QVariant data, FunctionSample source);

public slots:
    /**
     * @brief slot_producerFinished notifies the application that a producer finished
     * This will signal the producer to create more data if necessary
     * This will also signal the consumer to use the freshly produced data if avaible
     */
    void slot_producerFinished();

    /**
     * @brief slot_consumerFinished notifies the applicatoin that a consumer finished
     * If as many cosumers finished as the amount of input data the application will finish
     */
    void slot_consumerFinished();
};

}


#endif // MYAPPLICATION_H
