/*!
** @file   ProgressDlg.hh
** @author Alexandre Bique <bique.alexandre@gmail.com>
** @date   Sat Dec  2 22:42:11 2006
**
** @brief  Defines MononokeNotify::ProgressDlg
**
**
*/


#ifndef _PROGRESSDLG_HH_
# define _PROGRESSDLG_HH_

# include <QDialog>

class QGridLayout;

namespace MononokeNotify {

  class HttpDownloader;

  class ProgressDlg : public QDialog {

  Q_OBJECT

  public:
    ProgressDlg();
    void		monitorDownload(HttpDownloader *	dl);
    void		canHide(void);

  private:
    QGridLayout *	grid;

  private slots:
    void		checkBoxClicked(int			state);
  };
}

#endif /* !_PROGRESSDLG_HH_ */
