#include "MyApplication.h"

#include <iomanip>
#include <iostream>

#include <QDebug>
#include <QMetaType>
#include <QtGlobal>
#include <QtMath>


using namespace basicQt;

// begin sample functions
double square(double x) {
    return x * x;
}

double id(double x) {
    return x;
}

double sgn(double x) {
    if (x == 0) {
        return 0;
    } else if (x > 0) {
        return 1;
    } else {
        return -1;
    }
}
// end sample functions

MyApplication::MyApplication(int argc, char** argv):
    QCoreApplication(argc, argv),
    m_producer {this},
    m_consumer {this},
    m_input {
            {square, "square", 0, 10, 10000000},
            {id, "id", 0, 5, 100},
            {qSin, "sin", 0, 0.5 * 3.141592653589793, 1000000},
            {sgn, "sgn", -1, 1, 50},
            {qExp, "exp", 0, 1, 100000}
    } {

    setApplicationName("A basic Qt application");
    setApplicationVersion("v2015.12.18");
    setOrganizationName("GWT-TUD");

    // parseCommandLineArguments();
    QObject::connect(this, &MyApplication::signal_producersRequired,
                     &m_producer, &FunctionValueProducer::slot_produce);
    QObject::connect(this, &MyApplication::signal_dataAvailable,
                     &m_consumer, &FunctionValueConsumer::slot_consume);
}

void
MyApplication::parseCommandLineArguments() {
    // unused
    std::cerr << "Here are your command line arguments:" << std::endl;

    unsigned counter = 0;
    for (auto argument : arguments()) {
        std::cerr << std::setw(3) << std::right << counter << " : " << \
                     argument.toStdString() << std::endl;
        counter++;
    }
}

void
MyApplication::addProduct(QVariant product, FunctionSample source) {
    // thread-safe since workers can access this function concurrently
    QMutexLocker ml {&m_productsMutex};
    if (not m_products.contains(source)) {
        m_products[source] = product;
    } else {
        qWarning() << "Product from" << &source << "is already known!";
    }
}


void
MyApplication::setup() {
    // for queued connections
    qRegisterMetaType<FunctionValues>();
    for (auto f : m_input) {
        m_producer.addFunctionSample(f);
    }
    // Make sure there are sufficient producers at startup
    for (unsigned i = 0; i < m_minProducerCount; ++i) {
        emit signal_producersRequired();
    }
}

void
MyApplication::slot_producerFinished() {
    if (m_producer.workerCount() < m_minProducerCount) {
       emit signal_producersRequired();
    }

    m_productsMutex.lock();
        Q_ASSERT(not m_products.isEmpty());
        FunctionSample funcSample = m_products.begin().key();
        QVariant product = m_products.take(funcSample);
    m_productsMutex.unlock();

    emit signal_dataAvailable(product, funcSample);
}

void
MyApplication::slot_consumerFinished() {
    if (++m_finishedConsumers >= m_input.size()) {
        exit(0);
    }
}
