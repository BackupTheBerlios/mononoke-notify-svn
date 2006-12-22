
/*
**  Copyright 2006, Alexandre Bique <bique.alexandre@gmail.com>
**
**  This ./PrefsDlg.cc is part of mononoke-notify-2.
**
**  Foobar is free software; you can redistribute it and/or modify
**  it under the terms of the GNU General Public License as published by
**  the Free Software Foundation; either version 2 of the License, or
**  (at your option) any later version.
**
**  Foobar is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU General Public License for more details.
**
**  You should have received a copy of the GNU General Public License
**  along with Foobar; if not, write to the Free Software
**  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
**
*/

/*!
** @file   PrefsDlg.cc
** @author Alexandre Bique <bique.alexandre@gmail.com>
** @date   Sun Dec 10 21:40:55 2006
**
** @brief  Implementation of MononokeNotify::PrefsDlg
**
**
*/


#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QFrame>
#include <QTabWidget>
#include <QLabel>
#include <QListWidget>
#include <QDir>
#include <QLineEdit>
#include <QSpinBox>
#include <QtDebug>

#include "App.hh"
#include "PrefsDlg.hh"

using namespace MononokeNotify;

PrefsDlg::PrefsDlg()
  : QDialog()
{
  QVBoxLayout *v1 = new QVBoxLayout();
  QHBoxLayout *h1 = new QHBoxLayout();
  QTabWidget *tab = new QTabWidget();

  tab->addTab(makeUserWidget(), "Utilisateur");
  tab->addTab(makeThemeWidget(), "Themes");
  tab->addTab(makeDownloadThemeWidget(), "Dl des themes");
  tab->addTab(makeAboutWidget(), "A propos");
  v1->addWidget(tab);

  QFrame *f = new QFrame();

  f->setFrameStyle(QFrame::Sunken | QFrame::HLine);
  v1->addWidget(f);

  h1->addStretch(100);
  QPushButton *b = new QPushButton("Ok");

  connect(b, SIGNAL(clicked()), this, SLOT(ok()));
  h1->addWidget(b);
  b = new QPushButton("Appliquer");
  connect(b, SIGNAL(clicked()), this, SLOT(apply()));
  h1->addWidget(b);
  b = new QPushButton("Annuler");
  connect(b, SIGNAL(clicked()), this, SLOT(cancel()));
  h1->addWidget(b);
  v1->addLayout(h1);

  setLayout(v1);

  load();
}

QWidget *
PrefsDlg::makeUserWidget(void)
{
  QWidget *w = new QWidget();
  QGridLayout *grid = new QGridLayout();
  QLabel *l = new QLabel("Login Mononoke-bt : ");

  leUserName = new QLineEdit("");
  grid->addWidget(l, 0, 0);
  grid->addWidget(leUserName, 0, 1);
  l = new QLabel("Taille des icones : ");
  sIconSize = new QSpinBox();
  sIconSize->setMaximum(42);
  sIconSize->setMinimum(10);
  grid->addWidget(l, 1, 0);
  grid->addWidget(sIconSize, 1, 1);
  l = new QLabel("Torrents a afficher : ");
  sNbrTorrents = new QSpinBox();
  sNbrTorrents->setMaximum(10);
  sNbrTorrents->setMinimum(3);
  grid->addWidget(l, 2, 0);
  grid->addWidget(sNbrTorrents, 2, 1);
  grid->setRowStretch(3, 100);
  w->setLayout(grid);
  return w;
}

QWidget *
PrefsDlg::makeThemeWidget(void)
{
  lwTheme = new QListWidget();
  lwTheme->setSelectionMode(QAbstractItemView::SingleSelection);
  QDir d(QDir::homePath() + "/.config/mononoke-notify-2/themes/");
  QStringList sl = d.entryList();

  d.setFilter(QDir::Dirs);
  for (int i = 0; i < sl.size(); i++)
    if (sl[i] != "." && sl[i] != "..")
      lwTheme->addItem(sl[i]);

  return lwTheme;
}

QWidget *
PrefsDlg::makeDownloadThemeWidget(void)
{
  QWidget *w = new QWidget();

  return w;
}

QWidget *
PrefsDlg::makeAboutWidget(void)
{
  return new QLabel("");
}

void
PrefsDlg::ok(void)
{
  save();
  hide();
}

void
PrefsDlg::apply(void)
{
  save();
}

void
PrefsDlg::cancel(void)
{
  hide();
  load();
}

void
PrefsDlg::save(void)
{
  mn_config.userName = leUserName->text();
  mn_config.iconSize = sIconSize->value();
  mn_config.nbrTorrent = sNbrTorrents->value();
  if (lwTheme->currentItem())
    mn_config.theme = lwTheme->currentItem()->text();
  mn_config.save();
}

void
PrefsDlg::load(void)
{
  leUserName->setText(mn_config.userName);
  sIconSize->setValue(mn_config.iconSize);
  sNbrTorrents->setValue(mn_config.nbrTorrent);
  lwTheme->setItemSelected(lwTheme->findItems(mn_config.theme,
					      Qt::MatchExactly)[0], 1);
}
