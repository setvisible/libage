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

#ifndef AGE_SCRIPT_PARSER_H
#define AGE_SCRIPT_PARSER_H

#include <AGE/Globals>
#include <AGE/Database/ScriptFile>
#include <AGE/World/Script>

#include <QtCore/QSharedPointer>

#ifdef __cplusplus
extern "C" {
#endif

namespace AGE {

/**
 * Parse the AGE::Script to generate the detailed geometry for a given AGE::Element.
 *
 */
class LIBAGESHARED_EXPORT Parser //: public QObject
{
//    Q_OBJECT
public:
    explicit Parser();

private:
    AGE::ScriptFile m_file;
};

typedef QSharedPointer<Parser> ParserPtr;

} // namespace AGE

#ifdef __cplusplus
}
#endif

#endif // AGE_SCRIPT_PARSER_H
