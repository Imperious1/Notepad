#ifndef UTILS_H
#define UTILS_H

#include "QWidget"
#include "QTextEdit"
#include "QMessageBox"
#include "QNetworkRequest"

class Utils
{
public:
    Utils();
    static int *findTextPositions(QString noteContents, QString query);
    static void createMessageBox(QWidget *parent, QString title, QString message);
    static void selectText(QTextEdit *textEdit, int *data);
    static QMessageBox::StandardButton createDecisionMessageBox(QWidget *parent, QString title, QString message);
    static QString qStrReplace(QString needle, QString replacement, QString haystack);
//  static QNetworkRequest formRequest(std::list<std::pair<QString, QString>> pData, QString title);
};

#endif // UTILS_H
