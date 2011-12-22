/****************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
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
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QSENSORGESTURE_H
#define QSENSORGESTURE_H

#include <QObject>
#include <QStringList>
#include <qsensorsglobal.h>

#include <QList>
#include <QMap>
#include <QVector>

#include <QtCore/qmetatype.h>

QT_BEGIN_HEADER
QT_BEGIN_NAMESPACE

class QSensorGesturePrivate;

class Q_SENSORS_EXPORT QSensorGesture : public QObject
{
    //Do not use Q_OBJECT here
public:
    QSensorGesture(const QStringList &ids, QObject *parent = 0);
    ~QSensorGesture();

    bool isActive();

    QStringList validIds() const;
    QStringList invalidIds() const;

    QStringList gestureSignals() const;

    void startDetection();
    void stopDetection();

private:
    QSensorGesturePrivate * d_ptr;

private:
    // Pretend to be a Q_OBJECT
    const QMetaObject *metaObject() const;
    int qt_metacall(QMetaObject::Call, int, void **);

#ifdef Q_QDOC
signals:
    // these signals are created at runtime, along with
    // gesture recognizer specific signals.
     void detected(QString);
#endif
};

QT_END_NAMESPACE
QT_END_HEADER


#endif // QSENSORGESTURE_H