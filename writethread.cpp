#include "writethread.h"
#include "QString"
#include "QFile"
#include "QDebug"
#include "QSaveFile"

WriteThread::WriteThread(QString fileName, QByteArray data)
{
    // by this point, the data is corrupt.
    //so in short, before we pass it to the write threads constructor, everything is good, once there, its messed up
    qDebug() << fileName;
    qDebug() << "Data: " << *data;
    this->fileName = fileName;
    this->data = data + '\0';
}

void WriteThread::run() {
    qDebug() << "WriteThread: " << data;
    bool result = write ();
    if(result) qDebug() << "Successfully written";
    else qDebug() << "Error, write failed";
}


bool WriteThread::write() {
    QSaveFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;
    if (-1 == file.write(data))
        return false;
    return file.commit();
}
