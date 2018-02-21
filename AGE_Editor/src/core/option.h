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

#ifndef CORE_OPTION_H
#define CORE_OPTION_H

#include "optionengine.h"

#include <QtCore/QSet>

QT_BEGIN_NAMESPACE
class QString;
class QUndoStack;
QT_END_NAMESPACE


namespace OptionCommand {
class SetAxesVisible;
class SetGridVisible;
class SetBackgroundVisible;
// --
class SetMasterVisible;
class SetSlaveVisible;
// --
class SetContourVisible;
class SetWireframeVisible;
class SetTextureVisible;
class SetWireframeAndTextureVisible;
}

class Option : public OptionEngine
{
    Q_OBJECT
public:
    explicit Option(QObject *parent = Q_NULLPTR);

    QUndoStack *undoStack() const;

public Q_SLOTS:
    virtual void clear() Q_DECL_OVERRIDE;

    virtual void setAxesVisible(bool visible) Q_DECL_OVERRIDE;
    virtual void setGridVisible(bool visible) Q_DECL_OVERRIDE;
    virtual void setBackgroundVisible(bool visible) Q_DECL_OVERRIDE;
    // --
    virtual void setMasterVisible(bool visible) Q_DECL_OVERRIDE;
    virtual void setSlaveVisible(bool visible) Q_DECL_OVERRIDE;
    // --
    virtual void setContourVisible(bool visible) Q_DECL_OVERRIDE;
    virtual void setWireframeVisible(bool visible) Q_DECL_OVERRIDE;
    virtual void setTextureVisible(bool visible) Q_DECL_OVERRIDE;
    virtual void setWireframeAndTextureVisible(bool visible) Q_DECL_OVERRIDE;

protected:
    /* Friend Classes */
    friend class OptionCommand::SetAxesVisible;
    friend class OptionCommand::SetGridVisible;
    friend class OptionCommand::SetBackgroundVisible;
    // --
    friend class OptionCommand::SetMasterVisible;
    friend class OptionCommand::SetSlaveVisible;
    // --
    friend class OptionCommand::SetContourVisible;
    friend class OptionCommand::SetWireframeVisible;
    friend class OptionCommand::SetTextureVisible;
    friend class OptionCommand::SetWireframeAndTextureVisible;

    /* Callback Methods */
    void _q_setAxesVisible(bool visible);
    void _q_setGridVisible(bool visible);
    void _q_setBackgroundVisible(bool visible);
    // --
    void _q_setMasterVisible(bool visible);
    void _q_setSlaveVisible(bool visible);
    // --
    void _q_setContourVisible(bool visible);
    void _q_setWireframeVisible(bool visible);
    void _q_setTextureVisible(bool visible);
    void _q_setWireframeAndTextureVisible(bool visible);

private:
    QUndoStack* m_undoStack;

};

#endif // CORE_OPTION_H
