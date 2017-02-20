#include "mainwindow.h"
#include "QVBoxLayout"
#include "ui_mainwindow.h"
#include "QMessageBox"
#include "QDialog"
#include "QSaveFile"
#include "QFileDialog"
#include "QIODevice"
#include "QInputDialog"
#include "replacedialog.h"
#include "utils.h"
#include "writethread.h"
#include "QDebug"
#include "pastebindialog.h"
#include "readthread.h"
#include "QUrlQuery"
#include "trendingdialog.h"

#define NEW_NOTE "New Note"

//We need to find a better way to use these threads, putting them on heap with no way to destroy is a memory leak (i think, maybe not)
//We need to fix the ReadThread connect, our current method is inefficient and a waste of memory.

//Need to add horizonal scrollbars
//Need to fix scrolling vertically
//Add custom Find dialog, allow match case, find next, find last.
//Modify both find/find&replace to search the next
//Modify find/replace to replace all or replace next. Basically dont close dialogs until user says so

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    noteEdit = ui->noteEdit;
    setWindowTitle (NEW_NOTE);
    QSize dimens = size();
    noteEdit->setGeometry(0, 0, dimens.width(), dimens.height());
    opened = false;
    toggleActions(false, false, false, false, false, false, false);
    saved = true;
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
    QMainWindow::resizeEvent(event);
    noteEdit->setGeometry(0, 0, size().width(), size().height());
}

MainWindow::~MainWindow()
{
    delete ui;
    delete noteEdit;
}

void MainWindow::on_actionNew_triggered()
{
    if(!saved) {
        QMessageBox::StandardButton reply = Utils::createDecisionMessageBox (
                    this, "Warning!", "Any unsaved progress will be lost, are you sure?");
        if (reply == QMessageBox::Yes) {
            noteEdit->setText ("");
            setWindowTitle (NEW_NOTE);
            opened = false;
            openedFileName = "";
            saved = true;
            toggleActions(false, false, false, false, false, false, false);
        }
    } else {
        setWindowTitle (NEW_NOTE);
        noteEdit->setText ("");
        opened = false;
        saved = true;
        openedFileName = "";
        toggleActions(false, false, false, false, false, false, false);
    }
}

void MainWindow::on_actionSave_triggered()
{
    openedFileName = (opened) ? openedFileName : QFileDialog::getSaveFileName(this, "Save", QDir::homePath(), NULL, 0, 0);
    QByteArray array(noteEdit->toPlainText ().toStdString().c_str());
    WriteThread *thread = new WriteThread(
                openedFileName, array);
    thread->start ();
    QFileInfo info(openedFileName);
    setWindowTitle (info.fileName ());
    saved = true;
    if(!opened)
        opened = true;
    if(noteEdit->toPlainText().isEmpty()) {
        toggleActions(false, false, false, false, false, true, true);
    } else if(!noteEdit->toPlainText().isEmpty()) {
        toggleActions(true, true, true, false, true, true, true);
    }
}

void MainWindow::on_actionFind_triggered()
{
    bool ok;

    QInputDialog dialog(this, NULL);
    QString query = dialog.getText(0, "Find", "Search your text...", QLineEdit::Normal,
                                   "", &ok);\
    Utils::findTextPositions (noteEdit->toPlainText (), query);
    int *res = Utils::findTextPositions(noteEdit->toPlainText (), query);
    if(res != nullptr && ok) {
        Utils::selectText(noteEdit, res);
        res = nullptr;
    } else if(res != nullptr && !query.isEmpty ()) {
        delete res;
        Utils::createMessageBox (this, "No search results", "There is no results for \"" + query + "\"");
    }
    if(res != nullptr)
        delete res;
}

void MainWindow::on_actionFind_Replace_triggered()
{
    /*
     * This method requires setFocus() on the Search lineEdit, not sure if this will be resolved either.
     */
    ReplaceDialog dialog(this);
    dialog.setWindowTitle("Find and replace");
    dialog.exec ();
    QString query = dialog.getQuery ();
    QString replacement = dialog.getReplacement ();
    QString noteContents = noteEdit->toPlainText ();
    if(!dialog.wasRejected () && !query.isEmpty ()) {
        qDebug() << "Before: " << noteContents;
        noteContents = Utils::qStrReplace (query, replacement, noteContents);
        qDebug() << "After: " << noteContents;
        noteEdit->setText (noteContents);
        int *res = Utils::findTextPositions (noteEdit->toPlainText (), replacement);
        if(res != NULL) {
            Utils::selectText (noteEdit, res);
        } else {
            delete res;
            Utils::createMessageBox (this, "No search results", "There is no results for \"" + query + "\"");
        }
    }
}

void MainWindow::on_noteEdit_textChanged()
{
    if(!noteEdit->toPlainText ().isEmpty () && !opened) {
        saved = false;
        toggleActions (true, true, true, true, true, false, false);
    } else if(noteEdit->toPlainText().isEmpty () && !opened) {
        saved = true;
        toggleActions(false, false, false, false, false, false, false);
    } else if(noteEdit->toPlainText().isEmpty() && opened) {
        saved = false;
        toggleActions(false, false, false, true, false, true, true);
    } else if(!noteEdit->toPlainText().isEmpty() && opened) {
        saved = false;
        toggleActions(true, true, true, true, true, true, true);
    }
}

