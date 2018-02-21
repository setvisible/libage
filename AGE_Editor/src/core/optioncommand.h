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

#ifndef CORE_OPTION_COMMAND_H
#define CORE_OPTION_COMMAND_H

#include "option.h"

#include <QtWidgets/QUndoCommand>

namespace OptionCommand {

class SetAxesVisible : public QUndoCommand
{
public:
    SetAxesVisible(Option *opt, bool visible, QUndoCommand *parent = Q_NULLPTR)
        : QUndoCommand(parent), m_opt(opt), m_visible(visible)
    { this->setText(visible
                    ? QObject::tr("Axes On")
                    : QObject::tr("Axes Off")); }
    virtual void undo() { m_opt->_q_setAxesVisible(!m_visible); }
    virtual void redo() { m_opt->_q_setAxesVisible(m_visible); }
private:
    Option *m_opt;
    bool m_visible;
};

class SetGridVisible : public QUndoCommand
{
public:
    SetGridVisible(Option *opt, bool visible, QUndoCommand *parent = Q_NULLPTR)
        : QUndoCommand(parent), m_opt(opt), m_visible(visible)
    { this->setText(visible
                    ? QObject::tr("Grid On")
                    : QObject::tr("Grid Off")); }
    virtual void undo() { m_opt->_q_setGridVisible(!m_visible); }
    virtual void redo() { m_opt->_q_setGridVisible(m_visible); }
private:
    Option *m_opt;
    bool m_visible;
};

class SetBackgroundVisible : public QUndoCommand
{
public:
    SetBackgroundVisible(Option *opt, bool visible, QUndoCommand *parent = Q_NULLPTR)
        : QUndoCommand(parent), m_opt(opt), m_visible(visible)
    { this->setText(visible
                    ? QObject::tr("Background On")
                    : QObject::tr("Background Off")); }
    virtual void undo() { m_opt->_q_setBackgroundVisible(!m_visible); }
    virtual void redo() { m_opt->_q_setBackgroundVisible(m_visible); }
private:
    Option *m_opt;
    bool m_visible;
};

/******************************************************************************
 ******************************************************************************/
class SetMasterVisible : public QUndoCommand
{
public:
    SetMasterVisible(Option *opt, bool visible, QUndoCommand *parent = Q_NULLPTR)
        : QUndoCommand(parent), m_opt(opt), m_visible(visible)
    { this->setText(visible
                    ? QObject::tr("Master On")
                    : QObject::tr("Master Off")); }
    virtual void undo() { m_opt->_q_setMasterVisible(!m_visible); }
    virtual void redo() { m_opt->_q_setMasterVisible(m_visible); }
private:
    Option *m_opt;
    bool m_visible;
};

class SetSlaveVisible : public QUndoCommand
{
public:
    SetSlaveVisible(Option *opt, bool visible, QUndoCommand *parent = Q_NULLPTR)
        : QUndoCommand(parent), m_opt(opt), m_visible(visible)
    { this->setText(visible
                    ? QObject::tr("Slave On")
                    : QObject::tr("Slave Off")); }
    virtual void undo() { m_opt->_q_setSlaveVisible(!m_visible); }
    virtual void redo() { m_opt->_q_setSlaveVisible(m_visible); }
private:
    Option *m_opt;
    bool m_visible;
};

/******************************************************************************
 ******************************************************************************/
class SetContourVisible : public QUndoCommand
{
public:
    SetContourVisible(Option *opt, bool visible, QUndoCommand *parent = Q_NULLPTR)
        : QUndoCommand(parent), m_opt(opt), m_visible(visible)
    { this->setText(visible
                    ? QObject::tr("Contour On")
                    : QObject::tr("Contour Off")); }
    virtual void undo() { m_opt->_q_setContourVisible(!m_visible); }
    virtual void redo() { m_opt->_q_setContourVisible(m_visible); }
private:
    Option *m_opt;
    bool m_visible;
};

class SetWireframeVisible : public QUndoCommand
{
public:
    SetWireframeVisible(Option *opt, bool visible, QUndoCommand *parent = Q_NULLPTR)
        : QUndoCommand(parent), m_opt(opt), m_visible(visible)
    { this->setText(visible
                    ? QObject::tr("Wireframe On")
                    : QObject::tr("Wireframe Off")); }
    virtual void undo() { m_opt->_q_setWireframeVisible(!m_visible); }
    virtual void redo() { m_opt->_q_setWireframeVisible(m_visible); }
private:
    Option *m_opt;
    bool m_visible;
};

class SetTextureVisible : public QUndoCommand
{
public:
    SetTextureVisible(Option *opt, bool visible, QUndoCommand *parent = Q_NULLPTR)
        : QUndoCommand(parent), m_opt(opt), m_visible(visible)
    { this->setText(visible
                    ? QObject::tr("Texture On")
                    : QObject::tr("Texture Off")); }
    virtual void undo() { m_opt->_q_setTextureVisible(!m_visible); }
    virtual void redo() { m_opt->_q_setTextureVisible(m_visible); }
private:
    Option *m_opt;
    bool m_visible;
};

class SetWireframeAndTextureVisible : public QUndoCommand
{
public:
    SetWireframeAndTextureVisible(Option *opt, bool visible, QUndoCommand *parent = Q_NULLPTR)
        : QUndoCommand(parent), m_opt(opt), m_visible(visible)
    { this->setText(visible
                    ? QObject::tr("Wireframe And Texture On")
                    : QObject::tr("Wireframe And Texture Off")); }
    virtual void undo() { m_opt->_q_setWireframeAndTextureVisible(!m_visible); }
    virtual void redo() { m_opt->_q_setWireframeAndTextureVisible(m_visible); }
private:
    Option *m_opt;
    bool m_visible;
};

} // namespace OptionCommand

#endif // CORE_OPTION_COMMAND_H
