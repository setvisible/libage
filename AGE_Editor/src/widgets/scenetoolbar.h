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

#ifndef WIDGETS_SCENE_TOOLBAR_H
#define WIDGETS_SCENE_TOOLBAR_H

#include <Widgets/AbstractSceneView>

#include <QtWidgets/QToolBar>

class Option;

class SceneToolBar : public QToolBar
{
    Q_OBJECT
public:
    explicit SceneToolBar(const QString &title, QWidget *parent = Q_NULLPTR);
    explicit SceneToolBar(QWidget *parent = Q_NULLPTR);
    virtual ~SceneToolBar();

    void connect(Option *option);
    void reset();

protected Q_SLOTS:

private Q_SLOTS:

private:
    Option *m_option;

    QAction *m_buttonAxes;
    QAction *m_buttonGrid;
    QAction *m_buttonBackground;
    QAction *m_buttonLabel;
    // --
    QAction *m_buttonMaster;
    QAction *m_buttonSlave;
    // --
    QAction *m_buttonContour;
    QAction *m_buttonWireframe;
    QAction *m_buttonTexture;
    QAction *m_buttonWireframeAndTexure;

    void createActions();
};

#endif // WIDGETS_SCENE_TOOLBAR_H
