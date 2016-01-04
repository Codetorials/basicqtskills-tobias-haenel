#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QRunnable>


namespace basicQt {

/**
 * @brief The Worker class is a prototype for any worker used in QThreadpool
 */
class Worker :
        public QObject,
        public QRunnable {
    Q_OBJECT

public:
    explicit Worker();

    /**
     * @brief run is the function that should be overwritten by any real worker
     * to do its work.
     */
    virtual void run();
};

}


#endif // WORKER_H
