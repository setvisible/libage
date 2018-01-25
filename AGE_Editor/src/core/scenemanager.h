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

#ifndef CORE_SCENEMANAGER_H
#define CORE_SCENEMANAGER_H

#include <Core/AbstractSceneModel>

#include <QtCore/QSet>

#include <AGE/Globals>
#include <AGE/Database/World>

#include <osg/ref_ptr>
#include <osg/Group>

LIBAGE_BEGIN_NAMESPACE
//class World;
LIBAGE_END_NAMESPACE

class Scene;
class SceneManager : public AbstractSceneModel
{
    Q_OBJECT
public:
    explicit SceneManager(QObject *parent = Q_NULLPTR);

    void clear();

    /* Plain Old Text Serialization */
    void read(QByteArray &bytes, bool *ok = 0);
    void write(QByteArray &bytes) const;

    /* Public Getters */
    virtual osg::ref_ptr<osg::Group> sceneNode() const Q_DECL_OVERRIDE;
    virtual int pointCount() const Q_DECL_OVERRIDE;
    virtual AGE::PointPtr pointAt(const int index) const Q_DECL_OVERRIDE;
    virtual QSet<int> selectedPointIndexes() const Q_DECL_OVERRIDE;
    virtual AGE::ElementPtr elementAt(const int index) const Q_DECL_OVERRIDE;



Q_SIGNALS:
    void changed();

public Q_SLOTS:
    virtual bool insertPoint(const int index, const AGE::PointPtr &point) Q_DECL_OVERRIDE;
    virtual bool setPoint(const int index, const AGE::PointPtr &point) Q_DECL_OVERRIDE;
    virtual bool removePoint(const int index) Q_DECL_OVERRIDE;
    virtual bool setPointSelection(const QSet<int> indexes) Q_DECL_OVERRIDE;
    virtual bool setElementSelection(const QSet<int> indexes) Q_DECL_OVERRIDE;


private:
    Scene* m_scene;
    QSharedPointer<AGE::World> m_world;

    QSet<int> m_selectedPointIndexes;

    void regenerate();
};

#endif // CORE_SCENEMANAGER_H
