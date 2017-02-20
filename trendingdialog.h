#ifndef TRENDINGDIALOG_H
#define TRENDINGDIALOG_H

#include <QDialog>

namespace Ui {
class TrendingDialog;
}

class TrendingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TrendingDialog(QWidget *parent = 0);
    ~TrendingDialog();

private:
    Ui::TrendingDialog *ui;
};

#endif // TRENDINGDIALOG_H
