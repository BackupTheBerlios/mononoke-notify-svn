#include <QDomDocument>
#include <QFile>
#include <QDir>
#include <QtDebug>

#include "MononokeXml.hh"
#include "Updater.hh"
#include "App.hh"

using namespace MononokeNotify;


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
