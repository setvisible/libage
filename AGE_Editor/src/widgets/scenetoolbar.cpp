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

#include "scenetoolbar.h"

#include <Core/Option>

#include <QtGui/QIcon>
#include <QtWidgets/QAction>

SceneToolBar::SceneToolBar(const QString &title, QWidget *parent)
    : QToolBar(title, parent)
    , m_option(Q_NULLPTR)
{
    this->createActions();
    this->reset();
}

SceneToolBar::SceneToolBar(QWidget *parent)
    : QToolBar(parent)
    , m_option(Q_NULLPTR)
{
    this->createActions();
    this->reset();
}

SceneToolBar::~SceneToolBar()
{
}

/******************************************************************************
 ******************************************************************************/
void SceneToolBar::connect(Option *option)
{
    if (m_option) {
        QObject::disconnect(m_buttonAxes, SIGNAL(toggled(bool)),
                            m_option, SLOT(setAxesVisible(bool)));
        QObject::disconnect(m_option, SIGNAL(axesVisibilityChanged(bool)),
                            m_buttonAxes, SLOT(setChecked(bool)));

        QObject::disconnect(m_buttonGrid, SIGNAL(toggled(bool)),
                            m_option, SLOT(setGridVisible(bool)));
        QObject::disconnect(m_option, SIGNAL(gridVisibilityChanged(bool)),
                            m_buttonGrid, SLOT(setChecked(bool)));

        QObject::disconnect(m_buttonBackground, SIGNAL(toggled(bool)),
                            m_option, SLOT(setBackgroundVisible(bool)));
        QObject::disconnect(m_option, SIGNAL(backgroundVisibilityChanged(bool)),
                            m_buttonBackground, SLOT(setChecked(bool)));

        QObject::disconnect(m_buttonLabel, SIGNAL(toggled(bool)),
                            m_option, SLOT(setLabelVisible(bool)));
        QObject::disconnect(m_option, SIGNAL(labelVisibilityChanged(bool)),
                            m_buttonLabel, SLOT(setChecked(bool)));
        // --
        QObject::disconnect(m_buttonMaster, SIGNAL(toggled(bool)),
                            m_option, SLOT(setMasterVisible(bool)));
        QObject::disconnect(m_option, SIGNAL(masterVisibilityChanged(bool)),
                            m_buttonMaster, SLOT(setChecked(bool)));

        QObject::disconnect(m_buttonSlave, SIGNAL(toggled(bool)),
                            m_option, SLOT(setSlaveVisible(bool)));
        QObject::disconnect(m_option, SIGNAL(slaveVisibilityChanged(bool)),
                            m_buttonSlave, SLOT(setChecked(bool)));
        // --
        QObject::disconnect(m_buttonContour, SIGNAL(toggled(bool)),
                            m_option, SLOT(setContourVisible(bool)));
        QObject::disconnect(m_option, SIGNAL(contourVisibilityChanged(bool)),
                            m_buttonContour, SLOT(setChecked(bool)));

        QObject::disconnect(m_buttonWireframe, SIGNAL(toggled(bool)),
                            m_option, SLOT(setWireframeVisible(bool)));
        QObject::disconnect(m_option, SIGNAL(wireframeVisibilityChanged(bool)),
                            m_buttonWireframe, SLOT(setChecked(bool)));

        QObject::disconnect(m_buttonTexture, SIGNAL(toggled(bool)),
                            m_option, SLOT(setTextureVisible(bool)));
        QObject::disconnect(m_option, SIGNAL(textureVisibilityChanged(bool)),
                            m_buttonTexture, SLOT(setChecked(bool)));

        QObject::disconnect(m_buttonWireframeAndTexure, SIGNAL(toggled(bool)),
                            m_option, SLOT(setWireframeAndTexureVisible(bool)));
        QObject::disconnect(m_option, SIGNAL(wireframeAndTextureVisibilityChanged(bool)),
                            m_buttonWireframeAndTexure, SLOT(setChecked(bool)));
    }

    m_option = option;

    if (m_option) {
        QObject::connect(m_buttonAxes, SIGNAL(toggled(bool)),
                         m_option, SLOT(setAxesVisible(bool)));
        QObject::connect(m_option, SIGNAL(axesVisibilityChanged(bool)),
                         m_buttonAxes, SLOT(setChecked(bool)));

        QObject::connect(m_buttonGrid, SIGNAL(toggled(bool)),
                         m_option, SLOT(setGridVisible(bool)));
        QObject::connect(m_option, SIGNAL(gridVisibilityChanged(bool)),
                         m_buttonGrid, SLOT(setChecked(bool)));

        QObject::connect(m_buttonBackground, SIGNAL(toggled(bool)),
                         m_option, SLOT(setBackgroundVisible(bool)));
        QObject::connect(m_option, SIGNAL(backgroundVisibilityChanged(bool)),
                         m_buttonBackground, SLOT(setChecked(bool)));

        QObject::connect(m_buttonLabel, SIGNAL(toggled(bool)),
                         m_option, SLOT(setLabelVisible(bool)));
        QObject::connect(m_option, SIGNAL(labelVisibilityChanged(bool)),
                         m_buttonLabel, SLOT(setChecked(bool)));
        // --
        QObject::connect(m_buttonMaster, SIGNAL(toggled(bool)),
                         m_option, SLOT(setMasterVisible(bool)));
        QObject::connect(m_option, SIGNAL(masterVisibilityChanged(bool)),
                         m_buttonMaster, SLOT(setChecked(bool)));

        QObject::connect(m_buttonSlave, SIGNAL(toggled(bool)),
                         m_option, SLOT(setSlaveVisible(bool)));
        QObject::connect(m_option, SIGNAL(slaveVisibilityChanged(bool)),
                         m_buttonSlave, SLOT(setChecked(bool)));
        // --
        QObject::connect(m_buttonContour, SIGNAL(toggled(bool)),
                         m_option, SLOT(setContourVisible(bool)));
        QObject::connect(m_option, SIGNAL(contourVisibilityChanged(bool)),
                         m_buttonContour, SLOT(setChecked(bool)));

        QObject::connect(m_buttonWireframe, SIGNAL(toggled(bool)),
                         m_option, SLOT(setWireframeVisible(bool)));
        QObject::connect(m_option, SIGNAL(wireframeVisibilityChanged(bool)),
                         m_buttonWireframe, SLOT(setChecked(bool)));

        QObject::connect(m_buttonTexture, SIGNAL(toggled(bool)),
                         m_option, SLOT(setTextureVisible(bool)));
        QObject::connect(m_option, SIGNAL(textureVisibilityChanged(bool)),
                         m_buttonTexture, SLOT(setChecked(bool)));

        QObject::connect(m_buttonWireframeAndTexure, SIGNAL(toggled(bool)),
                         m_option, SLOT(setWireframeAndTextureVisible(bool)));
        QObject::connect(m_option, SIGNAL(wireframeAndTextureVisibilityChanged(bool)),
                         m_buttonWireframeAndTexure, SLOT(setChecked(bool)));
    }
}

