#include "trendingdialog.h"
#include "ui_trendingdialog.h"
#include "QUrlQuery"
#include "QtXml/QDomDocument"
#include "QtXml/QDomElement"

TrendingDialog::TrendingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TrendingDialog)
{
    ui->setupUi(this);
    QSize dimens = size();
    ui->trendList->setGeometry(0, 0, dimens.width(), dimens.height());

    QUrl serviceUrl = QUrl("http://www.pastebin.com/api/api_post.php");
    QUrlQuery postData;

    postData.addQueryItem("api_dev_key", "ie827461ea8c38526aa89f3d67cc8734");
    postData.addQueryItem("api_option", "trends");

    // Call the webservice
    QNetworkAccessManager *networkManager = new QNetworkAccessManager(this);
    connect(networkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(onRetrieveComplete(QNetworkReply*)));

    QNetworkRequest networkRequest(serviceUrl);
    networkRequest.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");
    networkManager->post(networkRequest, postData.toString(QUrl::FullyEncoded).toUtf8());
}

void TrendingDialog::resizeEvent(QResizeEvent* event)
{
    ui->trendList->setGeometry(0, 0, size().width(), size().height());
}

void TrendingDialog::onRetrieveComplete(QNetworkReply *reply) {
    QByteArray data = reply->readAll ();
    if(data.contains ("Bad API")) Utils::createMessageBox (this, "Problem occurred", data);
    QString test("<root>" + data + "</root>");
    QDomDocument doc;
    doc.setContent (test);
    QDomNodeList paste = doc.childNodes ().at (0).childNodes ();
    qint32 size = paste.size ();
    Trend trends[19];
    for(qint32 i = 0; i <= size; i++) {
        QDomNodeList pasteContents = paste.at (i).childNodes ();
        qint32 sizeContent = pasteContents.size ();
        Trend trend;
        for(qint32 j = 0; j <= sizeContent; j++) {
            qDebug() << pasteContents.at (j).toElement ().text() << endl;
            trend.key = pasteContents.at (0).toElement ().text ();
            trend.date = pasteContents.at (1).toElement ().text ().toLongLong ();
            trend.title = pasteContents.at (2).toElement ().text ();
            trend.size = pasteContents.at (3).toElement ().text ().toInt ();
            trend.expiration = pasteContents.at (4).toElement ().text ().toLongLong ();
            trend.privacy = pasteContents.at (5).toElement ().text ().toShort ();
            trend.formatLong = pasteContents.at (6).toElement ().text ();
            trend.formatShort = pasteContents.at (7).toElement ().text ();
            trend.formatShort = pasteContents.at (8).toElement ().text ();
            trend.url = pasteContents.at (9).toElement ().text ();
            trend.hits = pasteContents.at (10).toElement ().text ().toInt ();
            trends[i] = trend;
        }
    }
    setListData (trends);
}

void TrendingDialog::setListData(Trend trends[]) {
    QListWidget *trendList = ui->trendList;
    for(int i = 0; i <= 18; i++) {
        QString title = trends[i].title;
        trendList->addItem ((title.isEmpty ()) ? "Untitled" : title);
    }
}

TrendingDialog::~TrendingDialog()
{
    delete ui;
}
