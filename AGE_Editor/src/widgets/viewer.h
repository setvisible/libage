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

#ifndef WIDGETS_VIEWER_H
#define WIDGETS_VIEWER_H

#include <Widgets/AbstractSceneView>

class AbstractSceneModel;
class OpenGLViewer;


QT_BEGIN_NAMESPACE
class QWidget;
QT_END_NAMESPACE


class Viewer : public AbstractSceneView
{
    Q_OBJECT
public:
    explicit Viewer(QWidget *parent = Q_NULLPTR);
    virtual ~Viewer();

private Q_SLOTS:
    void update();

private:
    OpenGLViewer *m_openGLViewer;

};

#endif // WIDGETS_VIEWER_H
