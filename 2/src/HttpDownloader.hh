/*!
** @file   HttpDownloader.hh
** @author Alexandre Bique <bique.alexandre@gmail.com>
** @date   Sat Dec  2 19:00:38 2006
**
** @brief  Defines MononokeNotify::HttpDownloader classe
**
**
*/


#ifndef _MNHTTPDOWNLOADER_HH_
# define _MNHTTPDOWNLOADER_HH_

# include <QObject>
# include <QFile>
# include <QHttp>

namespace MononokeNotify {
  class HttpDownloader : public QObject {

  Q_OBJECT

  public:
    HttpDownloader(QString &	url,
		   QString &	filename,
		   QObject *	parent = NULL);

    static int	count(void);

    QString	name;
    QHttp	*http;
    QFile	*file;

  signals:
    void	finished(void);

  private slots:
    void	done(bool	error);

  };
}
#endif
