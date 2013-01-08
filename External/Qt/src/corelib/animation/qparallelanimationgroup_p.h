/****************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the QtCore module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial Usage
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Nokia.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights.  These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
** If you have questions regarding the use of this file, please contact
** Nokia at qt-info@nokia.com.
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QPARALLELANIMATIONGROUP_P_H
#define QPARALLELANIMATIONGROUP_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists for the convenience
// of QIODevice. This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include "qparallelanimationgroup.h"
#include "private/qanimationgroup_p.h"
#include <QtCore/qhash.h>

#ifndef QT_NO_ANIMATION

QT_BEGIN_NAMESPACE

class QParallelAnimationGroupPrivate : public QAnimationGroupPrivate
{
    Q_DECLARE_PUBLIC(QParallelAnimationGroup)
public:
    QParallelAnimationGroupPrivate()
        : lastLoop(0), lastCurrentTime(0)
    {
    }

    QHash<QAbstractAnimation*, int> uncontrolledFinishTime;
    int lastLoop;
    int lastCurrentTime;

    bool shouldAnimationStart(QAbstractAnimation *animation, bool startIfAtEnd) const;
    void applyGroupState(QAbstractAnimation *animation);
    bool isUncontrolledAnimationFinished(QAbstractAnimation *anim) const;
    void connectUncontrolledAnimations();
    void disconnectUncontrolledAnimations();

    void animationRemoved(int index, QAbstractAnimation *);

    // private slot
    void _q_uncontrolledAnimationFinished();
};

QT_END_NAMESPACE

#endif //QT_NO_ANIMATION

#endif //QPARALLELANIMATIONGROUP_P_H
