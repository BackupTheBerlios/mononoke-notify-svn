#include <QFileInfo>
#include <QUrl>

#include "HttpDownloader.hh"

using namespace MononokeNotify;

static int http_dl_count = 0;

HttpDownloader::HttpDownloader(QString & url, QString & filename, QObject * parent)
    : QObject(parent)
{
    http = new QHttp("mononoke-bt.org", 80, this);
    file = new QFile(filename, this);
    name = QFileInfo(filename).fileName();

    file->open(QIODevice::WriteOnly);
    http->get(url, file);
    connect(http, SIGNAL(done(bool)), this, SLOT(done(bool)));

    http_dl_count++;
}

void
HttpDownloader::done(bool error)
{
    file->close();
    http_dl_count--;
    finished();
    delete
	this;
}

int
HttpDownloader::count(void)
{
    return (http_dl_count);
}
