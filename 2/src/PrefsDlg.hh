/*!
** @file   PrefsDlg.hh
** @author Alexandre Bique <bique.alexandre@gmail.com>
** @date   Sat Dec  2 22:39:43 2006
**
** @brief  Defines MononokeNotify::PrefsDlg
**
**
*/


#ifndef _MNPREFSDLG_HH_
# define _MNPREFSDLG_HH_

# include <QDialog>

class QLineEdit;
class QSpinBox;
class QListWidget;

namespace MononokeNotify {
  class PrefsDlg : public QDialog {

  Q_OBJECT

  public:
    PrefsDlg();

  private:
    void		save();
    void		load();
    QWidget *		makeUserWidget(void);
    QWidget *		makeThemeWidget(void);
    QWidget *		makeDownloadThemeWidget(void);
    QWidget *		makeAboutWidget(void);
    QLineEdit *		leUserName;
    QSpinBox *		sNbrTorrents;
    QSpinBox *		sIconSize;
    QListWidget *	lwTheme;

  private slots:
    void		apply(void);
    void		cancel(void);
    void		ok(void);

  };
}

#endif /* !_MNPREFSDLG_HH_ */
