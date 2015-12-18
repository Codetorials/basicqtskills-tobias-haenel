#include "MyApplication.h"

#include <iomanip>
#include <iostream>

#include <QStringList>

using namespace basicQt;

MyApplication::MyApplication(int argc, char** argv):
    QCoreApplication(argc, argv) {

    setObjectName("My Application");
    setApplicationName("A basic Qt application");
    setApplicationVersion("v2015.12.18");
    setOrganizationName("GWT-TUD");

    parseCommandLineArguments();
}

void
MyApplication::parseCommandLineArguments() {
    std::cerr << "Here are your command line arguments:" << std::endl;

    unsigned counter = 0;
    for(auto argument : arguments()){
        std::cerr << std::setw(3) << std::right << counter << " : " << argument.toStdString() << std::endl;
        counter++;
    }
}

void
MyApplication::setup(){
    // Make sure there are sufficient producers at startup
}

void
MyApplication::slot_producerFinished() {
    if(m_producer.workerCount() < m_minProducerCount) {
       emit signal_producersRequired();
    }
}
