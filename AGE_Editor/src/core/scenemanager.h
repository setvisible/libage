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

#ifndef CORE_SCENE_MANAGER_H
#define CORE_SCENE_MANAGER_H

#include "scenemodelmanager.h"

#include <QtCore/QSet>

QT_BEGIN_NAMESPACE
class QString;
class QUndoStack;
QT_END_NAMESPACE


namespace SceneCommand {
class InsertPoint;
class SetPoint;
class RemovePoint;
// --
}

class SceneManager : public SceneModelManager
{
    Q_OBJECT
public:
    explicit SceneManager(QObject *parent = Q_NULLPTR);

    QUndoStack *undoStack() const;

public Q_SLOTS:
    virtual void clear() Q_DECL_OVERRIDE;

    virtual void insertPoint(const int index, const AGE::PointPtr &point) Q_DECL_OVERRIDE;
    virtual void setPoint(const int index, const AGE::PointPtr &point) Q_DECL_OVERRIDE;
    virtual void removePoint(const int index) Q_DECL_OVERRIDE;


protected:
    /* Friend Classes */
    friend class SceneCommand::InsertPoint;
    friend class SceneCommand::SetPoint;
    friend class SceneCommand::RemovePoint;

    /* Callback Methods */
    void _q_insertPoint(const int index, const AGE::PointPtr &point);
    void _q_setPoint(const int index, const AGE::PointPtr &point);
    void _q_removePoint(const int index);

private:
    QUndoStack* m_undoStack;

};

#endif // CORE_SCENE_MANAGER_H
