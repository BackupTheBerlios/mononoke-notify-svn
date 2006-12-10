/*!
** @file   HttpDownloader.cc
** @author Alexandre Bique <bique.alexandre@gmail.com>
** @date   Sun Dec 10 20:22:14 2006
**
** @brief  Implements MononokeNotify::HttpDownloader
**
**
*/


#include <QHttp>
#include <QFile>
#include <QFileInfo>
#include <QUrl>

#include "HttpDownloader.hh"

using namespace MononokeNotify;

static int	http_dl_count = 0;

/*!
** @param url the url to the file
** @param filename the filename
** @param parent the parent object
** @brief Downloads url to filename
*/
HttpDownloader::HttpDownloader(QString &	url,
			       QString &	filename,
			       QObject *	parent)
  : QObject(parent)
{
  http = new QHttp("mononoke-bt.org", 80, this);
  file = new QFile(filename, this);
  name = QFileInfo(filename).fileName();

  file->open(QIODevice::WriteOnly);
  http->get(url, file);
  connect(http, SIGNAL(done(bool)), this, SLOT(done(void)));

  http_dl_count++;
}



/*!
** @brief called when the download is finished
*/
void
HttpDownloader::done(void)
{
  file->close();
  http_dl_count--;
  finished();
  delete (this);
}

/*!
** @brief gives you the number of current download
** @return the number of current download
*/
int
HttpDownloader::count(void)
{
  return (http_dl_count);
}
