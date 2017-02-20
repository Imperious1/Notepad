#ifndef READTHREAD_H
#define READTHREAD_H

#include "QThread"
#include "QTextEdit"

class ReadThread : public QThread
{
private:
    QTextEdit *noteEdit;
    QString openedFileName;
    bool success;
    QByteArray data;

public:
    ReadThread();
    void configure(QString openedFileName);
    void openFile();
    bool wasSuccess();
    QString getData();
    virtual void run();
};

#endif // READTHREAD_H
