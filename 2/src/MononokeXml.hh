/*!
** @file   MononokeXml.hh
** @author Alexandre Bique <bique.alexandre@gmail.com>
** @date   Sat Dec  2 22:32:49 2006
**
** @brief  The definition of MononokeNotify::MononokeXml
**
**
*/


#ifndef _MNMONONOKEXML_HH_
# define _MNMONONOKEXML_HH_

# include <QObject>
# include <QDomNode>

# include "TorrentXml.hh"

namespace MononokeNotify {

# define _MN_TORRENTLIST_MAX_ 15

  struct TorrentList {
    TorrentXml		t[_MN_TORRENTLIST_MAX_];
    int			count;
  };

  /*! @brief Parses xml from mononoke-bt */
  class MononokeXml : public QObject {

  Q_OBJECT

  public slots:
    void		parse(void);

  public:
    quint32		id;
    quint64		upload;
    quint64		download;
    quint64		download_free;
    QString		show_hentai;
    qint32		class_;
    quint32		unread;
    TorrentList		need_seed;
    TorrentList		sorties;
    TorrentList		latest;
    float		ratio;
    float		trueRatio;

  private:
    void		handleNode(QDomNode&	node);
  };
}
#endif /* !_MNMONONOKEXML_HH_ */
