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

#include "openglviewer.h"

#include "compass.h"

#include <osgGA/TrackballManipulator>
#include <osgQt/GraphicsWindowQt>
#include <osgViewer/Viewer>

#include <QtGui/QWheelEvent>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QWidget>
#ifdef QT_DEBUG
#  include <QtCore/QDebug>
#endif


/*!
 * \class OpenGLViewer
 * \brief The OpenGLViewer class is a QWidget that embeds an osgViewer::Viewer.
 *
 */

/*! \brief Constructor.
 */
OpenGLViewer::OpenGLViewer(QWidget *parent, Qt::WindowFlags f)
    : QOpenGLWidget(parent, f)
{
    m_viewer = new osgViewer::CompositeViewer;

    /* disable the default setting of viewer.done() by pressing Escape. */
    m_viewer->setKeyEventSetsDone(0);

#if QT_VERSION >= 0x050000
    // Qt5 is currently crashing and reporting
    // "Cannot make QOpenGLContext current in a different thread"
    // when the viewer is run multi-threaded, this is regression from Qt4
    m_viewer->setThreadingModel(osgViewer::Viewer::SingleThreaded);
#else
    m_viewer->setThreadingModel(osgViewer::Viewer::CullDrawThreadPerContext);
#endif

    m_viewer->setRunFrameScheme( osgViewer::Viewer::ON_DEMAND );

    // enabling global multisampling
    // can be 2, 4 or 6, depending on specific graphics devices.
    osg::DisplaySettings::instance()->setNumMultiSamples( 4 );

    QWidget* widget = addViewWidget( createGraphicsWindow(0,0,100,100) );

    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0); /* no border */
    layout->addWidget(widget);
    setLayout( layout );

    {
        osgViewer::View* view = m_viewer->getView(0);
        Q_ASSERT(view);
        view->addEventHandler( new MyStatsHandler );

        osgGA::TrackballManipulator* manipulator = new osgGA::TrackballManipulator;
        manipulator->setAllowThrow( false );
        view->setCameraManipulator( manipulator );
    }

    m_viewer->realize();

    // This ensures that the widget will receive keyboard events. This focus
    // policy is not set by default. The default, Qt::NoFocus, will result in
    // keyboard events that are ignored.
    this->setFocusPolicy( Qt::StrongFocus );
    this->setMinimumSize( 100, 100 );

    // Ensures that the widget receives mouse move events even though no
    // mouse button has been pressed. We require this in order to let the
    // graphics window switch viewports properly.
    this->setMouseTracking( true );

    connect( &m_timer, SIGNAL(timeout()), this, SLOT(update()) );
    m_timer.start( (int)(1000.f/30.f) ); // 33.3 msec = 30 frames/sec

}

OpenGLViewer::~OpenGLViewer()
{
}

/******************************************************************************
 ******************************************************************************/
void OpenGLViewer::setSceneNode(const osg::ref_ptr<osg::Group> sceneNode)
{
    const unsigned int count = m_viewer->getNumViews();
    if (count != 1)
        return;
    osgViewer::View* view = m_viewer->getView(0);
    view->setSceneData(sceneNode);

    /* Add a Compass to the scene */
    osg::Camera* camera = view->getCamera();
    osg::ref_ptr<Compass> compass = new Compass;
    compass->setMainCamera( camera );
    compass->setViewport( 0.0, 0.0, 200.0, 200.0 );
    compass->setProjectionMatrix( osg::Matrixd::ortho(-1.5, 1.5, -1.5, 1.5, -10.0, 10.0) );

    compass->setRenderOrder( osg::Camera::POST_RENDER );
    compass->setClearMask( GL_DEPTH_BUFFER_BIT );
    compass->setAllowEventFocus( false );
    compass->setReferenceFrame( osg::Transform::ABSOLUTE_RF );
    compass->getOrCreateStateSet()->setMode( GL_LIGHTING, osg::StateAttribute::OFF );
    compass->getOrCreateStateSet()->setMode( GL_BLEND, osg::StateAttribute::ON );

    sceneNode->addChild( compass.get() );
}

/******************************************************************************
 ******************************************************************************/
void OpenGLViewer::paintEvent(QPaintEvent* /*paintEvent*/)
{
    this->paintGL();
}

void OpenGLViewer::paintGL()
{
    m_viewer->frame();
}

/******************************************************************************
 ******************************************************************************/

void OpenGLViewer::mouseMoveEvent(QMouseEvent* event)
{
    this->getEventQueue()->mouseMotion(
                static_cast<float>(event->x()),
                static_cast<float>(event->y()));
    this->update();
}

