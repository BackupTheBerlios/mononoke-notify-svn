
/*
**  Copyright 2006, Alexandre Bique <bique.alexandre@gmail.com>
**
**  This ./HttpDownloader.cc is part of mononoke-notify-2.
**
**  mononoke-notify-2 is free software; you can redistribute it and/or modify
**  it under the terms of the GNU General Public License as published by
**  the Free Software Foundation; either version 2 of the License, or
**  (at your option) any later version.
**
**  mononoke-notify-2 is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU General Public License for more details.
**
**  You should have received a copy of the GNU General Public License
**  along with mononoke-notify-2; if not, write to the Free Software
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
#include "App.hh"
#include "Config.hh"

using namespace MononokeNotify;

int	HttpDownloader::dl_count = 0;

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
  QUrl host(url);
  http = new QHttp(host.host(), 80, this);
  if (mn_config.proxy)
    http->setProxy(mn_config.proxyServer, mn_config.proxyPort,
		   mn_config.proxyUser, mn_config.proxyPass);
  file = new QFile(filename, this);
  name = QFileInfo(filename).fileName();

  file->open(QIODevice::WriteOnly);
  http->get(url, file);
  connect(http, SIGNAL(done(bool)), this, SLOT(done(void)));

  dl_count++;
}



/*!
** @brief called when the download is finished
*/
void
HttpDownloader::done(void)
{
  file->close();
  dl_count--;
  finished();
  deleteLater();
}

/*!
** @brief gives you the number of current download
** @return the number of current download
*/
int
HttpDownloader::count(void)
{
  return (dl_count);
}
