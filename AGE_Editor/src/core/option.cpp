/* - AGE Editor - Copyright (C) 2018 Sebastien Vavassori
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this program; If not, see <http://www.gnu.org/licenses/>.
 */

#include "option.h"

#include "optioncommand.h"


/*! \class Option
 *  \brief The class Option manages the view options for the scene.
 *
 * For example:
 * \li Axes On/Off
 * \li Grid On/Off
 * \li Wireframe On/Off
 * \li Textures On/Off
 * \li ...
 *
 */

Option::Option(QObject *parent) : OptionEngine(parent)
  , m_undoStack(new QUndoStack(this))
{
    this->clear();
}

QUndoStack* Option::undoStack() const
{
    return m_undoStack;
}

void Option::clear()
{
    OptionEngine::clear();
    m_undoStack->clear();
}

/******************************************************************************
 ******************************************************************************/
void Option::setAxesVisible(bool visible)
{
    m_undoStack->push(new OptionCommand::SetAxesVisible(this, visible));
}

void Option::setGridVisible(bool visible)
{
    m_undoStack->push(new OptionCommand::SetGridVisible(this, visible));
}

void Option::setBackgroundVisible(bool visible)
{
    m_undoStack->push(new OptionCommand::SetBackgroundVisible(this, visible));
}

// -----------------------------------------------------------------------------
void Option::setMasterVisible(bool visible)
{
    m_undoStack->push(new OptionCommand::SetMasterVisible(this, visible));
}

void Option::setSlaveVisible(bool visible)
{
    m_undoStack->push(new OptionCommand::SetSlaveVisible(this, visible));
}

// -----------------------------------------------------------------------------
void Option::setContourVisible(bool visible)
{
    m_undoStack->push(new OptionCommand::SetContourVisible(this, visible));
}

void Option::setWireframeVisible(bool visible)
{
    m_undoStack->push(new OptionCommand::SetWireframeVisible(this, visible));
}

void Option::setTextureVisible(bool visible)
{
    m_undoStack->push(new OptionCommand::SetTextureVisible(this, visible));
}

void Option::setWireframeAndTextureVisible(bool visible)
{
    m_undoStack->push(new OptionCommand::SetWireframeAndTextureVisible(this, visible));
}

/******************************************************************************
 ******************************************************************************/
/* Callback Methods */
void Option::_q_setAxesVisible(bool visible)
{
    OptionEngine::setAxesVisible(visible);
}

void Option::_q_setGridVisible(bool visible)
{
    OptionEngine::setGridVisible(visible);
}

void Option::_q_setBackgroundVisible(bool visible)
{
    OptionEngine::setBackgroundVisible(visible);
}

// -----------------------------------------------------------------------------
void Option::_q_setMasterVisible(bool visible)
{
    OptionEngine::setMasterVisible(visible);
}

void Option::_q_setSlaveVisible(bool visible)
{
    OptionEngine::setSlaveVisible(visible);
}

// -----------------------------------------------------------------------------
void Option::_q_setContourVisible(bool visible)
{
    OptionEngine::setContourVisible(visible);
}

void Option::_q_setWireframeVisible(bool visible)
{
    OptionEngine::setWireframeVisible(visible);
}

void Option::_q_setTextureVisible(bool visible)
{
    OptionEngine::setTextureVisible(visible);
}

void Option::_q_setWireframeAndTextureVisible(bool visible)
{
    OptionEngine::setWireframeAndTextureVisible(visible);
}
