// Copyright (c) 2018 LG Electronics, Inc.
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

#ifndef WEBOSCOMPOSITORPLUGINLOADER_H
#define WEBOSCOMPOSITORPLUGINLOADER_H

#include <QPluginLoader>

#include "weboscompositorinterface.h"
#include "weboscompositorwindow.h"
#include "weboscorecompositor.h"

class WEBOS_COMPOSITOR_EXPORT WebOSCompositorPluginLoader: public QObject
{
public:
    WebOSCompositorPluginLoader(QString pluginName);
    ~WebOSCompositorPluginLoader();

    WebOSCoreCompositor *compositor();
    WebOSCompositorWindow *compositorWindow();

private:
    QPluginLoader *load(QString pluginName);
    bool unload(QPluginLoader *pluginLoader);

    QString m_pluginName;
    QPluginLoader *m_pluginLoader;
    WebOSCoreCompositor *m_compositor;
    WebOSCompositorWindow *m_compositorWindow;
};
#endif //WEBOSCOMPOSITORPLUGINLOADER_H
