/*!
** @file   Updater.hh
** @author Alexandre Bique <bique.alexandre@gmail.com>
** @date   Sat Dec  2 22:55:19 2006
**
** @brief  Defines MononokeNotify::Updater
**
**
*/


#ifndef _MNUPDATER_HH_
# define _MNUPDATER_HH_

# include <QObject>
# include <QString>
# include <QDomElement>

namespace MononokeNotify {
  class Updater : QObject {

  Q_OBJECT

  public:
    Updater();
    void	update(void);
    void	downloadIcon(QString&		url,
			     QString&		filename);
    void	downloadTeamIcon(qint32		id);
    void	downloadAnimeIcon(qint32	id);
    void	downloadGenreIcon(qint32	id);

    quint32 count;

  public slots:
    void	checkTheme(void);
    void	tryUpdateMenu(void);

  private:
    void	checkThemeFiles(QDomElement&	elem,
				QString&	base);
    void	downloadDefaultTheme(void);
    void	downloadUserInfoXml(void);
    void	unexistantTheme(void);
  };
}

#endif /* !_MNUPDATER_HH_ */
