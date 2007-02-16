
/*
**  Copyright 2006, Alexandre Bique <bique.alexandre@gmail.com>
**
**  This ./TrayMenu.cc is part of mononoke-notify-2.
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

#include <QtDebug>
#include <QIcon>
#include <QDir>
#include <QDesktopServices>

#include "App.hh"
#include "TrayMenu.hh"
#include "TrayMenuAction.hh"
#include "MononokeXml.hh"
#include "Updater.hh"
#include "PrefsDlg.hh"

using namespace MononokeNotify;

TrayMenu::TrayMenu(void)
  :QMenu()
{
  addAction("Patience, on download des icons :-)");
}

/** @brief Generate the menu from scratch ;-) */
void
TrayMenu::generate(void)
{
  clear();
  QString filename = QDir::homePath() + "/.config/mononoke-notify-2/themes/"
    + mn_config.theme + "/theme.xml";
  parse(filename);
}

/*!
** @param filename The path to the xml theme file to parse
** @brief Parse the given file
*/
void
TrayMenu::parse(QString & filename)
{
  QDomDocument	doc("Theme");
  QFile		file(filename);

  if (!file.open(QIODevice::ReadOnly))
    return;
  if (!doc.setContent(&file)) {
    file.close();
    return;
  }
  file.close();

  QDomElement elem = doc.documentElement().firstChildElement("TrayMenu");
  handleTrayMenu(elem);
  elem = doc.documentElement().firstChildElement("TrayIcon");
  handleTrayIcon(elem);
}


void
TrayMenu::handleTrayIcon(QDomElement & elem)
{
  QString filename = QDir::homePath() + "/.config/mononoke-notify-2/themes/"
    + mn_config.theme + "/" + elem.attribute("src");
  mn_tray_icon.setIcon(QIcon(filename));
  mn_tray_icon.setVisible(42);
}

void
TrayMenu::handleTrayMenu(QDomElement & elem)
{
  QDomElement child = elem.firstChildElement();

  while (!child.isNull()) {
    if (child.nodeName() == "Item")
      handleItem(child);
    else if (child.nodeName() == "Separator")
      addSeparator();
    child = child.nextSiblingElement();
  }
}

void
TrayMenu::handleItem(QDomElement & elem)
{
  QDomElement child = elem.firstChildElement();
  QString text("");
  QAction * action = addAction("");
  QString tmp = elem.attribute("action");

  if (tmp == "Mononoke") {
    connect(action, SIGNAL(triggered()), this, SLOT(mononoke()));
  } else if (tmp == "Refresh") {
    connect(action, SIGNAL(triggered()), this, SLOT(update()));
  } else if (tmp == "NewMessage") {
    connect(action, SIGNAL(triggered()), this, SLOT(newMessage()));
  } else if (tmp == "ShowPrefs") {
    connect(action, SIGNAL(triggered()), mn_prefs, SLOT(show()));
  } else if (tmp == "Quit") {
    connect(action, SIGNAL(triggered()), qApp, SLOT(quit()));
  }

  while (!child.isNull()) {
    if (child.nodeName() == "Text") {
      text += child.attribute("val");
    } else if (child.nodeName() == "Icon") {
      action->setIcon(QIcon(QDir::homePath()
			    + "/.config/mononoke-notify-2/themes/"
			    + mn_config.theme + "/" + child.attribute("src")));
    } else if (child.nodeName() == "RatioIcon") {
      QString filename = QDir::homePath() + "/.config/mononoke-notify-2/themes/"
	+ mn_config.theme + "/";

      if (mn_xml.ratio < 1)
	filename += child.attribute("src1");
      else if (mn_xml.ratio <= 2)
	filename += child.attribute("src2");
      else if (mn_xml.ratio <= 3.5)
	filename += child.attribute("src3");
      else
	filename += child.attribute("src4");
      action->setIcon(QIcon(filename));
    } else if (child.nodeName() == "UserName") {
      text += mn_config.userName;
    } else if (child.nodeName() == "TotalUpload") {
      text += QString::number((float) mn_xml.upload / 1024 / 1024 / 1024,
			      'f', 2) + " Go";
    } else if (child.nodeName() == "CountedDownload") {
      text += QString::number((float) mn_xml.download / 1024 / 1024 / 1024,
			      'f', 2) + " Go";
    } else if (child.nodeName() == "FreeDownload") {
      text += QString::number((float) mn_xml.download_free / 1024 / 1024 / 1024,
			      'f', 2) + " Go";
    } else if (child.nodeName() == "TotalDownload") {
      text += QString::number((float) (mn_xml.download + mn_xml.download_free)
			      / 1024 / 1024 / 1024, 'f', 2) + " Go";
    } else if (child.nodeName() == "Ratio") {
      text += QString::number(mn_xml.ratio, 'f', 2);
    } else if (child.nodeName() == "TrueRatio") {
      text += QString::number(mn_xml.trueRatio, 'f', 2);
    } else if (child.nodeName() == "NbrNewMsg") {
      text += QString::number(mn_xml.unread);
    } else if (child.nodeName() == "NeedSeeds") {
      QMenu * menu = handleTorrentList(child.toElement(), mn_xml.need_seed);
      action->setMenu(menu);
      if (menu->isEmpty())
	action->setEnabled(0);
    } else if (child.nodeName() == "LastReleases") {
      QMenu * menu = handleTorrentList(child.toElement(), mn_xml.sorties);
      action->setMenu(menu);
      if (menu->isEmpty())
	action->setEnabled(0);
    } else if (child.nodeName() == "LastTorrents") {
      QMenu * menu = handleTorrentList(child.toElement(), mn_xml.latest);
      action->setMenu(menu);
      if (menu->isEmpty())
	action->setEnabled(0);
    }
    child = child.nextSiblingElement();
  }
  action->setText(text);
}

QMenu *
TrayMenu::handleTorrentList(QDomElement		elem,
			    TorrentList &	tl)
{
  QMenu *	menu = new QMenu();
  int		i;

  for (i = 0; i < tl.count; i++) {
    menu->addAction(new TrayMenuAction(elem, tl.t[i]));
  }
  return menu;
}

void
TrayMenu::mononoke(void)
{
  QUrl url("http://mononoke-bt.org");

  QDesktopServices::openUrl(url);
}

void
TrayMenu::update(void)
{
  mn_updater.update();
}

void
TrayMenu::newMessage(void)
{
  QUrl url("http://mononoke-bt.org/inbox.php");
  QDesktopServices::openUrl(url);
}
