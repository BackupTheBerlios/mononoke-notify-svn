
/*
**  Copyright 2006, Alexandre Bique <bique.alexandre@gmail.com>
**
**  This ./TrayMenuAction.cc is part of mononoke-notify-2.
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

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QIcon>
#include <QDir>
#include <QDesktopServices>

#include "App.hh"
#include "TrayMenuAction.hh"
#include "TrayMenuActionFrame.hh"

using namespace MononokeNotify;

TrayMenuAction::TrayMenuAction(QDomElement &	elem,
			       TorrentXml &	t,
			       QWidget *	parent)
  : QWidgetAction(parent)
{
  widget = new TrayMenuActionFrame(parent);
  QDomElement child = elem.firstChildElement();
  QHBoxLayout *h = new QHBoxLayout(widget);

  url = QUrl("http://mononoke-bt.org/gettorrent.php/"
	     + t.filename + "?id=" + QString::number(t.id) + "&r=1");

  h->setSpacing(2);
  h->setMargin(2);

  while (!child.isNull()) {
    if (child.nodeName() == "Text") {
      h->addWidget(new QLabel(child.attribute("val"), widget));
    } else if (child.nodeName() == "TeamIcon") {
      QString filename = QDir::homePath()
	+ "/.config/mononoke-notify-2/data/team_" + QString::number(t.team)
	+ ".jpg";
      QLabel *l = new QLabel(widget);

      l->setPixmap(QPixmap(filename).scaled(mn_config.iconSize,
					    mn_config.iconSize));
      h->addWidget(l);
    } else if (child.nodeName() == "AnimeIcon") {
      QString filename = QDir::homePath()
	+ "/.config/mononoke-notify-2/data/anime_" + QString::number(t.category)
	+ ".jpg";
      QLabel *l = new QLabel(widget);

      l->setPixmap(QPixmap(filename).scaled(mn_config.iconSize,
					    mn_config.iconSize));
      h->addWidget(l);
    } else if (child.nodeName() == "MainGenreIcon") {
      if (t.main_genre != 0) {
	QString filename = QDir::homePath()
	  + "/.config/mononoke-notify-2/data/genre_"
	  + QString::number(t.main_genre)
	  + ".jpg";
	QLabel *l = new QLabel(widget);

	l->setPixmap(QPixmap(filename).scaled(mn_config.iconSize,
					      mn_config.iconSize));
	h->addWidget(l);
      }
    } else if (child.nodeName() == "PackageIcon") {
      QString filename = QDir::homePath()
	+ "/.config/mononoke-notify-2/themes/default/"
	+ child.attribute("src" + QString::number(t.free_download));
      QLabel *l = new QLabel(widget);

      l->setPixmap(QPixmap(filename).scaled(mn_config.iconSize,
					    mn_config.iconSize));
      h->addWidget(l);
    } else if (child.nodeName() == "Id") {
      h->addWidget(new QLabel(QString::number(t.id), widget));
    } else if (child.nodeName() == "NbrLeech") {
      h->addWidget(new QLabel(QString::number(t.leechers), widget));
    } else if (child.nodeName() == "NbrSeed") {
      h->addWidget(new QLabel(QString::number(t.seeders), widget));
    } else if (child.nodeName() == "Name") {
      h->addWidget(new QLabel(t.name, widget));
    } else if (child.nodeName() == "Team") {
      h->addWidget(new QLabel(QString::number(t.team), widget));
    } else if (child.nodeName() == "FileName") {
      h->addWidget(new QLabel(t.filename, widget));
    } else if (child.nodeName() == "SeedRatio") {
      h->addWidget(new QLabel(QString::number(t.seedratio), widget));
    } else if (child.nodeName() == "FreeDownload") {
      h->addWidget(new QLabel(QString::number(t.free_download), widget));
    } else if (child.nodeName() == "Category") {
      h->addWidget(new QLabel(QString::number(t.category), widget));
    } else if (child.nodeName() == "TimesCompleted") {
      h->addWidget(new QLabel(QString::number(t.times_completed), widget));
    } else if (child.nodeName() == "Size") {
      h->addWidget(new QLabel(QString::number((double) t.size / 1024 / 1024)
			      + " Mo", widget));
    } else if (child.nodeName() == "Added") {
      h->addWidget(new QLabel(t.added, widget));
    } else if (child.nodeName() == "NumFiles") {
      h->addWidget(new QLabel(QString::number(t.numfiles), widget));
    } else if (child.nodeName() == "Rating") {
      h->addWidget(new QLabel(QString::number(t.rating), widget));
    } else if (child.nodeName() == "CatName") {
      h->addWidget(new QLabel(t.cat_name, widget));
    } else if (child.nodeName() == "IsHentai") {
      if (t.is_hentai)
	h->addWidget(new QLabel("hentai", widget));
    } else if (child.nodeName() == "MainGenre") {
      h->addWidget(new QLabel(QString::number(t.main_genre), widget));
    } else if (child.nodeName() == "TeamName") {
      h->addWidget(new QLabel(t.team_name, widget));
    }
    child = child.nextSiblingElement();
  }
  h->addStretch(100);
  widget->setLayout(h);
  connect(this, SIGNAL(triggered()), this, SLOT(clicked()));
}

QWidget *
TrayMenuAction::createWidget(QWidget * parent)
{
  widget->setParent(parent);
  return widget;
}

void
TrayMenuAction::clicked(void)
{
  QDesktopServices::openUrl(url);
}
