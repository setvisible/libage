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

#include "compass.h"

#include <osg/Geode>
#include <osg/MatrixTransform>
#include <osg/ShapeDrawable>

static const osg::Vec4 s_red    (1.0f, 0.0f, 0.0f, 1.0f);
static const osg::Vec4 s_green  (0.0f, 1.0f, 0.0f, 1.0f);
static const osg::Vec4 s_blue   (0.0f, 0.0f, 1.0f, 1.0f);
static const osg::Vec4 s_yellow (1.0f, 1.0f, 0.0f, 1.0f);


/*! \class Compass
 * \brief The class Compass is a camera that shows a 3D compass.
 *
 * A 3D compass represents the global coordinate system.
 * It's composed by three arrows. An arrow represents a global axis.
 */

Compass::Compass() : osg::Camera()
{
    m_transform = createGeometry();
    setComputeNearFarMode( osg::CullSettings::DO_NOT_COMPUTE_NEAR_FAR );
}

Compass::Compass( const Compass& copy, osg::CopyOp copyop )
    : osg::Camera(copy, copyop)
    , m_transform(copy.m_transform)
    , m_mainCamera(copy.m_mainCamera)
{
}

Compass::~Compass()
{
}

void Compass::setMainCamera(osg::Camera *camera)
{
    m_mainCamera = camera;
}

void Compass::traverse( osg::NodeVisitor& nv )
{
    if ( m_mainCamera.valid()
         && nv.getVisitorType() == osg::NodeVisitor::CULL_VISITOR ) {
        osg::Matrix matrix = m_mainCamera->getViewMatrix();
        matrix.setTrans( osg::Vec3() );
        if ( m_transform.valid() )
            m_transform->setMatrix( matrix );
    }
    m_transform->accept( nv );
    osg::Camera::traverse( nv );
}

osg::ref_ptr<osg::MatrixTransform> Compass::createGeometry()
{
    osg::ref_ptr<osg::Group> group = new osg::Group;
    group->addChild( createSphere(s_yellow) );
    group->addChild( createAxis(s_red  ,  osg::PI_2, osg::Y_AXIS) );
    group->addChild( createAxis(s_green, -osg::PI_2, osg::X_AXIS) );
    group->addChild( createAxis(s_blue ,       0.0f, osg::Z_AXIS) );

    osg::ref_ptr<osg::MatrixTransform> transform = new osg::MatrixTransform;
    transform->getOrCreateStateSet()->setRenderingHint(osg::StateSet::TRANSPARENT_BIN );
    transform->addChild( group.get() );
    transform->setName("compass");
    return transform.release();
}

osg::ref_ptr<osg::Geode> Compass::createSphere(const osg::Vec4 &color)
{
    const float origin_radius = 0.08f;
    const osg::Vec3 center(0.0f, 0.0f, 0.0f);

    osg::ref_ptr<osg::ShapeDrawable> sphere = new osg::ShapeDrawable;
    sphere->setShape( new osg::Sphere(center, origin_radius) );
    sphere->setColor( color );

    osg::ref_ptr<osg::Geode> sphere_geode = new osg::Geode;
    sphere_geode->addDrawable( sphere.get() );

    return sphere_geode.release();
}

osg::ref_ptr<osg::MatrixTransform> Compass::createAxis(
        const osg::Vec4 &color, const float angle, const osg::Vec3f &axis)
{
    const float radius = 0.04f;
    const float height = 20.0f * radius;
    const osg::Vec3 center(0.0f, 0.0f, height/2.0f);
    const float cone_radius = 2.0f * radius;
    const float cone_height = 2.5f * cone_radius;
    const osg::Vec3 cone_center(0.0f, 0.0f, height);

    osg::ref_ptr<osg::ShapeDrawable> cylinder = new osg::ShapeDrawable;
    cylinder->setShape( new osg::Cylinder(center, radius, height) );
    cylinder->setColor( color );

    osg::ref_ptr<osg::ShapeDrawable> cone = new osg::ShapeDrawable;
    cone->setShape( new osg::Cone(cone_center, cone_radius, cone_height) );
    cone->setColor( color );

    osg::ref_ptr<osg::Geode> arrow_geode = new osg::Geode;
    arrow_geode->addDrawable( cylinder.get() );
    arrow_geode->addDrawable( cone.get() );

    osg::ref_ptr<osg::MatrixTransform> arrow_node = new osg::MatrixTransform;
    arrow_node->setMatrix(osg::Matrix::rotate(angle, axis));
    arrow_node->addChild( arrow_geode.get() );
    return arrow_node.release();
}
