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

#ifndef WIDGETS_OPENGL_VIEWER_H
#define WIDGETS_OPENGL_VIEWER_H

#include <QOpenGLWidget>
#include <QTimer>

#include <osg/ref_ptr>
#include <osgViewer/CompositeViewer>
#include <osgViewer/ViewerEventHandlers>

class QWidget;
class SceneManager;

namespace osgQt{
class GraphicsWindowQt;
}

class MyStatsHandler : public osgViewer::StatsHandler
{
public:
    MyStatsHandler()
    {
        /****************************************************************\
        * Adjust font type/size for >=OSG3.                              *
        * OSG defaults aren't working/available for this programme.      *
        \****************************************************************/
        _font = "Fonts/helvetica_medium.txf";
        _characterSize = 16.0f; /* or 12.0f */
    }
};


class OpenGLViewer : public QOpenGLWidget
{
    Q_OBJECT
public:
    explicit OpenGLViewer(QWidget *parent = 0, Qt::WindowFlags f = 0);

Q_SIGNALS:

protected:
    /* Event handlers */
    bool event(QEvent* event) Q_DECL_OVERRIDE;
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void mouseDoubleClickEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
#ifndef QT_NO_WHEELEVENT
    virtual void wheelEvent(QWheelEvent *event);
#endif
    virtual void paintEvent(QPaintEvent* paintEvent);
    virtual void paintGL();

private:
    osg::ref_ptr<osgViewer::CompositeViewer> m_viewer;
    QTimer m_timer;

    osgGA::EventQueue* getEventQueue() const;
    QWidget* addViewWidget(osgQt::GraphicsWindowQt* gw);
    osgQt::GraphicsWindowQt* createGraphicsWindow(
            int x, int y, int w, int h,
            const std::string& name="", bool windowDecoration=false );

};

#endif // WIDGETS_OPENGL_VIEWER_H
