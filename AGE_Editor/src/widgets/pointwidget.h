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

#ifndef WIDGETS_POINT_WIDGET_H
#define WIDGETS_POINT_WIDGET_H

#include <AGE/Database/Point>
#include <Widgets/AbstractSceneView>

class QString;
class QTimer;

namespace Ui {
class PointWidget;
}

class PointWidget : public AbstractSceneView
{
    Q_OBJECT
public:
    explicit PointWidget(QWidget *parent = 0);
    ~PointWidget();

public Q_SLOTS:
    virtual void onPointChanged(const int index, const AGE::PointPtr &point) Q_DECL_OVERRIDE;
    virtual void onSelectionPointChanged() Q_DECL_OVERRIDE;

private Q_SLOTS:
    void onTextChanged(QString);
    void onValueChanged(double);
    void onChanged();
    void updateInfo();

private:
    Ui::PointWidget *ui;
    int m_currentIndex;
    QTimer *m_timer;
    void updateInfoLater(int msec = 100);

    AGE::PointPtr fromGUI() const;
    void toGUI(const AGE::PointPtr &point);
};

#endif // WIDGETS_POINT_WIDGET_H
