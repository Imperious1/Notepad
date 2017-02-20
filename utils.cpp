#include "utils.h"
#include "QString"
#include "QMessageBox"
#include "QtDebug"
#include "QtNetwork"

Utils::Utils()
{

}

using namespace std;

//Searches the notes content with the Haystack & Needle technique
int* Utils::findTextPositions(QString noteContents, QString query) {
    int *pos = new int[2];
    if(!query.isEmpty ()) {
        if(noteContents.contains (query)) {
            pos[0] = noteContents.indexOf (query, 0);
            pos[1] = noteContents.indexOf (query, 0) + query.length ();
            return pos;
        } else delete pos;
    }
    return nullptr;
}

void Utils::createMessageBox(QWidget *parent, QString title, QString message) {
    QMessageBox *box = new QMessageBox(parent);
    box->setText (message);
    box->setWindowTitle (title);
    box->exec ();
}

//Selects and highlights the specified text
void Utils::selectText(QTextEdit *textEdit, int *data) {
    QTextCursor c = textEdit->textCursor();
    c.setPosition(data[0]);
    c.setPosition(data[1], QTextCursor::KeepAnchor);
    delete data;
    textEdit->setTextCursor(c);
}

//Creates Yes or No dialog
QMessageBox::StandardButton Utils::createDecisionMessageBox (QWidget *parent, QString title, QString message) {
    return QMessageBox::question(parent, title, message,
                                 QMessageBox::Yes|QMessageBox::No);
}

QString Utils::qStrReplace(QString needle, QString replacement, QString haystack) {
    return haystack.replace(haystack.indexOf(needle), needle.size(), replacement);
}

/*
QNetworkRequest Utils::formRequest(list<pair<QString, QString>> pData, QString title) {
    QUrl serviceUrl = QUrl("http://www.pastebin.com/api/api_post.php");
    QUrlQuery postData;


    for(pair<QString, QString> p : pData) {
        postData.addQueryItem(p.first, p.second);
    }

    QNetworkRequest networkRequest(serviceUrl);
    networkRequest.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");

    return networkRequest;
}
*/
