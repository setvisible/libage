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

#include <QtTest/QtTest>
#include <QtCore/QDebug>

#include <AGE/IO/WorldFileWriter>

class tst_WorldFileWriter : public QObject
{
    Q_OBJECT
private slots:
    void read_empty();
    void read();

    void write_empty();
    void write();
};

using namespace AGE;


/******************************************************************************
 ******************************************************************************/
void tst_WorldFileWriter::read_empty()
{
    // Given
    bool ok;
    WorldFileWriter parser;
    QBuffer emptyBuffer;

    // When
    AGE::WorldPtr world = parser.read(emptyBuffer, &ok);

    // Then
    QCOMPARE(ok, true);
    QCOMPARE(parser.getErrors().count(), 0);
    QCOMPARE(world->isEmpty(), true);
}


/******************************************************************************
 ******************************************************************************/
void tst_WorldFileWriter::read()
{
    // Given
    bool ok;
    WorldFileWriter parser;
    QByteArray byteArray(
                "POINT 2 40 50 60\n"
                "EDGE 1 1 2\n"
                "POINT 1 10 20 30\n"
                );
    QBuffer buffer(&byteArray);

    // When
    AGE::WorldPtr world = parser.read(buffer, &ok);

    // Then
    QCOMPARE(ok, true);
    QCOMPARE(parser.getErrors().count(), 0);
    QCOMPARE(world->isEmpty(), false);

    QCOMPARE(world->pointCount(), 2);
    QCOMPARE((*world->pointAt(-10).data()), AGE::Point());
    QCOMPARE((*world->pointAt(0).data()), AGE::Point());
    QCOMPARE((*world->pointAt(1).data()), AGE::Point(1, 10, 20, 30));
    QCOMPARE((*world->pointAt(2).data()), AGE::Point(2, 40, 50, 60));
    QCOMPARE((*world->pointAt(3).data()), AGE::Point());
    QCOMPARE((*world->pointAt(99999).data()), AGE::Point());

    QCOMPARE(world->edgeCount(), 1);
    QCOMPARE((*world->edgeAt(-10).data()), AGE::Edge());
    QCOMPARE((*world->edgeAt(1).data()), AGE::Edge(1, 1, 2));
    QCOMPARE((*world->edgeAt(9999).data()), AGE::Edge());

    QCOMPARE(world->regionCount(), 0);
}

/******************************************************************************
 ******************************************************************************/
void tst_WorldFileWriter::write_empty()
{
    // Given
    AGE::WorldPtr world = QSharedPointer<AGE::World>(new AGE::World);
    QString expected(
                "$ Points\n"
                "$\n"
                "$\n"
                "$ Edges\n"
                "$\n"
                "$\n"
                "$ Regions\n"
                "$\n"
                "$\n"
                );
    expected.replace("\n", "\r\n");
    QBuffer actual;

    // When
    WorldFileWriter parser;
    bool ok = parser.write(actual, world);

    // Then
    QCOMPARE(ok, true);
    QCOMPARE(parser.getErrors().count(), 0);
    QCOMPARE(actual.buffer(), expected.toLatin1());
}


/******************************************************************************
 ******************************************************************************/
void tst_WorldFileWriter::write()
{
    // Given
    AGE::WorldPtr world = QSharedPointer<AGE::World>(new AGE::World);
    world.data()->m_points.append(QSharedPointer<AGE::Point>(new AGE::Point(1, 10, 20, 30)));
    world.data()->m_points.append(QSharedPointer<AGE::Point>(new AGE::Point(2, 40, 50, 60)));
    world.data()->m_edges.append(QSharedPointer<AGE::Edge>(new AGE::Edge(1, 1, 2)));

    QString expected(
                "$ Points\n"
                "POINT 1 10 20 30\n"
                "POINT 2 40 50 60\n"
                "$\n"
                "$\n"
                "$ Edges\n"
                "EDGE 1 1 2\n"
                "$\n"
                "$\n"
                "$ Regions\n"
                "$\n"
                "$\n"
                );
    expected.replace("\n", "\r\n");
    QBuffer actual;

    // When
    WorldFileWriter parser;
    bool ok = parser.write(actual, world);

    // Then
    QCOMPARE(ok, true);
    QCOMPARE(parser.getErrors().count(), 0);
    QCOMPARE(actual.buffer(), expected.toLatin1());
}

QTEST_APPLESS_MAIN(tst_WorldFileWriter)

#include "tst_worldfilewriter.moc"

