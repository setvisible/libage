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

#ifndef CORE_COMPASS_H
#define CORE_COMPASS_H

#include <osg/Camera>

namespace osg {
class MatrixTransform;
class Node;
}

class Compass : public osg::Camera
{
public:
    Compass();
    Compass(const Compass& copy, osg::CopyOp copyop = osg::CopyOp::SHALLOW_COPY);
    META_Node(osg, Compass);

    void setMainCamera(osg::Camera *camera);
    virtual void traverse(osg::NodeVisitor &nv);

protected:
    virtual ~Compass();

private:
    osg::ref_ptr<osg::MatrixTransform> m_transform;
    osg::observer_ptr<osg::Camera> m_mainCamera;

    osg::ref_ptr<osg::MatrixTransform> createGeometry();
    osg::ref_ptr<osg::Geode> createSphere(const osg::Vec4 &color);
    osg::ref_ptr<osg::MatrixTransform> createAxis(
            const osg::Vec4 &color, const float angle, const osg::Vec3f &axis);
};


#endif // CORE_COMPASS_H
