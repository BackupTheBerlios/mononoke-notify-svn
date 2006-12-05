/*!
** @file   TrayMenuActionFrame.hh
** @author Alexandre Bique <bique.alexandre@gmail.com>
** @date   Sat Dec  2 22:54:23 2006
**
** @brief  Defines MononokeNotify::TrayMenuActionFrame
**
**
*/


#ifndef _MNTRAYMENUACTIONFRAME_HH_
# define _MNTRAYMENUACTIONFRAME_HH_

# include <QFrame>

namespace MononokeNotify {
  class TrayMenuActionFrame : public QFrame {

  public:
    TrayMenuActionFrame();
    void	enterEvent(QEvent*	event);
    void	leaveEvent(QEvent*	event);

  };
}

#endif /* !_MNTRAYMENUACTIONFRAME_HH_ */
