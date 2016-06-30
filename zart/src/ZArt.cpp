/** -*- mode: c++ ; c-basic-offset: 2 -*-
 * @file   ZArt.cpp
 * @author Sebastien Fourey
 * @date   July 2010
 *
 * This file is part of the ZArt software's source code.
 *
 * Copyright Sebastien Fourey / GREYC Ensicaen (2010-...)
 *
 *                    https://foureys.users.greyc.fr/
 *
 * This software is a computer program whose purpose is to demonstrate
 * the possibilities of the GMIC image processing language by offering the
 * choice of several manipulations on a video stream aquired from a webcam. In
 * other words, ZArt is a GUI for G'MIC real-time manipulations on the output
 * of a webcam.
 *
 * This software is governed by the CeCILL  license under French law and
 * abiding by the rules of distribution of free software.  You can  use,
 * modify and/ or redistribute the software under the terms of the CeCILL
 * license as circulated by CEA, CNRS and INRIA at the following URL
 * "http://www.cecill.info". See also the directory "Licence" which comes
 * with this source code for the full text of the CeCILL license.
 *
 * As a counterpart to the access to the source code and  rights to copy,
 * modify and redistribute granted by the license, users are provided only
 * with a limited warranty  and the software's author,  the holder of the
 * economic rights,  and the successive licensors  have only  limited
 * liability.
 *
 * In this respect, the user's attention is drawn to the risks associated
 * with loading,  using,  modifying and/or developing or reproducing the
 * software by the user in light of its specific status of free software,
 * that may mean  that it is complicated to manipulate,  and  that  also
 * therefore means  that it is reserved for developers  and  experienced
 * professionals having in-depth computer knowledge. Users are therefore
 * encouraged to load and test the software's suitability as regards their
 * requirements in conditions enabling the security of their systems and/or
 * data to be ensured and,  more generally, to use and operate it in the
 * same conditions as regards security.
 *
 * The fact that you are presently reading this means that you have had
 * knowledge of the CeCILL license and that you accept its terms.
 */

#include <iostream>
using namespace std;
#include <QApplication>
#include <QMessageBox>
#include <QSplashScreen>
#include "WebcamSource.h"
#include "Common.h"
#include "MainWindow.h"
#include "gmic.h"

#ifdef _IS_UNIX_
#include <signal.h>
void onSigQuit(int)
{
  std::cout << "Got a Quit/Interrupt signal from keyboard.\n";
  qApp->closeAllWindows();
  exit(0);
}
#endif

int main(int argc, char *argv[])
{
#ifdef _IS_UNIX_
  signal(SIGQUIT,onSigQuit);
  signal(SIGINT,onSigQuit);
#endif
  QApplication app(argc, argv);
  app.setWindowIcon(QIcon(":images/gmic_hat.png"));
  QCoreApplication::setOrganizationName("GREYC");
  QCoreApplication::setOrganizationDomain("greyc.fr");
  QCoreApplication::setApplicationName("ZArt");
  QCoreApplication::setAttribute(Qt::AA_DontUseNativeMenuBar);

  QStringList args = app.arguments();
  QStringList::iterator it = args.begin();
  while (it != args.end()) {
    if (it->startsWith("-h") || it->startsWith("--help")) {
      cout << "Usage:" << endl
           << "       "
           << QFileInfo(argv[0]).baseName().toLatin1().constData()
          << " [options]" << endl
          << "  " << "Options: " << endl
          << "      --clear-cams  : Clear webcam cache." << endl
          << "      --help | -h   : print this help." << endl
          << endl;
      exit(EXIT_SUCCESS);
    }
    ++it;
  }
  QSplashScreen splashScreen(QPixmap(":/images/splash.png"));
  splashScreen.show();
  app.processEvents();
  if (QApplication::arguments().contains("--clear-cams")) {
    WebcamSource::clearSavedSettings();
  }
  WebcamSource::retrieveWebcamResolutions(WebcamSource::getWebcamList(),
                                          &splashScreen);
  if (! gmic::init_rc()) {
    cerr << "[ZArt] Warning: Could not create resources directory.\n";
  }
  MainWindow mainWindow;
  mainWindow.show();
  splashScreen.finish(&mainWindow);
  return app.exec();
}
