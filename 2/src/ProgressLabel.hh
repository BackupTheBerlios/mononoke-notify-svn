/*!
** @file   ProgressLabel.hh
** @author Alexandre Bique <bique.alexandre@gmail.com>
** @date   Sat Dec  2 22:40:55 2006
**
** @brief  Defines MononokeNotify::ProgressLabel
**
**
*/


#ifndef _PROGRESSLABEL_HH_
# define _PROGRESSLABEL_HH_

# include <QLabel>

namespace MononokeNotify {
  class ProgressLabel : public QLabel {

  Q_OBJECT

  public:
    ProgressLabel();

  public slots:
    void	update(int	current,
		       int	total);

  };
}

#endif /* !_PROGRESSLABEL_HH_ */
