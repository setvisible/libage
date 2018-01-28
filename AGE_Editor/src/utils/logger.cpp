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

#include "logger.h"

#include <QtCore/QtGlobal>
#include <QtCore/QString>

#ifdef QT_DEBUG
#  include <QtCore/QDebug>
#endif

/*! \class Logger
 *
 * To use it:
 *
 *
 * \code
 * // main.cpp
 * int main( int argc, char** argv )
 * {
 *      osg::setNotifyLevel( osg::INFO );
 *      osg::setNotifyHandler( new LogFileHandler("output.txt") );
 *      ...
 * }
 * \endcode
 *
 *
 * \code
 * // myfile.cpp
 * osg::setNotifyLevel( osg::FATAL );
 * ...
 * osg::notify(osg::WARN) << "Some warn message." << std::endl;
 * \endcode
 *
 */


Logger::Logger() : osg::NotifyHandler()
{
}


void Logger::setNotifyLevel(osg::NotifySeverity /*level*/)
{
    /// \todo implement
}

void Logger::notify(osg::NotifySeverity severity, const char* msg)
{
    QString text(msg);
    text = text.remove('\r');
    text = text.remove('\n');
    switch (severity) {
    case osg::ALWAYS:       qDebug() << "[INFO]" << text; break;
    case osg::FATAL:        qDebug() << "[FATAL]" << text; break;
    case osg::WARN:         qDebug() << "[WARNING]" << text; break;
    case osg::NOTICE:       qDebug() << "[NOTICE]" << text; break;
    case osg::INFO:         qDebug() << "[INFO]" << text; break;
    case osg::DEBUG_INFO:   qDebug() << "[DEBUG]" << text; break;
    case osg::DEBUG_FP:     qDebug() << "[DEBUG]" << text; break;
    default:
        Q_UNREACHABLE();
        break;
    }
}

