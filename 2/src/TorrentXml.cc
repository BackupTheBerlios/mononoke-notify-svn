
/*
**  Copyright 2006, Alexandre Bique <bique.alexandre@gmail.com>
**
**  This ./TorrentXml.cc is part of mononoke-notify-2.
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

#include "TorrentXml.hh"
#include "App.hh"

using namespace MononokeNotify;

void
   TorrentXml::parse(QDomNode & node)
{
   QDomNode
      child = node.firstChild();

   while (!child.isNull()) {
      handleNode(child);
      child = child.nextSibling();
   }
}

void
   TorrentXml::handleNode(QDomNode node)
{
   if (node.nodeName() == "id") {
      id = node.firstChild().nodeValue().toUInt();
   } else if (node.nodeName() == "leechers") {
      leechers = node.firstChild().nodeValue().toUInt();
   } else if (node.nodeName() == "seeders") {
      seeders = node.firstChild().nodeValue().toUInt();
   } else if (node.nodeName() == "name") {
      name = node.firstChild().nodeValue();
   } else if (node.nodeName() == "team") {
      team = node.firstChild().nodeValue().toUInt();
      mn_updater.downloadTeamIcon(team);
   } else if (node.nodeName() == "filename") {
      filename = node.firstChild().nodeValue();
   } else if (node.nodeName() == "seedratio") {
      seedratio = node.firstChild().nodeValue().toFloat();
   } else if (node.nodeName() == "free_download") {
      free_download = node.firstChild().nodeValue().toUInt();
   } else if (node.nodeName() == "category") {
      category = node.firstChild().nodeValue().toUInt();
      mn_updater.downloadAnimeIcon(category);
   } else if (node.nodeName() == "times_completed") {
      times_completed = node.firstChild().nodeValue().toUInt();
   } else if (node.nodeName() == "size") {
      size = node.firstChild().nodeValue().toULong();
   } else if (node.nodeName() == "added") {
      added = node.firstChild().nodeValue();
   } else if (node.nodeName() == "numfiles") {
      numfiles = node.firstChild().nodeValue().toUInt();
   } else if (node.nodeName() == "rating") {
      rating = node.firstChild().nodeValue().toFloat();
   } else if (node.nodeName() == "cat_name") {
      cat_name = node.firstChild().nodeValue();
   } else if (node.nodeName() == "is_hentai") {
      is_hentai = node.firstChild().nodeValue().toInt();
   } else if (node.nodeName() == "main_genre") {
      main_genre = node.firstChild().nodeValue().toUInt();
      mn_updater.downloadGenreIcon(main_genre);
   } else if (node.nodeName() == "team_name") {
      team_name = node.firstChild().nodeValue();
   }
}
