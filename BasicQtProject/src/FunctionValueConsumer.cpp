#include "include/FunctionValueConsumer.h"
#include "include/FunctionValues.h"
#include "include/FunctionStatWorker.h"

#include <QThreadPool>
#include <QDebug>

using namespace basicQt;

FunctionValueConsumer::FunctionValueConsumer(QObject *parent) : QObject(parent) {}

void
FunctionValueConsumer::slot_consume(QVariant product) {
    if (product.canConvert<FunctionValues>()) {
        FunctionValues funcValues = product.value<FunctionValues>();
        FunctionStatWorker *funcStatWorker = new FunctionStatWorker(funcValues, this);
        m_workerPool.start(funcStatWorker);
    }

}
