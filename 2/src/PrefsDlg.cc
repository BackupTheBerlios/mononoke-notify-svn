/*
**  Copyright 2006, Alexandre Bique <bique.alexandre@gmail.com>
**
**  This ./PrefsDlg.cc is part of mononoke-notify-2.
**
**  mononoke-notify-2 is free software; you can redistribute it and/or modify
**  it under the terms of the GNU General Public License as published by
**  the Free Software Foundation; either version 2 of the License, or
**  (at your option) any later version.
**
**  mononoke-notify-2 is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU General Public License for more details.
**
**  You should have received a copy of the GNU General Public License
**  along with mononoke-notify-2; if not, write to the Free Software
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
#include <QTextEdit>
#include <QFrame>
#include <QTabWidget>
#include <QLabel>
#include <QListWidget>
#include <QDir>
#include <QLineEdit>
#include <QSpinBox>
#include <QtDebug>
#include <QComboBox>
#include <QStyleFactory>
#include <QCheckBox>

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
  tab->addTab(makeProxyWidget(), "Proxy");
  tab->addTab(makeThemeWidget(), "Themes");
#if 0
  tab->addTab(makeDownloadThemeWidget(), "Dl des themes");
  tab->addTab(makeAboutWidget(), "A propos");
#endif
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
  resize(400, 400);

  load();
}

QWidget *
PrefsDlg::makeUserWidget(void)
{
  QWidget *w = new QWidget();
  QGridLayout *grid = new QGridLayout();
  QLabel *label = new QLabel("Login Mononoke-bt : ");

  leUserName = new QLineEdit("");
  grid->addWidget(label, 0, 0);
  grid->addWidget(leUserName, 0, 1);

  label = new QLabel("Taille des icones : ");
  sIconSize = new QSpinBox();
  sIconSize->setMaximum(42);
  sIconSize->setMinimum(10);
  grid->addWidget(label, 1, 0);
  grid->addWidget(sIconSize, 1, 1);

  label = new QLabel("Torrents a afficher : ");
  sNbrTorrents = new QSpinBox();
  sNbrTorrents->setMaximum(10);
  sNbrTorrents->setMinimum(3);
  grid->addWidget(label, 2, 0);
  grid->addWidget(sNbrTorrents, 2, 1);

  label = new QLabel("Style : ");
  cbQtStyle = new QComboBox();
  cbQtStyle->insertItems(0, QStyleFactory::keys());
  grid->addWidget(label, 3, 0);
  grid->addWidget(cbQtStyle, 3, 1);

  label = new QLabel("Fermer automatiquement\n"
		     "la fenetre de telechargement");
  cbDlProgress = new QCheckBox();
  grid->addWidget(label, 4, 0);
  grid->addWidget(cbDlProgress, 4, 1);
  grid->setRowStretch(5, 100);
  w->setLayout(grid);
  return w;
}

QWidget *
PrefsDlg::makeProxyWidget(void)
{
  QWidget *w = new QWidget();
  QGridLayout *grid = new QGridLayout();

  cbProxy = new QCheckBox("J'utilise un proxy");
  grid->addWidget(cbProxy, 0, 0);

  QLabel *label = new QLabel("Serveur :");
  leProxyServer = new QLineEdit("");
  grid->addWidget(label, 1, 0);
  grid->addWidget(leProxyServer, 1, 1);

  label = new QLabel("Port :");
  leProxyPort = new QLineEdit("");
  grid->addWidget(label, 2, 0);
  grid->addWidget(leProxyPort, 2, 1);

  label = new QLabel("Utilisateur :");
  leProxyUser = new QLineEdit("");
  grid->addWidget(label, 3, 0);
  grid->addWidget(leProxyUser, 3, 1);

  label = new QLabel("Pass :");
  leProxyPass = new QLineEdit("");
  leProxyPass->setEchoMode(QLineEdit::Password);
  grid->addWidget(label, 4, 0);
  grid->addWidget(leProxyPass, 4, 1);
  grid->setRowStretch(5, 100);
  w->setLayout(grid);

  return (w);
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

  return (lwTheme);
}

QWidget *
PrefsDlg::makeDownloadThemeWidget(void)
{
  QWidget *w = new QWidget();

  return (w);
}

QWidget *
PrefsDlg::makeAboutWidget(void)
{
  return (0);
}

void
PrefsDlg::ok(void)
{
  apply();
  hide();
  mn_updater.update();
}

void
PrefsDlg::apply(void)
{
  QApplication::setStyle(cbQtStyle->currentText());
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
  /* User */
  mn_config.userName = leUserName->text();
  mn_config.iconSize = sIconSize->value();
  mn_config.nbrTorrent = sNbrTorrents->value();
  mn_config.qtStyle = cbQtStyle->currentText();
  mn_config.progressDlgClose = cbDlProgress->checkState();
  /* Proxy */
  mn_config.proxy = cbProxy->checkState();
  mn_config.proxyServer = leProxyServer->text();
  mn_config.proxyPort = leProxyPort->text().toInt();
  mn_config.proxyUser = leProxyUser->text();
  mn_config.proxyPass = leProxyPass->text();
  /* Theme */
  if (lwTheme->currentItem())
    mn_config.theme = lwTheme->currentItem()->text();
  mn_config.save();
}

void
PrefsDlg::load(void)
{
  /* User */
  leUserName->setText(mn_config.userName);
  sIconSize->setValue(mn_config.iconSize);
  sNbrTorrents->setValue(mn_config.nbrTorrent);
  cbQtStyle->setCurrentIndex(cbQtStyle->findText(mn_config.qtStyle));
  cbDlProgress->setCheckState((Qt::CheckState)mn_config.progressDlgClose);
  /* Proxy */
  cbProxy->setCheckState((Qt::CheckState)mn_config.proxy);
  leProxyServer->setText(mn_config.proxyServer);
  leProxyPort->setText(QString::number(mn_config.proxyPort));
  leProxyUser->setText(mn_config.proxyUser);
  leProxyPass->setText(mn_config.proxyPass);
  /* Theme */
  if (lwTheme->count() > 0)
    lwTheme->setItemSelected(lwTheme->findItems(mn_config.theme,
						Qt::MatchExactly)[0], 1);
}
