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

#ifndef CORE_ABSTRACT_SCENE_MODEL_H
#define CORE_ABSTRACT_SCENE_MODEL_H

#include <AGE/Database/Point>
#include <AGE/Database/Edge>
#include <AGE/Database/Region>
#include <AGE/Database/World>
#include <AGE/ScriptEngine/Element>

#include <osg/ref_ptr>
#include <osg/Group>

#include <QtCore/QObject>
#include <QtCore/QtContainerFwd> /* Forward Declarations of the Qt's Containers */

//LIBAGE_BEGIN_NAMESPACE
// class Point;
// class Edge;
// class Region;
// class World;
// class Element;
//LIBAGE_END_NAMESPACE

class AbstractSceneModel : public QObject
{
    Q_OBJECT

public:
    explicit AbstractSceneModel(QObject *parent = Q_NULLPTR) : QObject(parent) {}
    virtual ~AbstractSceneModel() Q_DECL_NOEXCEPT {}

    /* Public Getters */
    Q_INVOKABLE virtual osg::ref_ptr<osg::Group> sceneNode() const = 0;

    Q_INVOKABLE virtual int pointCount() const = 0;
    Q_INVOKABLE virtual AGE::PointPtr pointAt(const int index) const = 0;
    Q_INVOKABLE virtual QSet<int> selectedPointIndexes() const = 0;
    Q_INVOKABLE virtual AGE::ElementPtr elementAt(const int index) const = 0;


Q_SIGNALS:
    /* Internal Notifications */
    void pointInserted(const int index, const AGE::PointPtr &point);
    void pointChanged(const int index, const AGE::PointPtr &point);
    void pointRemoved(const int index);
    void selectionPointChanged();
    void selectionElementChanged();

    // void meshChanged();
    // ...


public Q_SLOTS:
    /* Public Setters */
    Q_INVOKABLE virtual void insertPoint(const int index, const AGE::PointPtr &point) {
        Q_UNUSED(index);
        Q_UNUSED(point);
    }

    Q_INVOKABLE virtual void setPoint(const int index, const AGE::PointPtr &point) {
        Q_UNUSED(index);
        Q_UNUSED(point);
    }

    Q_INVOKABLE virtual void removePoint(const int index) {
        Q_UNUSED(index);
    }

    Q_INVOKABLE virtual void setPointSelection(const QSet<int> indexes);
    Q_INVOKABLE virtual void setElementSelection(const QSet<int> indexes);


};

#endif // CORE_ABSTRACT_SCENE_MODEL_H
