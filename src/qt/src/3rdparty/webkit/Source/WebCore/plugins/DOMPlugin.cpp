/*
 *  Copyright (C) 2008 Nokia Corporation and/or its subsidiary(-ies)
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include "config.h"
#include "DOMPlugin.h"

#include "PluginData.h"
#include "Frame.h"
#include <wtf/text/AtomicString.h>

namespace WebCore {

DOMPlugin::DOMPlugin(PluginData* pluginData, Frame* frame, unsigned index)
    : m_pluginData(pluginData)
    , m_frame(frame)
    , m_index(index)
{
    if (m_frame)
        m_frame->addDestructionObserver(this);
}

DOMPlugin::~DOMPlugin()
{
    if (m_frame)
        m_frame->removeDestructionObserver(this);
}

String DOMPlugin::name() const
{
#ifdef LOG_MODS_FP
    String log_str = String("DOMPlugin::name") + pluginInfo().name;
    logFPCalls(m_frame, log_str);
#endif
    return pluginInfo().name;
}

String DOMPlugin::filename() const
{
#ifdef LOG_MODS_FP
    String log_str = String("DOMPlugin::filename") + pluginInfo().file;
    logFPCalls(m_frame, log_str);
#endif
    return pluginInfo().file;
}

String DOMPlugin::description() const
{
#ifdef LOG_MODS_FP
    String log_str = String("DOMPlugin::description") + pluginInfo().desc;
    logFPCalls(m_frame, log_str);
#endif
    return pluginInfo().desc;
}

unsigned DOMPlugin::length() const
{
#ifdef LOG_MODS_FP
    String log_str = String("DOMPlugin::length") + String("%d", pluginInfo().mimes.size());
    logFPCalls(m_frame, log_str);
#endif
    return pluginInfo().mimes.size();
}

PassRefPtr<DOMMimeType> DOMPlugin::item(unsigned index)
{
#ifdef LOG_MODS_FP
    String log_str = String("DOMPlugin::item w/ index: ") + String("%d", index);
    logFPCalls(m_frame, log_str);
#endif
    if (index >= pluginInfo().mimes.size())
        return 0;

    const MimeClassInfo& mime = pluginInfo().mimes[index];

    const Vector<MimeClassInfo>& mimes = m_pluginData->mimes();
    for (unsigned i = 0; i < mimes.size(); ++i) {
        if (mimes[i] == mime && m_pluginData->mimePluginIndices()[i] == m_index)
            return DOMMimeType::create(m_pluginData.get(), m_frame, i).get();
    }
    return 0;
}

bool DOMPlugin::canGetItemsForName(const AtomicString& propertyName)
{
    const Vector<MimeClassInfo>& mimes = m_pluginData->mimes();
    for (unsigned i = 0; i < mimes.size(); ++i)
        if (mimes[i].type == propertyName)
            return true;
    return false;
}

PassRefPtr<DOMMimeType> DOMPlugin::namedItem(const AtomicString& propertyName)
{
    const Vector<MimeClassInfo>& mimes = m_pluginData->mimes();
    for (unsigned i = 0; i < mimes.size(); ++i)
        if (mimes[i].type == propertyName)
            return DOMMimeType::create(m_pluginData.get(), m_frame, i).get();
    return 0;
}

} // namespace WebCore
