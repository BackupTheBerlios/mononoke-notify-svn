/*!
** @file   TrayMenu.hh
** @author Alexandre Bique <bique.alexandre@gmail.com>
** @date   Sat Dec  2 22:44:20 2006
**
** @brief  Defines MononokeNotify::TrayMenu
**
**
*/


#ifndef _MNTRAYMENU_HH_
# define _MNTRAYMENU_HH_

# include <QMenu>
# include <QDomElement>

# include "MononokeXml.hh"

namespace MononokeNotify {
  /** @brief The menu displayed when the user right click */
  class TrayMenu : public QMenu {

  Q_OBJECT

  public:
    TrayMenu(void);

    void	generate(void);

  private:
    void	appendSepparator(void);
    void	parse(QString&			filename);
    void	handleTrayMenu(QDomElement&	elem);
    void	handleItem(QDomElement&		elem);
    QMenu*	handleTorrentList(QDomElement	elem,
				  TorrentList&	tl);

  private slots:
    void	showPrefs(void);
    void	mononoke(void);
    void	newMessage(void);
    void	update(void);
  };
}

#endif /* !_MNTRAYMENU_HH_ */
