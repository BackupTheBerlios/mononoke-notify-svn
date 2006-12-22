
/*
**  Copyright 2006, Alexandre Bique <bique.alexandre@gmail.com>
**
**  This ./MononokeXml.cc is part of mononoke-notify-2.
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
** @file   MononokeXml.cc
** @author Alexandre Bique <bique.alexandre@gmail.com>
** @date   Sun Dec 10 21:36:18 2006
**
** @brief  Implementation of MononokeNotify::MononokeXml
**
**
*/


#include <QDomDocument>
#include <QFile>
#include <QDir>
#include <QtDebug>

#include "MononokeXml.hh"
#include "Updater.hh"
#include "App.hh"

using namespace MononokeNotify;


/** @brief parses a xml file */
void
MononokeXml::parse(void)
{
  QString		error("");
  QDomDocument	doc("MononokeXml");
  QFile		file(QDir::homePath()
		     + "/.config/mononoke-notify-2/user_info.xml");

  if (!file.open(QIODevice::ReadOnly))
    return;
  if (!doc.setContent(&file, &error)) {
    qDebug() << "Oups " + error;
    file.close();
    return;
  }
  file.close();

  QDomElement		elem = doc.documentElement();
  QDomNode		node = elem.firstChild();

  while (!node.isNull()) {
    handleNode(node);
    node = node.nextSibling();
  }

  if (download != 0)
    ratio = (float) upload / download;
  else
    ratio = -1;
  if (download + download_free != 0)
    trueRatio = (float) upload / (download + download_free);
  else
    trueRatio = -1;

  mn_updater.tryUpdateMenu();
}


/*!
** @param node xml node
** @brief handle a node and store its data
*/
void
MononokeXml::handleNode(QDomNode & node)
{
  if (node.nodeName() == "id") {
    id = node.firstChild().nodeValue().toUInt();
  } else if (node.nodeName() == "upload") {
    upload = node.firstChild().nodeValue().toULongLong();
  } else if (node.nodeName() == "download") {
    download = node.firstChild().nodeValue().toULongLong();
  } else if (node.nodeName() == "download_free") {
    download_free = node.firstChild().nodeValue().toULongLong();
  } else if (node.nodeName() == "show_hentai") {
    show_hentai = node.firstChild().nodeValue();
  } else if (node.nodeName() == "class") {
    class_ = node.firstChild().nodeValue().toUInt();
  } else if (node.nodeName() == "unread") {
    unread = node.firstChild().nodeValue().toUInt();
  } else if (node.nodeName() == "need_seed") {
    QDomNode child = node.firstChild();
    need_seed.count = 0;
    while (!child.isNull() && need_seed.count < _MN_TORRENTLIST_MAX_) {
      need_seed.t[need_seed.count].parse(child);
      need_seed.count++;
      child = child.nextSibling();
    }
  } else if (node.nodeName() == "sorties") {
    QDomNode child = node.firstChild();
    sorties.count = 0;
    while (!child.isNull() && sorties.count < _MN_TORRENTLIST_MAX_) {
      sorties.t[sorties.count].parse(child);
      sorties.count++;
      child = child.nextSibling();
    }
  } else if (node.nodeName() == "latest") {
    QDomNode child = node.firstChild();
    latest.count = 0;
    while (!child.isNull() && latest.count < _MN_TORRENTLIST_MAX_) {
      latest.t[latest.count].parse(child);
      latest.count++;
      child = child.nextSibling();
    }
  }
}
