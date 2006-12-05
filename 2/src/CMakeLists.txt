set(QT_USE_QTNETWORK TRUE)
set(QT_USE_QTXML TRUE)
include(${QT_USE_FILE})
set(MN_SRCS
  App.cc App.hh
  Config.cc Config.hh
  HttpDownloader.cc HttpDownloader.hh
  MononokeXml.cc MononokeXml.hh
  PrefsDlg.cc PrefsDlg.hh
  ProgressDlg.cc ProgressDlg.hh
  ProgressLabel.cc ProgressLabel.hh
  TorrentXml.cc TorrentXml.hh
  TrayMenu.cc TrayMenu.hh
  TrayMenuAction.cc TrayMenuAction.hh
  TrayMenuActionFrame.cc TrayMenuActionFrame.hh
  Updater.cc Updater.hh
  )
qt4_wrap_cpp(MN_SRCS
  App.hh
  HttpDownloader.hh
  MononokeXml.hh
  PrefsDlg.hh
  ProgressDlg.hh
  ProgressLabel.hh
  TrayMenu.hh
  TrayMenuAction.hh
  Updater.hh
  )
add_executable(mononoke-notify ${MN_SRCS})
target_link_libraries(mononoke-notify ${QT_LIBRARIES})
