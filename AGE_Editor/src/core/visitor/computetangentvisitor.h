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

#ifndef CORE_COMPUTE_TANGENT_VISITOR_H
#define CORE_COMPUTE_TANGENT_VISITOR_H

#include <osg/Geode>
#include <osg/Geometry>
#include <osg/Node>
#include <osg/NodeVisitor>
#include <osgUtil/TangentSpaceGenerator>

#include <QDebug>

class ComputeTangentVisitor : public osg::NodeVisitor
{
public:
    void apply( osg::Node& node ) { traverse(node); }

    void apply( osg::Geode& node )
    {
        for ( unsigned int i=0; i<node.getNumDrawables(); ++i ) {
            osg::Geometry* geom = dynamic_cast<osg::Geometry*>( node.getDrawable(i) );
         if ( geom ) {
             qDebug() << QString::fromStdString( geom->getName() );
             if (geom->getName() == "Bump Mapping test") {
                 generateTangentArray( geom );
             }
         }

        }
        traverse( node );
    }

    void generateTangentArray( osg::Geometry* geom )
    {
        osg::ref_ptr<osgUtil::TangentSpaceGenerator> tsg = new osgUtil::TangentSpaceGenerator;
        tsg->generate( geom );
        geom->setVertexAttribArray( 6, tsg->getTangentArray() );
        geom->setVertexAttribBinding( 6, osg::Geometry::BIND_PER_VERTEX );
        geom->setVertexAttribArray( 7, tsg->getBinormalArray() );
        geom->setVertexAttribBinding( 7, osg::Geometry::BIND_PER_VERTEX );
    }
};


#endif // CORE_COMPUTE_TANGENT_VISITOR_H
