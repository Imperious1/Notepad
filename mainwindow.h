#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QLabel>
#include <QActionGroup>
#include <readthread.h>
#include <QNetworkReply>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:

private:
    Ui::MainWindow *ui;
    void createActions();
    void createMenus();
    ReadThread *tempReadThread;
    bool saved;
    bool opened;
    void resizeEvent(QResizeEvent* event);
    QString openedFileName;
    QTextEdit *noteEdit;
    void toggleActions(bool actionFind, bool actionFp, bool actionUpToPb,
                                   bool actionSave, bool actionSaveA, bool actionDel, bool actionNew);

private slots:
    void on_actionNew_triggered();
    void on_actionSave_triggered();
    void on_actionFind_triggered();
    void on_actionFind_Replace_triggered();
    void on_noteEdit_textChanged();
    void on_actionWord_Wrap_toggled(bool arg1);
    void on_actionOpen_triggered();
    void on_actionSave_as_triggered();
    void on_actionExit_triggered();
    void read_finished();
    void onPasteComplete(QNetworkReply *);
    void on_actionDelete_triggered();
    void on_actionUpload_triggered();
    void on_actionTrending_triggered();
};

#endif // MAINWINDOW_H