void OpenGLViewer::mousePressEvent(QMouseEvent* event)
{
    // 1 = left mouse button
    // 2 = middle mouse button
    // 3 = right mouse button
    unsigned int button = 0;
    switch( event->button() )
    {
    case Qt::LeftButton:
        button = 1;
        break;

    case Qt::MiddleButton:
        button = 2;
        break;

    case Qt::RightButton:
        button = 3;
        break;

    default:
        break;
    }

    this->getEventQueue()->mouseButtonPress(
                static_cast<float>( event->x() ),
                static_cast<float>( event->y() ),
                button );

    this->update();
}

void OpenGLViewer::mouseDoubleClickEvent(QMouseEvent* /*event*/)
{
}


void OpenGLViewer::mouseReleaseEvent(QMouseEvent* event)
{
    // 1 = left mouse button
    // 2 = middle mouse button
    // 3 = right mouse button
    unsigned int button = 0;
    switch( event->button() )
    {
    case Qt::LeftButton:
        button = 1;
        break;

    case Qt::MiddleButton:
        button = 2;
        break;

    case Qt::RightButton:
        button = 3;
        break;

    default:
        break;
    }

    this->getEventQueue()->mouseButtonRelease(
                static_cast<float>( event->x() ),
                static_cast<float>( event->y() ),
                button );

    this->update();
}

void OpenGLViewer::wheelEvent(QWheelEvent* event)
{
    event->accept();
    int delta = event->delta();

    osgGA::GUIEventAdapter::ScrollingMotion motion
            = (delta > 0) ?
                osgGA::GUIEventAdapter::SCROLL_UP
              : osgGA::GUIEventAdapter::SCROLL_DOWN;

    this->getEventQueue()->mouseScroll( motion );
}

/******************************************************************************
 ******************************************************************************/
bool OpenGLViewer::event(QEvent* event)
{
    bool handled = QWidget::event( event );

    // This ensures that the OSG widget is always going to be repainted after the
    // user performed some interaction. Doing this in the event handler ensures
    // that we don't forget about some event and prevents duplicate code.
    switch( event->type() )
    {
    case QEvent::KeyPress:
    case QEvent::KeyRelease:
    case QEvent::MouseButtonDblClick:
    case QEvent::MouseButtonPress:
    case QEvent::MouseButtonRelease:
    case QEvent::MouseMove:
    case QEvent::Wheel:
        this->update();
        break;

    default:
        break;
    }

    return handled;
}


/******************************************************************************
 ******************************************************************************/
osgGA::EventQueue* OpenGLViewer::getEventQueue() const
{
    osgGA::EventQueue* eventQueue = m_viewer->getView(0)->getEventQueue();
    Q_ASSERT_X(eventQueue, Q_FUNC_INFO, "Unable to obtain valid event queue");
    return eventQueue;
}

QWidget* OpenGLViewer::addViewWidget(osgQt::GraphicsWindowQt* gw)
{
    osgViewer::View* view = new osgViewer::View;
    m_viewer->addView( view );

    osg::Camera* camera = view->getCamera();
    camera->setGraphicsContext( gw );

    const osg::GraphicsContext::Traits* traits = gw->getTraits();

    camera->setClearColor( osg::Vec4(0.2, 0.2, 0.6, 1.0) );
    camera->setViewport( new osg::Viewport(0, 0, traits->width, traits->height) );
    camera->setProjectionMatrixAsPerspective(
                30.0f, static_cast<double>(traits->width) / static_cast<double>(traits->height),
                1.0f, 10000.0f );

    return gw->getGLWidget();
}

osgQt::GraphicsWindowQt* OpenGLViewer::createGraphicsWindow(
        int x, int y, int w, int h,
        const std::string& name, bool windowDecoration )
{
    osg::DisplaySettings* ds = osg::DisplaySettings::instance().get();
    osg::ref_ptr<osg::GraphicsContext::Traits> traits = new osg::GraphicsContext::Traits;
    traits->windowName = name;
    traits->windowDecoration = windowDecoration;
    traits->x = x;
    traits->y = y;
    traits->width = w;
    traits->height = h;
    traits->doubleBuffer = true;
    traits->alpha = ds->getMinimumNumAlphaBits();
    traits->stencil = ds->getMinimumNumStencilBits();
    traits->sampleBuffers = ds->getMultiSamples();
    traits->samples = ds->getNumMultiSamples();

    return new osgQt::GraphicsWindowQt(traits.get());
}

