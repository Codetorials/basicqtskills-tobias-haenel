#include "include/Producer.h"

Producer::Producer(QObject *parent) : QObject(parent)
{

}

unsigned Producer::workerCount(){
    return 0; // TODO mockup implementation...
}
