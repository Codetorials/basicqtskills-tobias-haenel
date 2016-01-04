#include "include/FunctionStatWorker.h"
#include "include/FunctionValueConsumer.h"

#include <QDebug>
#include <QtGlobal>

using namespace basicQt;

FunctionValueConsumer::FunctionValueConsumer(QObject *parent) : QObject(parent) {}

void
FunctionValueConsumer::slot_consume(QVariant product, FunctionSample funcSample) {
    // only support FunctionValues at the moment
    // QVariant is kind of useless in this case
    if (product.canConvert<FunctionValues>()) {
        FunctionValues funcValues = product.value<FunctionValues>();
        Q_ASSERT(funcValues != nullptr);
        FunctionStatWorker *funcStatWorker = new FunctionStatWorker(funcValues, funcSample, this);
        // thread pool will delete the worker automatically
        m_threadPool.start(funcStatWorker);
    } else {
        qDebug() << "Unknown product:" << product;
    }
}
