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

#include "pickhandler.h"

#include <osg/ShapeDrawable>
#include <osgUtil/IntersectionVisitor>
#include <osgUtil/LineSegmentIntersector>
#include <osgViewer/Viewer>

#include <QtCore/QDebug>

PickHandler::PickHandler() : osgGA::GUIEventHandler()
{
}

PickHandler::~PickHandler()
{
}

bool PickHandler::handle(const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &aa)
{
    /*
     * You must press Ctrl at the same time to distinguish
     * the selecting operation with normal scene navigating
     */

    if ( ea.getEventType() != osgGA::GUIEventAdapter::RELEASE ||
         ea.getButton() != osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON ||
         !(ea.getModKeyMask()&osgGA::GUIEventAdapter::MODKEY_CTRL) ) {
        return false;
    }

    osgViewer::View* viewer = dynamic_cast<osgViewer::View*>(&aa);
    if (viewer) {
        osg::ref_ptr<osgUtil::LineSegmentIntersector> intersector
                = new osgUtil::LineSegmentIntersector(
                    osgUtil::Intersector::WINDOW, ea.getX(), ea.getY() );

        osgUtil::IntersectionVisitor iv( intersector.get() );
        viewer->getCamera()->accept(iv);

        if(intersector->containsIntersections()) {
            process( intersector->getIntersections() );
        }
    }
    return false;
}

void PickHandler::process(std::multiset<osgUtil::LineSegmentIntersector::Intersection> &intersections)
{
    qDebug() << "Got " << intersections.size() << " intersections:";

    std::multiset<osgUtil::LineSegmentIntersector::Intersection>::const_iterator it;
    for (it = intersections.cbegin(); it != intersections.cend(); ++it) {
        const osgUtil::LineSegmentIntersector::Intersection &result = (*it);

        qDebug() << "  - Local intersection point = "
                 << result.localIntersectionPoint.x()
                 << result.localIntersectionPoint.y()
                 << result.localIntersectionPoint.z();

        if ( result.nodePath.size()>0 ) {
            osg::Geode* geode = dynamic_cast<osg::Geode*>(result.nodePath.back() );
            if ( geode ) {
                osg::ShapeDrawable* shape = dynamic_cast<osg::ShapeDrawable*>( result.drawable.get() );
                if ( shape ) {
                    shape->setColor( osg::Vec4(1.0f, 1.0f, 1.0f, 2.0f) - shape->getColor() );
                }
            }
        }
    }
}
