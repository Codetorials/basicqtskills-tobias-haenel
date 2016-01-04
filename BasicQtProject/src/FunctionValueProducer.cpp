#include "include/FunctionValueProducer.h"
#include "include/FunctionValueWorker.h"


using namespace basicQt;

FunctionValueProducer::FunctionValueProducer(QObject *parent) :
    QObject(parent) {}

void
FunctionValueProducer::addFunctionSample(FunctionSample funcSample) {
    // will only be used in one thread and therefore
    // doesn't need to be thread-safe
    m_funcSamples.append(funcSample);
}


void
FunctionValueProducer::slot_produce() {
   if (not m_funcSamples.isEmpty()) {
        FunctionValueWorker *funcValueWorker = new FunctionValueWorker(m_funcSamples.dequeue(), this);
        // thread pool will delete the worker automatically
        m_threadPool.start(funcValueWorker);
        m_workerCount++;
   }
   // ignore this slot if we don't have any input left
}

void
FunctionValueProducer::slot_handleFinishedWorker() {
    m_workerCount--;
}
