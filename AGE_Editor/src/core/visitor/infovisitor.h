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

#ifndef CORE_INFO_VISITOR_H
#define CORE_INFO_VISITOR_H

#include <osgDB/ReadFile>
#include <osgViewer/Viewer>
#include <iostream>


class InfoVisitor : public osg::NodeVisitor
{
public:
    explicit InfoVisitor() ;

    std::string spaces();

    virtual void apply( osg::Node& node );
    virtual void apply( osg::Geode& geode );

protected:
    unsigned int m_level;
};

#endif // CORE_INFO_VISITOR_H
