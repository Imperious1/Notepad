#include "trendingdialog.h"
#include "ui_trendingdialog.h"

TrendingDialog::TrendingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TrendingDialog)
{
    ui->setupUi(this);
}

TrendingDialog::~TrendingDialog()
{
    delete ui;
}
