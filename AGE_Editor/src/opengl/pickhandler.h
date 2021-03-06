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

#ifndef OPENGL_PICK_HANDLER_H
#define OPENGL_PICK_HANDLER_H

#include <osgGA/GUIEventHandler>
#include <osgUtil/LineSegmentIntersector>

class PickHandler : public osgGA::GUIEventHandler
{
public:
    explicit PickHandler();
    virtual ~PickHandler();

    virtual bool handle(const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &aa);

private:
    void process(std::multiset<osgUtil::LineSegmentIntersector::Intersection> &intersections);

};

#endif // OPENGL_PICK_HANDLER_H
