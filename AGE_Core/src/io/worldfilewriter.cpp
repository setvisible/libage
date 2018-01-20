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

#include "worldfilewriter.h"

#include <AGE/Database/Point>

#include <QtCore/QIODevice>
#include <QtCore/QByteArray>
#include <QtCore/QSharedPointer>
#ifdef QT_DEBUG
#  include <QtCore/QDebug>
#endif

static const char *s_point     = "POINT";
static const char *s_edge      = "EDGE";
static const char *s_region    = "REGION";
static const char s_separator  = ' ';
static const char s_endl       = '\n';
static const char s_comment    = '$';

static QByteArray _t(const QString &text = QString())
{
    QByteArray ret;
    ret += s_comment;
    if (!text.isEmpty()) {
        ret += s_separator;
        ret += text.toLatin1();
    }
    ret += s_endl;
    return ret;
}


/*!
 * \class WorldFileWriter
 * \brief The class WorldFileWriter is a reader/writer for World file.
 *
 * The World file contains the data related to the world, especially
 * the master keypoints.
 *
 * The World file is saved in plain format, to be editable manually by a user.
 *
 * \code
 * bool ok;
 * QFileDevice device("my_world.txt");
 * WorldFileWriter parser;
 * AGE::WorldPtr world = parser.read(device, &ok);
 * if (!ok) {
 *      qDebug() << parser.getErrors();
 * }
 * \endcode
 *
 * \sa CellFileWriter
 */

/*! \brief Constructor.
 */
WorldFileWriter::WorldFileWriter()
{
}


/******************************************************************************
 ******************************************************************************/
/*! \brief Return the detailed errors generated by read() or write()
 */
QStringList WorldFileWriter::getErrors() const
{
    return m_errors;
}

/******************************************************************************
 ******************************************************************************/
/*! \brief Reads the given \a device and returns a pointer to the created world.
 *
 * If the method has encountered an error, \a ok is set to false.
 * Otherwise \a ok is true.
 */
AGE::WorldPtr WorldFileWriter::read(QIODevice &device, bool *ok)
{
    QSharedPointer<AGE::World> world = QSharedPointer<AGE::World>(new AGE::World);
    Q_ASSERT(!world.isNull());

    m_errors.clear();
    (*ok) = true;

    if (!device.open(QIODevice::ReadOnly | QIODevice::Text)) {
        m_errors << QLatin1String("Cannot read the device.");
        (*ok) = false;
        return world;
    }

    int lineNumber = 0;

    /* ************************************************* */
    /* first pass: load the points                       */
    /* ************************************************* */
    while (!device.atEnd()) {
        lineNumber++;
        QByteArray line = device.readLine();
        line = line.simplified();

        if (line.isEmpty() || line.startsWith(s_comment)) {
            continue;
        }

        /* ************************************************* */
        /* POINT                                             */
        /* ************************************************* */
        if (line.toUpper().startsWith(s_point)) {

            const QList<QByteArray> list = line.split(s_separator);
            if (list.count() != 5) {
                m_errors << QString("line %0: wrong format for POINT.").arg(lineNumber);
                (*ok) = false;
            } else {

                QByteArray pid = list.at(1);
                QByteArray lon = list.at(2);
                QByteArray lat = list.at(3);
                QByteArray alt = list.at(4);

                AGE::PointPtr point = AGE::PointPtr(new AGE::Point);

                bool convert_ok = true;
                bool _ok;
                point->m_identifier        = pid.toInt(&_ok, 10); convert_ok &= _ok;
                point->m_longitude = (AGE::GeoCoordinate) lon.toInt(&_ok, 10); convert_ok &= _ok;
                point->m_latitude  = (AGE::GeoCoordinate) lat.toInt(&_ok, 10); convert_ok &= _ok;
                point->m_altitude  = (AGE::GeoCoordinate) alt.toInt(&_ok, 10); convert_ok &= _ok;
                if (!convert_ok) {
                    m_errors << QString("line %0: invalid argument for POINT.").arg(lineNumber);
                    (*ok) = false;
                } else {
                    world->m_points.append( point );
                }
            }
            continue;
        }

        /* ************************************************* */
        /* EDGE                                              */
        /* ************************************************* */
        if (line.toUpper().startsWith(s_edge)) {

            const QList<QByteArray> list = line.split(s_separator);
            if (list.count() != 4) {
                m_errors << QString("line %0: wrong format for EDGE.").arg(lineNumber);
                (*ok) = false;
            } else {

                QByteArray eid = list.at(1);
                QByteArray pi1 = list.at(2);
                QByteArray pi2 = list.at(3);

                AGE::EdgePtr edge = AGE::EdgePtr(new AGE::Edge);

                bool convert_ok = true;
                bool _ok;
                edge->m_identifier = eid.toInt(&_ok, 10); convert_ok &= _ok;
                edge->m_pid1 = pi1.toInt(&_ok, 10); convert_ok &= _ok;
                edge->m_pid2 = pi2.toInt(&_ok, 10); convert_ok &= _ok;
                if (!convert_ok) {
                    m_errors << QString("line %0: invalid argument for EDGE.").arg(lineNumber);
                    (*ok) = false;
                } else {
                    world->m_edges.append( edge );
                }
            }

            continue;

        }

        /* ************************************************* */
        /* REGION                                            */
        /* ************************************************* */


        /* else */
        //tempo
        qDebug() << "error";

    }

    /* ************************************************* */
    /* second pass: load the edges and regions           */
    /* ************************************************* */


    return world;
}

/******************************************************************************
 ******************************************************************************/
/*! \brief Writes the given \a world into the given \a device.
 *
 * If the method has encountered an error, the method returns false.
 * Otherwise, the method returns true.
 */
bool WorldFileWriter::write(QIODevice &device, const AGE::WorldPtr &world)
{
    Q_ASSERT(!world.isNull());
    m_errors.clear();

    if (!device.open(QIODevice::WriteOnly | QIODevice::Text)) {
        m_errors << QLatin1String("Cannot write the device.");
        return false;
    }

    /* ************************************************* */
    /* first pass: write the points                      */
    /* ************************************************* */
    device.write(_t(QLatin1String("Points")));
    foreach (const AGE::PointPtr &point, world->m_points) {
        QByteArray line;
        line.append(s_point);
        line.append(s_separator);
        line.append(QByteArray::number(point->m_identifier));
        line.append(s_separator);
        line.append(QByteArray::number(point->m_longitude));
        line.append(s_separator);
        line.append(QByteArray::number(point->m_latitude));
        line.append(s_separator);
        line.append(QByteArray::number(point->m_altitude));
        line.append(s_endl);
        device.write(line);
    }

    /* ************************************************* */
    /* second pass: load the edges                       */
    /* ************************************************* */
    device.write(_t());
    device.write(_t());
    device.write(_t(QLatin1String("Edges")));
    foreach (const AGE::EdgePtr &edge, world->m_edges) {
        QByteArray line;
        line.append(s_edge);
        line.append(s_separator);
        line.append(QByteArray::number(edge->m_identifier));
        line.append(s_separator);
        line.append(QByteArray::number(edge->m_pid1));
        line.append(s_separator);
        line.append(QByteArray::number(edge->m_pid2));
        line.append(s_endl);
        device.write(line);
    }


    /* ************************************************* */
    /* second pass: load the regions                     */
    /* ************************************************* */
    device.write(_t());
    device.write(_t());
    device.write(_t(QLatin1String("Regions")));


    device.write(_t());
    device.write(_t());
    return true;
}

