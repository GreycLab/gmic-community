/** -*- mode: c++ ; c-basic-offset: 2 -*-
 * @file   CommandParamsWidget.cpp
 * @author Sebastien Fourey
 * @date   Nov 2014
 * @brief  Definition of the class CommandParamsWidget
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

#include "Common.h"
#include "CommandParamsWidget.h"
#include "AbstractParameter.h"
#include <QGridLayout>
#include <QLabel>

CommandParamsWidget::CommandParamsWidget(QWidget * parent)
  :QWidget(parent),
    _valueString(""),
    _pbReset(0),
    _labelNoParams(0)
{
  delete layout();
  QGridLayout * grid = new QGridLayout;
  grid->setRowStretch(1,2);
  setLayout(grid);
  _labelNoParams = new QLabel("<i>No parameters</i>",this);
  _labelNoParams->setAlignment(Qt::AlignHCenter|Qt::AlignCenter);
  grid->addWidget(_labelNoParams,0,0,4,3);
}

void
CommandParamsWidget::build(QDomNode presetNode)
{
  clear();
  delete layout();
  QGridLayout * grid = new QGridLayout;
  grid->setRowStretch(1,2);
  setLayout(grid);

  int row = 0;
  QDomNode child = presetNode.firstChild();
  while (! child.isNull()) {
    AbstractParameter * parameter = AbstractParameter::createFromNode(child, this);
    if (parameter) {
      _presetParameters.push_back(parameter);
      if (parameter->isVisible()) {
        parameter->addTo(this,row++);
      }
      connect(parameter,SIGNAL(valueChanged()),
              this,SLOT(updateValueString()));
    }
    child = child.nextSibling();
  }
  if (row) {
    _pbReset = new QPushButton("Reset",this);
    grid->addWidget(_pbReset,row,0,1,3);
    connect(_pbReset,SIGNAL(clicked()),
            this,SLOT(reset()));
    delete _labelNoParams;
    _labelNoParams = 0;
  } else {
    _labelNoParams = new QLabel("<i>No parameters</i>",this);
    _labelNoParams->setAlignment(Qt::AlignHCenter|Qt::AlignCenter);
    grid->addWidget(_labelNoParams,0,0,4,3);
  }
  updateValueString(false);
}

CommandParamsWidget::~CommandParamsWidget()
{
  clear();
}

const QString &
CommandParamsWidget::valueString() const
{
  return _valueString;
}

QStringList
CommandParamsWidget::valueStringList() const
{
  QStringList list;
  for (int i = 0; i < _presetParameters.size(); ++i) {
    list.append(_presetParameters[i]->unquotedTextValue());
  }
  return list;
}

void
CommandParamsWidget::setValues(const QStringList & list)
{
  if (_presetParameters.size() != list.size()) {
    return;
  }
  for (int i = 0; i < _presetParameters.size(); ++i) {
    _presetParameters[i]->setValue(list[i]);
  }
  updateValueString(true);
}

void
CommandParamsWidget::saveValuesInDOM()
{
  for (int i = 0; i < _presetParameters.size(); ++i) {
    _presetParameters[i]->saveValueInDOM();
  }
}

void
CommandParamsWidget::updateValueString(bool notify)
{
  _valueString.clear();
  bool firstParameter = true;
  for (int i = 0; i < _presetParameters.size(); ++i) {
    QString str = _presetParameters[i]->textValue();
    if (!str.isNull()) {
      if (!firstParameter) {
        _valueString += ",";
      }
      _valueString += str;
      firstParameter = false;
    }
  }
  if (notify)
    emit valueChanged();
}

void
CommandParamsWidget::reset()
{
  for (int i = 0; i < _presetParameters.size(); ++i) {
    _presetParameters[i]->reset();
  }
  updateValueString(true);
}

void
CommandParamsWidget::clear()
{
  QVector<AbstractParameter*>::iterator it = _presetParameters.begin();
  while (it != _presetParameters.end()) {
    delete *it;
    ++it;
  }
  _presetParameters.clear();
  delete _pbReset;
  _pbReset = 0;
  delete _labelNoParams;
  _labelNoParams = 0;
}
