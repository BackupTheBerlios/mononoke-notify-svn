
/*
**  Copyright 2006, Alexandre Bique <bique.alexandre@gmail.com>
**
**  This ./Updater.cc is part of mononoke-notify-2.
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
** @file   Updater.cc
** @author Alexandre Bique <bique.alexandre@gmail.com>
** @date   Fri Dec 22 16:37:08 2006
**
** @brief  Implements MononokeNotify::Updater
**
**
*/


#include <QDir>
#include <QFile>
#include <QHttp>
#include <QDomDocument>
#include <QtDebug>

#include "App.hh"
#include "Config.hh"
#include "Updater.hh"
#include "HttpDownloader.hh"
#include "ProgressDlg.hh"
#include "TrayMenu.hh"

using namespace MononokeNotify;

Updater::Updater()
  : QObject(qApp)
{
}

void
Updater::update(void)
{
  mn_progress->show();
  downloadUserInfoXml();
  checkTheme();
}

void
Updater::downloadUserInfoXml(void)
{
  QString url = "http://mononoke-bt.org/myinfos.php?login="
    + mn_config.userName + "&latest="
    + QString::number(mn_config.nbrTorrent) + "&xml";
  QString filename = QDir::homePath()
    + "/.config/mononoke-notify-2/user_info.xml";
  HttpDownloader *dl = new HttpDownloader(url, filename, this);

  connect(dl, SIGNAL(finished()), &mn_xml, SLOT(parse()));
  mn_progress->monitorDownload(dl);
}

void
Updater::downloadIcon(QString &		url,
		      QString &		filename)
{
  HttpDownloader *dl = new HttpDownloader(url, filename, this);

  connect(dl, SIGNAL(finished()), this, SLOT(tryUpdateMenu()));
  mn_progress->monitorDownload(dl);
}

void
Updater::downloadTeamIcon(qint32 id)
{
  if (id == 0)
    return;
  QString url = "http://mononoke-bt.org/pic/teams/icons/" +
    QString::number(id) + ".jpg";
  QString filename = QDir::homePath() + "/.config/mononoke-notify-2/data/team_"
    + QString::number(id) + ".jpg";
  if (QFile::exists(filename))
    return;
  downloadIcon(url, filename);
}

void
Updater::downloadAnimeIcon(qint32 id)
{
  if (id == 0)
    return;
  QString url = "http://mononoke-bt.org/pic/categories/" +
    QString::number(id) + ".jpg";
  QString filename = QDir::homePath()
    + "/.config/mononoke-notify-2/data/anime_" + QString::number(id) + ".jpg";

  if (QFile::exists(filename))
    return;
  downloadIcon(url, filename);
}

void
Updater::downloadGenreIcon(qint32 id)
{
  if (id == 0)
    return;
  //return; /*\ WARNING !!! \*/
  QString url = "http://mononoke-bt.org/pic/genres/" +
    QString::number(id) + ".jpg";
  QString filename = QDir::homePath()
    + "/.config/mononoke-notify-2/data/genre_" + QString::number(id) + ".jpg";

  if (QFile::exists(filename))
    return;
  downloadIcon(url, filename);
}

void
Updater::tryUpdateMenu(void)
{
  if (HttpDownloader::count() == 0) {
    mn_progress->canHide();
    // On genere le menu
    if (mn_menu)
    {
      delete (mn_menu);
    }
    mn_menu = new TrayMenu();
    mn_tray_icon.setContextMenu(mn_menu);
    mn_menu->generate();
  }
}

void
Updater::downloadDefaultTheme(void)
{
  QString url = "http://dev.mononoke-bt.org/projects/mononoke-notify/themes/default/theme.xml";
  QString filename = QDir::homePath() +
    "/.config/mononoke-notify-2/themes/default/theme.xml";
  QDir dir(QDir::homePath() + "/.config/mononoke-notify-2/themes/default/");

  if (!dir.exists())
    dir.mkpath(QDir::homePath() + "/.config/mononoke-notify-2/themes/default/");
  HttpDownloader *dl = new HttpDownloader(url, filename);

  connect(dl, SIGNAL(finished()), this, SLOT(checkTheme()));
  mn_progress->monitorDownload(dl);
}

void
Updater::unexistantTheme(void)
{
  qDebug() << "Theme inexistant.";
  if (mn_config.theme != "default") {
    /* On prends le theme par defaut */
    mn_config.theme = "defaut";
    mn_config.save();
    checkTheme();
    return;
  }
  /* On a pas le theme par defaut, on le download */
  downloadDefaultTheme();
}

void
Updater::checkTheme(void)
{
  QFile file(QDir::homePath() + "/.config/mononoke-notify-2/themes/" +
	     mn_config.theme + "/theme.xml");
  if (!file.exists()) {
    unexistantTheme();
    return;
  }
  file.open(QIODevice::ReadOnly | QIODevice::Text);
  QDomDocument doc("Theme");

  if (!doc.setContent(&file)) {
    file.close();
    return;
  }
  QDomElement elem = doc.documentElement().firstChildElement("Files");
  QString base = elem.attribute("base");

  elem = elem.firstChildElement("File");
  checkThemeFiles(elem, base);
}

void
Updater::checkThemeFiles(QDomElement &	elem,
			 QString &	base)
{
  QString		local;
  QString		url;
  HttpDownloader	*dl = 0;

  for (; !elem.isNull(); elem = elem.nextSiblingElement("File")) {
    local = QDir::homePath() + "/.config/mononoke-notify-2/themes/"
      + mn_config.theme + "/" + elem.attribute("name");
    url = base + elem.attribute("name");
    if (QFile::exists(local)) {
      elem = elem.nextSiblingElement("File");
      continue;
    }
    dl = new HttpDownloader(url, local);
    connect(dl, SIGNAL(finished()), this, SLOT(tryUpdateMenu()));
    mn_progress->monitorDownload(dl);
  }
}
