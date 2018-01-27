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

#include "infovisitor.h"

InfoVisitor::InfoVisitor()
    : m_level(0)
{
    setTraversalMode(osg::NodeVisitor::TRAVERSE_ALL_CHILDREN);
}

std::string InfoVisitor::spaces()
{
    return std::string(m_level*2, ' ');
}

void InfoVisitor::apply( osg::Node& node )
{
    std::cout << spaces() << node.libraryName() << "::"
              << node.className() << std::endl;
    m_level++;
    traverse( node );
    m_level--;
}

void InfoVisitor::apply( osg::Geode& geode )
{
    std::cout << spaces() << geode.libraryName() << "::"
              << geode.className() << std::endl;
    m_level++;
    for ( unsigned int i=0; i<geode.getNumDrawables(); ++i )
    {
        osg::Drawable* drawable = geode.getDrawable(i);
        std::cout << spaces() << drawable->libraryName() << "::"
                  << drawable->className() << std::endl;
    }
    traverse( geode );
    m_level--;
}
