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

#include "gridnode.h"

#include <osg/ShapeDrawable>

#include <osg/Program>
#include <osg/Texture2D>
#include <osg/ShapeDrawable>
#include <osg/Geode>
#include <osgDB/ReadFile>

#include <osg/MatrixTransform>

GridNode::GridNode() : osg::Geode()
{

    osg::ref_ptr<osg::ShapeDrawable> shapeDrawable = new osg::ShapeDrawable;

    shapeDrawable->setShape(
                new osg::Box(
                    osg::Vec3(1.0f, 0.0f, 0.0f),
                    10.0f, 10.0f, 5.0f) );

    this->addDrawable( shapeDrawable.get() );

}


osg::Node* GridNode::createNode()
{
    osg::ref_ptr<osg::Node> skydome = osgDB::readNodeFile("data/skydome.osgt");

    const float scale = 0.001f;
    osg::ref_ptr<osg::MatrixTransform> scaled = new osg::MatrixTransform;
    scaled->preMult(osg::Matrix::translate(0.0f, 0.0f, 0.0f) *
                    osg::Matrix::scale(scale, scale, scale) *
                    osg::Matrix::translate(0.0f, 0.0f, 0.0f) );
    scaled->addChild( skydome.get() );


    osg::ref_ptr<osg::Group> root = new osg::Group;
    root->addChild( scaled.get() );
    return root.release();
}
