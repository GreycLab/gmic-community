/** -*- mode: c++ ; c-basic-offset: 2 -*-
 * @file   WebcamGrabber.h
 * @author Sebastien Fourey
 * @date   July 2010
 * @brief  Declaration of the class ImageFilter
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
 *
 */

#ifndef _WEBCAMGRABBER_H_
#define _WEBCAMGRABBER_H_

#if defined(HAS_OPENCV2_HEADERS) || defined(OPENCV2_HEADERS)
#include <opencv2/core/core_c.h>
#include <opencv2/highgui/highgui_c.h>
#else
#include <cv.h>
#include <highgui.h>
#endif
#include <QVector>
#include <QList>
#include <QSize>
#include "ImageSource.h"

class QSplashScreen;
class QStatusBar;

class WebcamSource : public ImageSource {
public:
  WebcamSource();
  ~WebcamSource();
  int cameraIndex();
  void capture();
  void setCameraIndex(int i);
  void stop();
  void start();
  QSize captureSize();
  void setCaptureSize(int width, int height);
  void setCaptureSize(const QSize & size);
  static const QList<int> & getWebcamList();
  static const QList<int> & getCachedWebcamList();
  static int getFirstUnusedWebcam();
  static bool isWebcamUnused(int index);
  static void retrieveWebcamResolutions(const QList<int> & camList, QSplashScreen * splashScreen = 0, QStatusBar * statusBar = 0);
  static const QList<QSize> & webcamResolutions(int index);
  static void clearSavedSettings();
private:
  CvCapture *_capture;
  int _cameraIndex;
  QSize _captureSize;
  static QList<int> _webcamList;
  static QVector< QList<QSize> > _webcamResolutions;
};

#endif
