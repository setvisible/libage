/* - AGE Editor - Copyright (C) 2017 Sebastien Vavassori
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

#include "abstractsceneview.h"

#include <Core/AbstractSceneModel>

#include <AGE/Database/Point>


/*! \class AbstractSceneView
 *  \brief The class AbstractSceneView is a view of the AbstractSceneModel.
 *
 * \sa AbstractSceneModel
 */

AbstractSceneView::AbstractSceneView(QWidget *parent) : QWidget(parent)
  , m_model(Q_NULLPTR)
{
}

/******************************************************************************
 ******************************************************************************/
AbstractSceneModel *AbstractSceneView::model() const
{
    return m_model;
}

void AbstractSceneView::setModel(AbstractSceneModel *model)
{
    if (model == m_model)
        return;

    if (m_model) {
        QObject::disconnect(m_model, SIGNAL(pointInserted(int,AGE::PointPtr)),
                            this, SLOT(onPointInserted(int,AGE::PointPtr)));
        QObject::disconnect(m_model, SIGNAL(pointChanged(int,AGE::PointPtr)),
                            this, SLOT(onPointChanged(int,AGE::PointPtr)));
        QObject::disconnect(m_model, SIGNAL(pointRemoved(int)),
                            this, SLOT(onPointRemoved(int)));

        QObject::disconnect(m_model, SIGNAL(selectionPointChanged()),
                            this, SLOT(onSelectionPointChanged()));
        QObject::disconnect(m_model, SIGNAL(selectionElementChanged()),
                            this, SLOT(onSelectionElementChanged()));
    }
    m_model = model;
    if (m_model) {

        QObject::connect(m_model, SIGNAL(pointInserted(int,AGE::PointPtr)),
                         this, SLOT(onPointInserted(int,AGE::PointPtr)));
        QObject::connect(m_model, SIGNAL(pointChanged(int,AGE::PointPtr)),
                         this, SLOT(onPointChanged(int,AGE::PointPtr)));
        QObject::connect(m_model, SIGNAL(pointRemoved(int)),
                         this, SLOT(onPointRemoved(int)));

        QObject::connect(m_model, SIGNAL(selectionPointChanged()),
                         this, SLOT(onSelectionPointChanged()));
        QObject::connect(m_model, SIGNAL(selectionElementChanged()),
                            this, SLOT(onSelectionElementChanged()));

    }
}

/******************************************************************************
 ******************************************************************************/
void AbstractSceneView::onPointInserted(const int, const AGE::PointPtr &)
{
}

void AbstractSceneView::onPointChanged(const int, const AGE::PointPtr &)
{
}

void AbstractSceneView::onPointRemoved(const int)
{
}

/******************************************************************************
 ******************************************************************************/
void AbstractSceneView::onSelectionPointChanged()
{
}

void AbstractSceneView::onSelectionElementChanged()
{
}

