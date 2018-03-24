/* - AGE Core Library - Copyright (C) 2018 Sebastien Vavassori
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

#ifndef AGE_WORLD_PROPERTY_H
#define AGE_WORLD_PROPERTY_H

#include <AGE/Globals>
#include <AGE/World/Element>
#include <AGE/World/Script>

#include <QtCore/QSharedPointer>

#ifdef __cplusplus
extern "C" {
#endif

namespace AGE {

/**
 * Contains all the non-geometrical properties for AGE::Element.
 *
 * For example, if the Element represents a building parcel,
 * its AGE::Property might contain a seed number to generate a
 * random number of floors, and another seed number to generate a
 * random number of windows.
 *
 * The seed numbers are consumed by the AGE::Script.
 *
 * An AGE::Property owns properties for one or several AGE::Element.
 * An AGE::Element owns however only one AGE::Property.
 */
class LIBAGESHARED_EXPORT Property
{
public:
    explicit Property();

};

typedef QSharedPointer<Property> PropertyPtr;

} // namespace AGE

#ifdef __cplusplus
}
#endif

#endif // AGE_WORLD_PROPERTY_H
