/** -*- mode: c++ ; c-basic-offset: 2 -*-
 * @file   TextParameter.cpp
 * @author Sebastien Fourey
 * @date   Nov 2014
 *
 * @brief  Declaration of the class TextParameter
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
#include "TextParameter.h"
#include "Common.h"
#include <QWidget>
#include <QGridLayout>
#include <QLineEdit>
#include <QLabel>

TextParameter::TextParameter(QDomNode node, QObject *parent)
  : AbstractParameter(parent),
    _node(node),
    _label(0),
    _lineEdit(0)
{
  _name = node.attributes().namedItem("name").nodeValue();
  QString def = node.attributes().namedItem("default").nodeValue();
  _default = node.toElement().attribute("default",QString());
  _value = node.toElement().attribute("savedValue",_default);
}

TextParameter::~TextParameter()
{
  delete _lineEdit;
  delete _label;
}

void
TextParameter::addTo(QWidget * widget, int row)
{
  QGridLayout * grid = dynamic_cast<QGridLayout*>(widget->layout());
  if (! grid) return;
  delete _label;
  delete _lineEdit;
  _lineEdit = new QLineEdit(_value,widget);
  grid->addWidget(_label = new QLabel(_name,widget),row,0,1,1);
  grid->addWidget(_lineEdit,row,1,1,2);
  connect(_lineEdit,SIGNAL(editingFinished()),
          this,SIGNAL(valueChanged()));
}

QString
TextParameter::textValue() const
{
  QString text = _lineEdit->text();
  text.replace(QChar('"'),QString("\\\""));
  if (_lineEdit->text().isEmpty())
    return QString("\"\\\"\\\"\"");
  else
    return QString("\"%1\"").arg(text);
}

QString
TextParameter::unquotedTextValue() const
{
  return _lineEdit->text();
}

void
TextParameter::setValue(const QString & value)
{
  _value = value;
  if (_lineEdit) {
    _lineEdit->setText(_value);
  }
}

void
TextParameter::reset()
{
  _lineEdit->setText(_default);
  _value = _default;
}

void
TextParameter::saveValueInDOM()
{
  _node.toElement().setAttribute("savedValue",_lineEdit->text());
}
