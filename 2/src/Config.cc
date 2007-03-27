
/*
**  Copyright 2006, Alexandre Bique <bique.alexandre@gmail.com>
**
**  This ./Config.cc is part of mononoke-notify-2.
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
** @file   Config.cc
** @author Alexandre Bique <bique.alexandre@gmail.com>
** @date   Sat Dec  2 18:55:49 2006
**
** @brief  Implements MononokeNotify::Config class
**
**
*/

#include <QtDebug>
#include <QDir>
#include <QDomDocument>
#include <QApplication>

#include "Config.hh"

using namespace MononokeNotify;

Config::Config()
  : QObject(), userName(), theme(), qtStyle(), iconSize(42),
    nbrTorrent(6), progressDlgClose(1), proxy(0), proxyServer(),
    proxyPort(3128), proxyUser(), proxyPass()
{
}

/** @brief Initialize configuration */
void
Config::init(void)
{
  loadDefault();
  checkPath();
}

/** @brief Creates configurations paths if they don't exist */
void
Config::checkPath(void)
{
  QString	path(QDir::homePath() + "/.config/mononoke-notify-2");
  QString	tmp(path + "/data");
  QDir		dir;

  /* Check ~/.config/mononoke-notify-2 */
  if (!dir.exists(path))
    if (!dir.mkpath(path)) {
      qDebug() << path;
      return;
    }

  /* Check ~/.config/mononoke-notify-2/data */
  if (!dir.exists(tmp))
    if (!dir.mkpath(tmp)) {
      qDebug() << tmp;
      return;
    }

  /* Check ~/.config/mononoke-notify-2/themes */
  tmp = path + "/themes";
  if (!dir.exists(tmp))
    if (!dir.mkpath(tmp)) {
      qDebug() << tmp;
      return;
    }
}

/** @brief Loads the config file */
void
Config::load(void)
{
  QFile file(QDir::homePath() + "/.config/mononoke-notify-2/config.xml");
  /* As-t-on un fichier de config ? */
  if (!file.exists()) {
    /* On sauve la config par defaut et on se casse */
    save();
    return;
  }
  if (!file.open(QIODevice::ReadOnly))
    return;

  QDomDocument doc("Config");
  if (!doc.setContent(&file)) {
    file.close();
    return;
  }
  file.close();

  QDomElement elem = doc.documentElement();

  userName = elem.firstChildElement("UserName").attribute("val", "BabaLi");
  theme = elem.firstChildElement("Theme").attribute("val", "default");
  qtStyle = elem.firstChildElement("QtStyle").attribute("val", "Plastique");
  QApplication::setStyle(qtStyle);
  iconSize = elem.firstChildElement("IconSize").attribute("val", "32").toInt();
  nbrTorrent = elem.firstChildElement("NbrTorrent").attribute("val", "6").toInt();
  progressDlgClose = elem.firstChildElement("ProgressDlgClose")
    .attribute("val", "0").toInt();
  proxy = elem.firstChildElement("Proxy").attribute("state", "2").toInt();
  proxyServer = elem.firstChildElement("Proxy").attribute("server");
  proxyPort = elem.firstChildElement("Proxy").attribute("port").toInt();
  proxyUser = elem.firstChildElement("Proxy").attribute("user");
  proxyPass = elem.firstChildElement("Proxy").attribute("pass");
}

/** @brief Loads default values */
void
Config::loadDefault(void)
{
  userName = "BabaLi";
  theme = "default";
  nbrTorrent = 6;
  iconSize = 32;
  progressDlgClose = 0;
  qtStyle = "Plastique";
}

/** @brief Saves configuration to ~/.config/mononoke-notify-2/config.xml */
void
Config::save(void)
{
  QString filename(QDir::homePath() + "/.config/mononoke-notify-2/config.xml");
  QFile file(filename);
  QDomDocument doc;

  QDomElement config = doc.createElement("Config");
  QDomElement element = doc.createElement("UserName");
  element.setAttribute("val", userName);
  config.appendChild(element);
  element = doc.createElement("Theme");
  element.setAttribute("val", theme);
  config.appendChild(element);
  element = doc.createElement("IconSize");
  element.setAttribute("val", iconSize);
  config.appendChild(element);
  element = doc.createElement("QtStyle");
  element.setAttribute("val", qtStyle);
  config.appendChild(element);
  element = doc.createElement("NbrTorrent");
  element.setAttribute("val", nbrTorrent);
  config.appendChild(element);
  element = doc.createElement("ProgressDlgClose");
  element.setAttribute("val", progressDlgClose);
  config.appendChild(element);
  element = doc.createElement("Proxy");
  element.setAttribute("state", proxy);
  element.setAttribute("server", proxyServer);
  element.setAttribute("port", proxyPort);
  element.setAttribute("user", proxyUser);
  element.setAttribute("pass", proxyPass);
  config.appendChild(element);
  doc.appendChild(config);

  file.open(QIODevice::WriteOnly);
  file.write(doc.toByteArray(2));
  file.close();
}
