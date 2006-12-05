/*!
** @file   TrayMenuAction.hh
** @author Alexandre Bique <bique.alexandre@gmail.com>
** @date   Sat Dec  2 22:52:27 2006
**
** @brief  Defines MononokeNotify::TrayMenuAction
**
**
*/


#ifndef _TRAYMENUACTION_HH_
# define _TRAYMENUACTION_HH_

# include <QDomElement>
# include <QUrl>
# include <QWidgetAction>
# include <QFrame>

# include "TorrentXml.hh"

namespace MononokeNotify {
  class TrayMenuAction : public QWidgetAction {

  Q_OBJECT

  public:
    TrayMenuAction(QDomElement&		elem,
		   TorrentXml&		t);

  protected:
    QWidget*	createWidget(QWidget*	parent);

  private:
    QFrame*	widget;
    QUrl	url;

  private slots:
    void	clicked(void);

  };
}

#endif /* !_TRAYMENUACTION_HH_ */
