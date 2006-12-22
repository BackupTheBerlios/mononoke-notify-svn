
/*
**  Copyright 2006, Alexandre Bique <bique.alexandre@gmail.com>
**
**  This ./HttpDownloader.cc is part of mononoke-notify-2.
**
**  Foobar is free software; you can redistribute it and/or modify
**  it under the terms of the GNU General Public License as published by
**  the Free Software Foundation; either version 2 of the License, or
**  (at your option) any later version.
**
**  Foobar is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU General Public License for more details.
**
**  You should have received a copy of the GNU General Public License
**  along with Foobar; if not, write to the Free Software
**  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
**
*/

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
