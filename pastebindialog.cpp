#include "pastebindialog.h"
#include "ui_pastebindialog.h"

PasteBinDialog::PasteBinDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PasteBinDialog)
{
    ui->setupUi(this);

}

PasteBinDialog::~PasteBinDialog()
{
    delete ui;
}

QString PasteBinDialog::getTitle() {
    return ui->titleLineEdit->text ();
}

int PasteBinDialog::getPrivacy() {
    return ui->privacyBox->currentIndex ();

}

QString PasteBinDialog::getExpiration() {
    return indexToExpiration(ui->expirationBox->currentIndex ());
}

QString PasteBinDialog::getPasteFormat () {
    return indexToPasteType (ui->syntaxBox->currentIndex ());
}

QString PasteBinDialog::indexToExpiration(int i) {
    switch(i) {
    case 0:
        return "10M";

    case 1:
        return "1H";

    case 2:
        return "1D";

    case 3:
        return "1W";

    case 4:
        return "2W";

    case 5:
        return "1M";

    case 6:
        return "N";

    default:
        return "10M";
    }
}

QString PasteBinDialog::indexToPasteType (int i) {
    switch(i) {
    case 0:
        return "text";
    case 1:
        return "actionscript";
    case 2:
        return "actionscript3";
    case 3:
        return "asp";
    case 4:
        return "asm";
    case 5:
        return "autohotkey";

    case 6:
        return "autoconf";
    case 7:
        return "bash";
    case 8:
        return "batch";
    case 9:
        return "brainfuck";
    case 10:
        return "c";
    case 11:
        return "c_winapi";
    case 12:
        return "c_mac";
    case 13:
        return "cil";
    case 14:
        return "csharp";
    case 15:
        return "cpp";
    case 16:
        return "cpp-winapi";
    case 17:
        return "cpp-qt";
    case 18:
        return "cmake";
    case 19:
        return "coffeescript";
    case 20:
        return "css";
    case 21:
        return "delphi";
    case 22:
        return "email";
    case 23:
        return "erlang";
    case 24:
        return "fsharp";
    case 25:
        return "gml";
    case 26:
        return "haskell";
    case 27:
        return "html4strict";
    case 28:
        return "html5";
    case 29:
        return "ini";
    case 30:
        return "java";
    case 31:
        return "java5";
    case 32:
        return "javascript";
    case 33:
        return "jquery";
    case 34:
        return "json";
    case 35:
        return "lisp";
    case 36:
        return "llvm";
    case 37:
        return "lolcode";
    case 38:
        return "lua";
    case 39:
        return "make";
    case 40:
        return "mysql";
    case 41:
        return "newlisp";
    case 42:
        return "nginx";
    case 43:
        return "objc";
    case 44:
        return "glsl";
    case 45:
        return "oracle11";
    case 46:
        return "oracle8";
    case 47:
        return "pascal";
    case 48:
        return "pawn";
    case 49:
        return "perl";
    case 50:
        return "perl6";
    case 51:
        return "php";
    case 52:
        return "plsql";
    case 53:
        return "postgresql";
    case 54:
        return "python";
    case 55:
        return "pys60";
    case 56:
        return "qbasic";
    case 57:
        return "qml";
    case 58:
        return "rbs";
    case 59:
        return "ruby";
    case 60:
        return "sas";
    case 61:
        return "scala";
    case 62:
        return "smalltalk";
    case 63:
        return "smarty";
    case 64:
        return "sqf";
    case 65:
        return "sql";
    case 66:
        return "swift";
    case 67:
        return "tsql";
    case 68:
        return "uscript";
    case 69:
        return "vbnet";
    case 70:
        return "vbscript";
    case 71:
        return "vim";
    case 72:
        return "vb";
    case 73:
        return "whitespace";
    case 74:
        return "whois";
    case 75:
        return "xml";
    case 76:
        return "xorg_conf";
    case 77:
        return "yaml";
    case 78:
        return "z80";
    default:
        return "text";
    }
}
