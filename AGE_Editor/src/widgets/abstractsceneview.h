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

#ifndef WIDGETS_ABSTRACT_SCENE_VIEW_H
#define WIDGETS_ABSTRACT_SCENE_VIEW_H

#define C_SHORT_DELAY_MSEC 10
#define C_LONG_DELAY_MSEC 100

#include <AGE/Globals>
#include <QtWidgets/QWidget>

LIBAGE_BEGIN_NAMESPACE
class Point;
typedef QSharedPointer<Point> PointPtr;
LIBAGE_END_NAMESPACE

class AbstractSceneModel;

class AbstractSceneView : public QWidget
{
    Q_OBJECT
public:
    explicit AbstractSceneView(QWidget *parent = Q_NULLPTR);
    virtual ~AbstractSceneView() Q_DECL_NOEXCEPT {}

    virtual void setModel(AbstractSceneModel *model);
    AbstractSceneModel *model() const;

public Q_SLOTS:
    virtual void onPointInserted(const int index, const AGE::PointPtr &point);
    virtual void onPointChanged(const int index, const AGE::PointPtr &point);
    virtual void onPointRemoved(const int index);

    virtual void onSelectionPointChanged();
    virtual void onSelectionElementChanged();

private:
    AbstractSceneModel *m_model;
};

#endif // WIDGETS_ABSTRACT_SCENE_VIEW_H
