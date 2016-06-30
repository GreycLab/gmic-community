/** -*- mode: c++ ; c-basic-offset: 2 -*-
 * @file   ChoiceParameter.cpp
 * @author Sebastien Fourey
 * @date   Nov 2014
 *
 * @brief  Declaration of the class AbstractParameter
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
#include "ChoiceParameter.h"
#include "Common.h"
#include <QWidget>
#include <QGridLayout>
#include <QComboBox>
#include <QLabel>
#include <QDomNamedNodeMap>

ChoiceParameter::ChoiceParameter(QDomNode node, QObject *parent)
  : AbstractParameter(parent),
    _node(node),
    _label(0),
    _comboBox(0)
{
  _name = node.attributes().namedItem("name").nodeValue();

  QString def = node.toElement().attribute("default","0");
  QString value = node.toElement().attribute("savedValue",def);
  _default = def.toInt();
  _value = value.toInt();
}

ChoiceParameter::~ChoiceParameter()
{
  delete _comboBox;
  delete _label;
}

void
ChoiceParameter::addTo(QWidget * widget, int row)
{
  QGridLayout * grid = dynamic_cast<QGridLayout*>(widget->layout());
  if (! grid) return;
  delete _comboBox;
  delete _label;

  _comboBox = new QComboBox(widget);
  QDomNamedNodeMap attributes = _node.attributes();
  bool done = false;
  for (int i = 0; i < 50 && !done; ++i) {
    QDomAttr attr = attributes.namedItem(QString("choice%1").arg(i)).toAttr();
    if (attr.isNull()) {
      done = true;
    } else {
      _comboBox->addItem(attr.nodeValue(),QVariant(i));
    }
  }
  _comboBox->setCurrentIndex(_value);

  grid->addWidget(_label = new QLabel(_name,widget),row,0,1,1);
  grid->addWidget(_comboBox,row,1,1,2);
  connect(_comboBox, SIGNAL(currentIndexChanged(int)),
          this, SLOT(onComboBoxIndexChanged(int)));
}

QString
ChoiceParameter::textValue() const
{
  return QString("%1").arg(_comboBox->currentIndex());
}

void
ChoiceParameter::setValue(const QString & value)
{
  _value = value.toInt();
  if (_comboBox) {
    _comboBox->setCurrentIndex(_value);
  }
}

void
ChoiceParameter::reset()
{
  _comboBox->setCurrentIndex(_default);
  _value = _default;
}

void ChoiceParameter::saveValueInDOM()
{
  _node.toElement().setAttribute("savedValue",_comboBox->currentIndex());
}

void
ChoiceParameter::onComboBoxIndexChanged(int i)
{
  _value = i;
  emit valueChanged();
}