/******************************************************************************
 ******************************************************************************/
void SceneToolBar::reset()
{
    m_buttonAxes->setChecked(false);
    m_buttonGrid->setChecked(false);
    m_buttonBackground->setChecked(false);
    m_buttonLabel->setChecked(false);
    // --
    m_buttonMaster->setChecked(true);
    m_buttonSlave->setChecked(true);
    // --
    m_buttonContour->setChecked(false);
    m_buttonWireframe->setChecked(false);
    m_buttonTexture->setChecked(true);
    m_buttonWireframeAndTexure->setChecked(false);
}

/******************************************************************************
 ******************************************************************************/
void SceneToolBar::createActions()
{
    {
        m_buttonAxes = new QAction(
                    QIcon(":/icons/menu/view_axes_24x24.png"),
                    tr("Show &Axes"), this);
        m_buttonAxes->setCheckable(true);
        m_buttonAxes->setStatusTip(tr("Show Axes"));
        this->addAction(m_buttonAxes);
    }
    {
        m_buttonGrid = new QAction(
                    QIcon(":/icons/menu/view_grid_24x24.png"),
                    tr("Show &Grid"), this);
        m_buttonGrid->setCheckable(true);
        m_buttonGrid->setStatusTip(tr("Show Grid"));
        this->addAction(m_buttonGrid);
    }
    {
        m_buttonBackground = new QAction(
                    QIcon(":/icons/menu/view_background_24x24.png"),
                    tr("Show &Background"), this);
        m_buttonBackground->setCheckable(true);
        m_buttonBackground->setStatusTip(tr("Show Background"));
        this->addAction(m_buttonBackground);
    }
    {
        m_buttonLabel = new QAction(
                    QIcon(":/icons/menu/view_label_24x24.png"),
                    tr("Show &Label"), this);
        m_buttonLabel->setCheckable(true);
        m_buttonLabel->setStatusTip(tr("Show Label"));
        this->addAction(m_buttonLabel);
    }
    this->addSeparator();
    {
        m_buttonMaster = new QAction(
                    QIcon(":/icons/menu/view_master_24x24.png"),
                    tr("Show &Master"), this);
        m_buttonMaster->setCheckable(true);
        m_buttonMaster->setStatusTip(tr("Show Master"));
        this->addAction(m_buttonMaster);
    }
    {
        m_buttonSlave = new QAction(
                    QIcon(":/icons/menu/view_slave_24x24.png"),
                    tr("Show &Slave"), this);
        m_buttonSlave->setCheckable(true);
        m_buttonSlave->setStatusTip(tr("Show Slave"));
        this->addAction(m_buttonSlave);
    }
    this->addSeparator();
    {
        m_buttonContour = new QAction(
                    QIcon(":/icons/menu/view_contour_24x24.png"),
                    tr("Show &Contour"), this);
        m_buttonContour->setCheckable(true);
        m_buttonContour->setStatusTip(tr("Show Contour"));
        this->addAction(m_buttonContour);
    }
    {
        m_buttonWireframe = new QAction(
                    QIcon(":/icons/menu/view_wireframe_24x24.png"),
                    tr("Show &Wireframe"), this);
        m_buttonWireframe->setCheckable(true);
        m_buttonWireframe->setStatusTip(tr("Show Wireframe"));
        this->addAction(m_buttonWireframe);
    }
    {
        m_buttonTexture = new QAction(
                    QIcon(":/icons/menu/view_texture_24x24.png"),
                    tr("Show &Texture"), this);
        m_buttonTexture->setCheckable(true);
        m_buttonTexture->setStatusTip(tr("Show Texture"));
        this->addAction(m_buttonTexture);
    }
    {
        m_buttonWireframeAndTexure = new QAction(
                    QIcon(":/icons/menu/view_wireframe_and_texture_24x24.png"),
                    tr("Show Wireframe an&d Texture"), this);
        m_buttonWireframeAndTexure->setCheckable(true);
        m_buttonWireframeAndTexure->setStatusTip(tr("Show Wireframe and Texture"));
        this->addAction(m_buttonWireframeAndTexure);
    }
}
