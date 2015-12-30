#include "include/FunctionValueProducer.h"
#include "include/FunctionValueWorker.h"

#include <QDebug>
#include <QTime>
#include <QObject>
#include <QThreadPool>

using namespace basicQt;

FunctionValueProducer::FunctionValueProducer(QObject *parent) :
    QObject(parent) {}

void
FunctionValueProducer::slot_produce() {
   if (not m_funcs.isEmpty()) {
        FunctionValueWorker *funcValueWorker = new FunctionValueWorker(m_funcs.dequeue(), this);
        m_workerPool.start(funcValueWorker);
        m_workerCount++;
   }
}

void
FunctionValueProducer::slot_handleFinishedWorker() {
    m_workerCount--;
}
