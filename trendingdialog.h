#ifndef TRENDINGDIALOG_H
#define TRENDINGDIALOG_H

#include <QDialog>
#include "QNetworkReply"
#include "utils.h"

namespace Ui {

class TrendingDialog;
}

class TrendingDialog : public QDialog
{
    Q_OBJECT

    struct Trend {
        QString key;
        qlonglong date;
        QString title;
        int size;
        qlonglong expiration;
        short privacy;
        QString formatLong;
        QString formatShort;
        QString url;
        int hits;
    };

public:
    explicit TrendingDialog(QWidget *parent = 0);
    ~TrendingDialog();

private slots:
    void onRetrieveComplete(QNetworkReply *reply);

private:
    void resizeEvent(QResizeEvent* event);
    void setListData(Trend trends[]);
    Ui::TrendingDialog *ui;
};

#endif // TRENDINGDIALOG_H
