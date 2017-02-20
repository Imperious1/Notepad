#ifndef PASTEBINDIALOG_H
#define PASTEBINDIALOG_H

#include <QDialog>
#include <QLineEdit>

namespace Ui {
class PasteBinDialog;
}

class PasteBinDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PasteBinDialog(QWidget *parent = 0);
    ~PasteBinDialog();
    int getPrivacy();
    QString getExpiration();
    QString getTitle();
    QString indexToExpiration(int);
    QString getPasteFormat();
    QString indexToPasteType(int);

private:
    Ui::PasteBinDialog *ui;
};

#endif // PASTEBINDIALOG_H
