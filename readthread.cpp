#include "readthread.h"
#include "QFileDialog"
#include "QDebug"

ReadThread::ReadThread()
{

}

void ReadThread::configure(QString openedFileName) {
    this->openedFileName = openedFileName;
}

void ReadThread::openFile() {
    QFile file (openedFileName);
    if(file.open (QIODevice::ReadOnly)) {
        data = file.readAll ();
        file.close ();
        success = true;
    } else success = false;
}

bool ReadThread::wasSuccess() {
    return success;
}

void ReadThread::run() {
    openFile();
}

QString ReadThread::getData() {
    return data;
}
