/***************************************************************************
 *   Copyright (C) 1999 by Johan Levin                                     *
 *                                                                         *
 *   Copyright (C) 2011-2014 by Ilya Kotov                                 *
 *   forkotov02@hotmail.ru                                                 *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.         *
 ***************************************************************************/

#include <QSettings>
#include <math.h>
#include <stdlib.h>
#include <qmmp/qmmp.h>
#include "monoplugin.h"

MonoPlugin *MonoPlugin::m_instance = 0;

MonoPlugin::MonoPlugin() : Effect()
{
    m_instance = this;
    m_format = Qmmp::PCM_S16LE;
    m_avg = 0;
    m_ldiff = 0;
    m_rdiff = 0;
    m_tmp = 0;
    m_chan = 0;
    QSettings settings(Qmmp::configFile(), QSettings::IniFormat);
}

MonoPlugin::~MonoPlugin()
{
    m_instance = 0;
}

void MonoPlugin::applyEffect(Buffer *b)
{
    if(m_chan != 2)
        return;

    m_mutex.lock();
    if(m_format == Qmmp::PCM_S16LE)
    {
        short *data = (short *)b->data;
        for (uint i = 0; i < (b->nbytes >> 1); i += 2)
        {
            m_avg = (data[i]>>1) + (data[i + 1]>>1);
            m_avg = qBound(-32768.0, m_avg, 32767.0);
            data[i] = data[i + 1] = m_avg;
        }
    }
    else if(m_format == Qmmp::PCM_S24LE || m_format == Qmmp::PCM_S32LE)
    {
        int *data = (int *)b->data;
        for (uint i = 0; i < (b->nbytes >> 2); i += 2)
        {
            m_avg = (data[i]>>1) + (data[i + 1]>>1);
            data[i] = data[i + 1] = m_avg;
        }
    }
    m_mutex.unlock();
}

void MonoPlugin::configure(quint32 freq, ChannelMap map, Qmmp::AudioFormat format)
{
    m_chan = map.count();
    m_format = format;
    Effect::configure(freq, map, format);
}

MonoPlugin* MonoPlugin::instance()
{
    return m_instance;
}
