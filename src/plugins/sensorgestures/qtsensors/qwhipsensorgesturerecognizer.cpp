/****************************************************************************
**
** Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/
**
** This file is part of the QtSensors module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this
** file. Please review the following information to ensure the GNU Lesser
** General Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights. These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU General
** Public License version 3.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of this
** file. Please review the following information to ensure the GNU General
** Public License version 3.0 requirements will be met:
** http://www.gnu.org/copyleft/gpl.html.
**
** Other Usage
** Alternatively, this file may be used in accordance with the terms and
** conditions contained in a signed written agreement between you and Nokia.
**
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/


#include "qwhipsensorgesturerecognizer.h"
QT_BEGIN_NAMESPACE

QWhipSensorGestureRecognizer::QWhipSensorGestureRecognizer(QObject *parent) :
    QSensorGestureRecognizer(parent), whipIt(0)
{
}

QWhipSensorGestureRecognizer::~QWhipSensorGestureRecognizer()
{
}

void QWhipSensorGestureRecognizer::create()
{
    accel = new QAccelerometer(this);
    accel->connectToBackend();
    timer = new QTimer(this);

    qoutputrangelist outputranges = accel->outputRanges();

    if (outputranges.count() > 0)
        accelRange = (int)(outputranges.at(0).maximum);
    else
        accelRange = 44; //this should never happen

    connect(timer,SIGNAL(timeout()),this,SLOT(timeout()));
    timer->setSingleShot(true);
    timer->setInterval(750);

}

QString QWhipSensorGestureRecognizer::id() const
{
    return QString("QtSensors.whip");
}

bool QWhipSensorGestureRecognizer::start()
{
    connect(accel,SIGNAL(readingChanged()),this,SLOT(accelChanged()));
    active = accel->start();

    return active;
}

bool QWhipSensorGestureRecognizer::stop()
{
    accel->stop();
    active = accel->isActive();
    disconnect(accel,SIGNAL(readingChanged()),this,SLOT(accelChanged()));
    return !active;
}

bool QWhipSensorGestureRecognizer::isActive()
{
    return active;
}

#define WHIP_THRESHOLD_FACTOR 0.85
#define WHIP_DETECTION_FACTOR 0.3

void QWhipSensorGestureRecognizer::accelChanged()
{
    qreal x = accel->reading()->x();

    if (whipIt) {
        qreal difference = lastX - x;

        if ((!wasNegative && difference > accelRange * WHIP_THRESHOLD_FACTOR)
                || (wasNegative && difference < -accelRange * WHIP_THRESHOLD_FACTOR)) {

            Q_EMIT whip();
            Q_EMIT detected("whip");
            whipIt = false;
        }

    } else if (x > (accelRange * WHIP_DETECTION_FACTOR)
               || x < -(accelRange * WHIP_DETECTION_FACTOR)) {
        //start of gesture
        timer->start();
        whipIt = true;
        if (lastX > 0)
            wasNegative = false;
        else
            wasNegative = true;
    }
    lastX = x;
}

void QWhipSensorGestureRecognizer::timeout()
{
    whipIt = false;
}

QT_END_NAMESPACE