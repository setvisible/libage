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

#ifndef WIDGETS_POINT_TABLE_WIDGET_H
#define WIDGETS_POINT_TABLE_WIDGET_H

#include <Widgets/AbstractSceneView>

class QTimer;

LIBAGE_BEGIN_NAMESPACE
class Point;
typedef QSharedPointer<Point> PointPtr;
LIBAGE_END_NAMESPACE

namespace Ui {
class PointTableWidget;
}

class PointTableWidget : public AbstractSceneView
{
    Q_OBJECT
public:
    explicit PointTableWidget(QWidget *parent = 0);
    virtual ~PointTableWidget();

public Q_SLOTS:
    virtual void onPointInserted(const int index, const AGE::PointPtr &point) Q_DECL_OVERRIDE;
    virtual void onPointChanged(const int index, const AGE::PointPtr &point) Q_DECL_OVERRIDE;
    virtual void onPointRemoved(const int index) Q_DECL_OVERRIDE;
    virtual void onSelectionPointChanged() Q_DECL_OVERRIDE;

protected Q_SLOTS:
    void onItemSelectionChanged();
    void updateTable();
    void updateSelection();

private:
    Ui::PointTableWidget *ui;
    QTimer *m_tableTimer;
    QTimer *m_selectionTimer;
    void resizeColumnToContents();
    void updateTableLater(int msec = 100);
    void updateSelectionLater(int msec = 100);
};

#endif // GUI_POINT_TABLE_WIDGET_H
