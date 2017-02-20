#ifndef WRITETHREAD_H
#define WRITETHREAD_H

#include "QString"
#include "QThread"

class WriteThread : public QThread
{
private:
    QString fileName;
    QByteArray data;
    bool write();

public:
    WriteThread(QString fileName, QByteArray data);
    virtual void run();
};

#endif // WRITETHREAD_H
