/* - AGE Editor - Copyright (C) 2017 Sebastien Vavassori
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

#ifndef CORE_SCENE_COMMAND_H
#define CORE_SCENE_COMMAND_H

#include <Core/SceneManager>

#include <QtCore/QMap>
#include <QtCore/QMapIterator>
#include <QtWidgets/QUndoCommand>

#define C_COMMAND_ID_SET_POINT          10


namespace SceneCommand {

class InsertPoint : public QUndoCommand
{
public:
    InsertPoint(SceneManager *manager, int index, AGE::PointPtr point, QUndoCommand *parent = Q_NULLPTR)
        : QUndoCommand(parent), m_manager(manager), m_index(index), m_point(point)
    { this->setText("Insert Point"); }
    virtual void undo() { m_manager->_q_removePoint(m_index); }
    virtual void redo() { m_manager->_q_insertPoint(m_index, m_point); }
private:
    SceneManager *m_manager;
    int m_index;
    AGE::PointPtr m_point;
};

class SetPoint : public QUndoCommand
{
public:
    SetPoint(SceneManager *manager, int index, AGE::PointPtr point, QUndoCommand *parent = Q_NULLPTR)
        : QUndoCommand(parent), m_manager(manager)
    {
        this->setText("Modify Point");
        m_points.insert(index, point);
        m_previous.insert(index, m_manager->pointAt(index));
    }
    virtual void undo()
    {
        QMapIterator<int, AGE::PointPtr> i(m_previous);
        while (i.hasNext()) {
            i.next();
            m_manager->_q_setPoint(i.key(), i.value());
        }
    }
    virtual void redo()
    {
        QMapIterator<int, AGE::PointPtr> i(m_points);
        while (i.hasNext()) {
            i.next();
            m_manager->_q_setPoint(i.key(), i.value());
        }
    }
    virtual int id() const { return C_COMMAND_ID_SET_POINT; }
    bool mergeWith(const QUndoCommand *other)
    {
        if (other->id() != id())
            return false;
        QMap<int, AGE::PointPtr> previous = static_cast<const SetPoint*>(other)->m_previous;
        QMapIterator<int, AGE::PointPtr> prev(previous);
        while (prev.hasNext()) {
            prev.next();
            if (!m_previous.contains(prev.key())) {
                m_previous.insert(prev.key(), prev.value());
            }
        }
        QMap<int, AGE::PointPtr> points = static_cast<const SetPoint*>(other)->m_points;
        QMapIterator<int, AGE::PointPtr> i(points);
        while (i.hasNext()) {
            i.next();
            m_points.insert(i.key(), i.value());
        }
        return true;
    }
private:
    SceneManager *m_manager;
    QMap<int, AGE::PointPtr> m_previous;
    QMap<int, AGE::PointPtr> m_points;
};

class RemovePoint : public QUndoCommand
{
public:
    RemovePoint(SceneManager *manager, int index, QUndoCommand *parent = Q_NULLPTR)
        : QUndoCommand(parent), m_manager(manager), m_index(index), m_previous(m_manager->pointAt(index))
    { this->setText("Remove Point"); }
    virtual void undo() { m_manager->_q_insertPoint(m_index, m_previous); }
    virtual void redo() { m_manager->_q_removePoint(m_index); }
private:
    SceneManager *m_manager;
    int m_index;
    AGE::PointPtr m_previous;
};
/******************************************************************************
 ******************************************************************************/


} // namespace SceneCommand

#endif // CORE_SCENE_COMMAND_H
