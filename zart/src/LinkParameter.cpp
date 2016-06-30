/** -*- mode: c++ ; c-basic-offset: 2 -*-
 * @file   LinkParameter.cpp
 * @author Sebastien Fourey
 * @date   Nov 2014
 *
 * @brief  Declaration of the class LinkParameter
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
#include "LinkParameter.h"
#include "Common.h"
#include <QString>
#include <QUrl>
#include <QLabel>
#include <QGridLayout>
#include <QDesktopServices>

LinkParameter::LinkParameter(QDomNode node, QObject *parent)
  : AbstractParameter(parent),
    _label(0)
{
  _text = node.attributes().namedItem("name").nodeValue();
  _url = node.attributes().namedItem("url").nodeValue();
  QString align = node.toElement().attribute("align",QString("left"));
  if (align == "left") _alignment = Qt::AlignLeft;
  if (align == "center") _alignment = Qt::AlignHCenter;
  if (align == "right") _alignment = Qt::AlignRight;
}

LinkParameter::~LinkParameter()
{
  delete _label;
}

void
LinkParameter::addTo(QWidget * widget, int row)
{
  QGridLayout * grid = dynamic_cast<QGridLayout*>(widget->layout());
  if (! grid) return;
  delete _label;
  _label = new QLabel(QString("<a href=\"%2\">%1</a>").arg(_text).arg(_url),widget);
  _label->setAlignment(_alignment);
  _label->setTextFormat(Qt::RichText);
  _label->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Fixed);
  connect(_label, SIGNAL(linkActivated(QString)),
          this, SLOT(onLinkActivated(QString)));
  grid->addWidget(_label,row,0,1,3);
}

QString
LinkParameter::textValue() const
{
  return QString::null;
}

void
LinkParameter::setValue(const QString &)
{
}

void
LinkParameter::reset()
{
}

void
LinkParameter::saveValueInDOM()
{
}

void
LinkParameter::onLinkActivated(const QString &link)
{
  QDesktopServices::openUrl(QUrl(link));
}
