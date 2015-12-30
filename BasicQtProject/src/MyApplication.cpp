#include "MyApplication.h"
#include "include/FunctionValueProducer.h"
#include "include/FunctionValues.h"

#include <iomanip>
#include <iostream>

#include <QStringList>

using namespace basicQt;

// functions to be sampled
double f1(double x) { return x * x; }
double f2(double x) { return 1 / (1 + x * x); }
double f3(double x) { return 1 - x; }
double f4(double x) {
    if (x == 0) return 0;
    else if (x > 0) return 1;
    else return -1;
}

MyApplication::MyApplication(int argc, char** argv):
    QCoreApplication(argc, argv),
    m_consumer {this},
    m_producer {this},
    m_input {f1, f2, f3, f4} {

    setApplicationName("A basic Qt application");
    setApplicationVersion("v2015.12.18");
    setOrganizationName("GWT-TUD");

    parseCommandLineArguments();
    QObject::connect(this, &MyApplication::signal_producersRequired, &m_producer, &FunctionValueProducer::slot_produce);
    QObject::connect(this, &MyApplication::signal_dataAvailable, &m_consumer, &FunctionValueConsumer::slot_consume);
}

void
MyApplication::parseCommandLineArguments() {
    std::cerr << "Here are your command line arguments:" << std::endl;

    unsigned counter = 0;
    for (auto argument : arguments()) {
        std::cerr << std::setw(3) << std::right << counter << " : " << argument.toStdString() << std::endl;
        counter++;
    }
}

void
MyApplication::addProduct(QVariant product) {
    QMutexLocker ml {&m_productsMutex};
    m_products.enqueue(product);
}


void
MyApplication::setup() {
    qRegisterMetaType<FunctionValues>();
    for (auto f : m_input) {
        m_producer.addFunction(f);
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
        QVariant product = m_products.dequeue();
    m_productsMutex.unlock();

    emit signal_dataAvailable(product);
}

void
MyApplication::slot_consumerFinished() {
    if (++m_finishedConsumers >= m_input.size()) {
        exit(0);
    }
}