void MainWindow::toggleActions(bool actionFind, bool actionFp, bool actionUpToPb,
                               bool actionSave, bool actionSaveA, bool actionDel, bool actionNew) {
    ui->actionFind->setEnabled(actionFind);
    ui->actionFind_Replace->setEnabled(actionFp);
    ui->actionUpload->setEnabled(actionUpToPb);
    ui->actionSave->setEnabled(actionSave);
    ui->actionSave_as->setEnabled(actionSaveA);
    ui->actionDelete->setEnabled(actionDel);
    ui->actionNew->setEnabled(actionNew);
}

void MainWindow::on_actionWord_Wrap_toggled(bool arg1)
{
    (arg1 == true) ? noteEdit->setWordWrapMode (
                         QTextOption::WrapAtWordBoundaryOrAnywhere) :  noteEdit->setWordWrapMode (
                         QTextOption::NoWrap);

}

void MainWindow::on_actionOpen_triggered()
{
    openedFileName = QFileDialog::getOpenFileName (this, tr("Open File"), QDir::homePath (), NULL);
    tempReadThread = new ReadThread();
    tempReadThread->configure(openedFileName);
    tempReadThread->start();
    connect(tempReadThread, SIGNAL(finished()), this, SLOT(read_finished()));
}

void MainWindow::read_finished() {
    QFileInfo info(openedFileName);
    if(tempReadThread->wasSuccess()) {
        noteEdit->setText(tempReadThread->getData());
        setWindowTitle (info.fileName ());
        saved = true;
        opened = true;
        if(noteEdit->toPlainText().isEmpty()) {
            toggleActions(false, false, false, false, false, true, true);
        } else if(!noteEdit->toPlainText().isEmpty()) {
            toggleActions(true, true, true, false, true, true, true);
        }
    }
    delete tempReadThread;
}

void MainWindow::on_actionSave_as_triggered()
{
    openedFileName = QFileDialog::getSaveFileName(this, "Save", QDir::homePath(), NULL, 0, 0);
    QByteArray array(noteEdit->toPlainText().toStdString().c_str());
    WriteThread *thread = new WriteThread(openedFileName, array);
    thread->start ();
    QFileInfo info(openedFileName);
    setWindowTitle (info.fileName ());
    saved = true;
    opened = true;
}

void MainWindow::on_actionExit_triggered()
{
    if(!saved) {
        QMessageBox::StandardButton reply = Utils::createDecisionMessageBox (
                    this, "Warning!", "Any unsaved progress will be lost, are you sure?");
        if (reply == QMessageBox::Yes) {
            QApplication::exit (0);
        }
    } else {
        QApplication::exit (0);
    }
}

void MainWindow::onPasteComplete(QNetworkReply *reply) {
    QByteArray data = reply->readAll ();
    if(data.contains ("Bad API"))
        Utils::createMessageBox (this, "Problem occurred", data);
    else Utils::createMessageBox (this, "Uploaded successfully!", data);
}

void MainWindow::on_actionDelete_triggered()
{
    QMessageBox::StandardButton decision = Utils::createDecisionMessageBox (
                this, "Warning!", "Are you sure you want to delete this file?");
    if(decision == QMessageBox::Yes) {
        QFile::remove (openedFileName);
        setWindowTitle (NEW_NOTE);
        noteEdit->setText ("");
        opened = false;
        saved = true;
        toggleActions(false, false, false, false, false, false, false);
    }
}

void MainWindow::on_actionUpload_triggered()
{
    if(!noteEdit->toPlainText ().isEmpty ()) {
        PasteBinDialog *dialog = new PasteBinDialog(this);
        dialog->setWindowTitle ("Upload to Pastebin");
        if(dialog->exec ()) {
            QUrl serviceUrl = QUrl("http://www.pastebin.com/api/api_post.php");
            QUrlQuery postData;
            QString title = dialog->getTitle ();

            postData.addQueryItem("api_dev_key", "ie827461ea8c38526aa89f3d67cc8734");
            postData.addQueryItem("api_option", "paste");
            postData.addQueryItem ("api_paste_code", noteEdit->toPlainText ());
            postData.addQueryItem ("api_paste_name", (title.isEmpty ()) ? "Untitled" : title);
            postData.addQueryItem ("api_paste_private", QString::number (dialog->getPrivacy ()));
            postData.addQueryItem ("api_paste_expire_date", dialog->getExpiration ());
            postData.addQueryItem ("api_paste_format", dialog->getPasteFormat ());

            // Call the webservice
            QNetworkAccessManager *networkManager = new QNetworkAccessManager(this);
            connect(networkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(onPasteComplete(QNetworkReply*)));

            QNetworkRequest networkRequest(serviceUrl);
            networkRequest.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");
            networkManager->post(networkRequest, postData.toString(QUrl::FullyEncoded).toUtf8());
        }
    }
}

void MainWindow::on_actionTrending_triggered()
{
    TrendingDialog *dialog = new TrendingDialog();
    if(dialog->exec ()) {

    }
}
