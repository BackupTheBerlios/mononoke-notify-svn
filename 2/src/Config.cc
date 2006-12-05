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

#include "Config.hh"

using namespace MononokeNotify;

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

  userName = elem.firstChildElement("UserName").attribute("val");
  theme = elem.firstChildElement("Theme").attribute("val");
  iconSize = elem.firstChildElement("IconSize").attribute("val").toInt();
  nbrTorrent = elem.firstChildElement("NbrTorrent").attribute("val").toInt();
  progressDlgClose = elem.firstChildElement("ProgressDlgClose")
    .attribute("val").toInt();
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
}

/** @brief Saves configuration to ~/.config/mononoke-notify-2/config.xml */
void
Config::save(void)
{
  QString filename(QDir::homePath() + "/.config/mononoke-notify-2/config.xml");
  QString data("");
  QFile file(filename);

  data += "<Config>\n";
  data += "  <UserName val=\"" + userName + "\"/>\n"
    + "  <Theme val=\"" + theme + "\"/>\n"
    + "  <IconSize val=\"" + QString::number(iconSize) + "\"/>\n"
    + "  <NbrTorrent val=\"" + QString::number(nbrTorrent) + "\"/>\n"
    + "  <ProgressDlgClose val=\"" + QString::number(progressDlgClose) + "\"/>\n"
    + "</Config>\n\n";

  file.open(QIODevice::WriteOnly);
  file.write(data.toAscii());
  file.close();
}
