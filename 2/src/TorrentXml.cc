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
