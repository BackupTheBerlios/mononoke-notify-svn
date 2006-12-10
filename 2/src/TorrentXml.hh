/*!
** @file   TorrentXml.hh
** @author Alexandre Bique <bique.alexandre@gmail.com>
** @date   Sat Dec  2 22:43:38 2006
**
** @brief  Defines MononokeNotify::TorrentXml
**
**
*/


#ifndef _MNTORRENTXML_HH_
# define _MNTORRENTXML_HH_

# include <QObject>
# include <QDomNode>

namespace MononokeNotify {
  class TorrentXml : public QObject {

  public:
    void	parse(QDomNode &	node);

    quint32	id;
    quint32	leechers;
    quint32	seeders;
    QString	name;
    quint32	team;
    QString	filename;
    float	seedratio;
    quint32	free_download;
    quint32	category;
    quint32	times_completed;
    quint64	size;
    QString	added;
    quint32	numfiles;
    float	rating;
    QString	cat_name;
    bool	is_hentai;
    quint32	main_genre;
    QString	team_name;

  private:
    void	handleNode(QDomNode	node);

  };
}

#endif /* !_MNTORRENTXML_HH_ */
