// Copyright (c) 2013-2018 LG Electronics, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// SPDX-License-Identifier: Apache-2.0

#ifndef WEBOSKEYFILTER_H
#define WEBOSKEYFILTER_H

#include <WebOSCoreCompositor/weboscompositorexport.h>

#include <QObject>
#include <QKeyEvent>
#include <QJSValue>
#include <QPointer>

class QQmlEngine;

#include <qweboskeyextension.h>

class WebOS : public QObject {
    Q_OBJECT

public:
    WEBOS_KEY_ENUM_DECLARATION;
    Q_ENUMS(KeyWebOS);
};

class WebOSKeyPolicy : public QObject {
    Q_OBJECT

public:
    // This enum values describes an action by a key policy.
    // NotAccepted means the key filter should not accept the key event
    // and it would be propagated to the focus item.
    // Accepted means the key event should be accepted by the key filter.
    // NextPolicy means the policy doesn't decide whether it accepts or not.
    enum Result { \
        NotAccepted  = 0, \
        Accepted     = 1, \
        NextPolicy   = 2, \
    };
    Q_ENUMS(Result);
};

/*!
 * \brief Provides a webOS specific key filter for the qml compositor
 *
 * Provides the interface between external key filter and the compositor.
 */
class WEBOS_COMPOSITOR_EXPORT WebOSKeyFilter : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString keyFilterPreProcess READ preProcess WRITE setPreProcess);
    Q_PROPERTY(QString keyFilterFallback READ fallback WRITE setFallback);

public:
    WebOSKeyFilter(QObject *parent = 0);
    ~WebOSKeyFilter();

    QString preProcess() const { return m_preProcess; }
    void setPreProcess(QString func) { m_preProcess = func; }

    QString fallback() const { return m_fallback; }
    void setFallback(QString func) { m_fallback = func; }

    void keyFocusChanged();

    Q_INVOKABLE bool handleKeyEvent(int keycode, bool pressed, bool autoRepeat);

    Q_INVOKABLE void loadKeyFilters(QJSValue keyFilters, QObject *properties);

protected:
    bool eventFilter(QObject *obj, QEvent *event);

private:
    bool loadFile(QString filepath, QQmlEngine *engine);
    bool setProperties(QObject *properties, QQmlEngine *engine);
    void reset();

    QString m_preProcess;
    QString m_fallback;
    bool m_disallowRelease;
    bool m_wasAutoRepeat;

    QMap<QString, QQmlEngine*> m_engineMap;
    QList<QPair<QString, QQmlEngine*>> m_handlerList;

    QJSValue m_keyFilters;
    QObject *m_properties;
    QPointer<WebOS> m_webos;
    QPointer<WebOSKeyPolicy> m_webosKeyPolicy;
};

#endif // WEBOSKEYFILTER_H
