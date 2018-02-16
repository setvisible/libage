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

#include "pointwidget.h"
#include "ui_pointwidget.h"

#include <Core/AbstractSceneModel>

#include <QtCore/QTimer>

PointWidget::PointWidget(QWidget *parent) : AbstractSceneView(parent)
  , ui(new Ui::PointWidget)
  , m_currentIndex(-1)
  , m_timer(new QTimer(this))
{
    ui->setupUi(this);

    QObject::connect(m_timer, SIGNAL(timeout()), this, SLOT(updateInfo()));

    QObject::connect(ui->identifier , SIGNAL(textChanged(QString)), this, SLOT(onTextChanged(QString)));
    QObject::connect(ui->longitude, SIGNAL(valueChanged(double)), this, SLOT(onValueChanged(double)));
    QObject::connect(ui->latitude, SIGNAL(valueChanged(double)), this, SLOT(onValueChanged(double)));
    QObject::connect(ui->altitude, SIGNAL(valueChanged(double)), this, SLOT(onValueChanged(double)));

}

PointWidget::~PointWidget()
{
    delete ui;
}


/******************************************************************************
 ******************************************************************************/
void PointWidget::onTextChanged(QString)
{
    onChanged();
}

void PointWidget::onValueChanged(double)
{
    onChanged();
}

void PointWidget::onChanged()
{
    AGE::PointPtr point = fromGUI();
    model()->setPoint(m_currentIndex, point);
}

/******************************************************************************
 ******************************************************************************/
void PointWidget::onPointChanged(const int, const AGE::PointPtr &)
{
    updateInfoLater(C_SHORT_DELAY_MSEC);
}

void PointWidget::onSelectionPointChanged()
{
    QSet<int> set = model()->selectedPointIndexes();
    if (set.count() == 1) {
        QSetIterator<int> it(set);
        m_currentIndex = it.next();
        AGE::PointPtr point = model()->pointAt(m_currentIndex);
        toGUI(point);
        ui->groupBox->setEnabled(true);
    } else {
        if (ui->groupBox->isEnabled()) {
            ui->groupBox->setEnabled(false);
            m_currentIndex = -1;
            AGE::PointPtr dummypoint = AGE::PointPtr(new AGE::Point);
            toGUI(dummypoint);
        }
    }
}

/******************************************************************************
 ******************************************************************************/
void PointWidget::updateInfoLater(int msec)
{
    m_timer->stop();
    m_timer->start(msec);
}

void PointWidget::updateInfo()
{
    m_timer->stop();

    if (m_currentIndex >= 0 && m_currentIndex < model()->pointCount()) {
        AGE::PointPtr point = model()->pointAt(m_currentIndex);
        toGUI(point);
    }
}

/******************************************************************************
 ******************************************************************************/
AGE::PointPtr PointWidget::fromGUI() const
{
    AGE::PointPtr point = AGE::PointPtr(new AGE::Point);
    bool ok;
    int id = ui->identifier->text().toInt(&ok, 10);
    point->m_identifier = ok ? id : -1;
    point->m_longitude = ui->longitude->value();
    point->m_latitude = ui->latitude->value();
    point->m_altitude = ui->altitude->value();
    return point;
}

void PointWidget::toGUI(const AGE::PointPtr &point)
{
    bool blocked_identifier = ui->identifier->blockSignals(true);
    bool blocked_longitude  = ui->longitude->blockSignals(true);
    bool blocked_latitude   = ui->latitude->blockSignals(true);
    bool blocked_altitude   = ui->altitude->blockSignals(true);

    QString text = (point->m_identifier != -1)
            ? QString(point->m_identifier)
            : tr("<Select a point>");

    ui->identifier->setText( text );
    ui->longitude->setValue( point->m_longitude );
    ui->latitude->setValue( point->m_latitude );
    ui->altitude->setValue( point->m_altitude );

    ui->identifier->blockSignals(blocked_identifier);
    ui->longitude->blockSignals(blocked_longitude);
    ui->latitude->blockSignals(blocked_latitude);
    ui->altitude->blockSignals(blocked_altitude);
}
