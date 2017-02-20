#include "replacedialog.h"
#include "ui_replacedialog.h"

ReplaceDialog::ReplaceDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ReplaceDialog)
{
    ui->setupUi(this);
    rejected = false;
}

ReplaceDialog::~ReplaceDialog()
{
    delete ui;
}

QString ReplaceDialog::getQuery () {
    return ui->searchLineEdit->text ();
}

QString ReplaceDialog::getReplacement () {
    return ui->replaceLineEdit->text ();
}

void ReplaceDialog::on_buttonBox_rejected()
{
    rejected = true;

}

bool ReplaceDialog::wasRejected () {
    return rejected;
}

void ReplaceDialog::on_buttonBox_accepted()
{
    rejected = false;
}
