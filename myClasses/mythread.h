#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>

class myThread : public QThread
{
    Q_OBJECT
public:
    myThread(){

    }

    void run(){
        exec();
    }
};

#endif // MYTHREAD_H
