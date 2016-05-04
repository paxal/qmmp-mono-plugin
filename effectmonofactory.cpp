/***************************************************************************
 *   Copyright (C) 2009-2015 by Ilya Kotov                                 *
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

#include <QTranslator>
#include <QMessageBox>
#include <qmmp/qmmp.h>
#include "effectmonofactory.h"
#include "monoplugin.h"

const EffectProperties EffectMonoFactory::properties() const
{
    EffectProperties properties;
    properties.name = tr("Extra Mono Plugin");
    properties.shortName = "mono";
    properties.hasSettings = false;
    properties.hasAbout = true;
    return properties;
}

Effect *EffectMonoFactory::create()
{
    return new MonoPlugin();
}

void EffectMonoFactory::showSettings(QWidget *parent)
{
}

void EffectMonoFactory::showAbout(QWidget *parent)
{
    QMessageBox::about (parent, tr("About Mono Plugin"),
                        tr("Qmmp Mono Plugin")+"\n"+
                        tr("Written by: Cyril Pascal"));
}

QTranslator *EffectMonoFactory::createTranslator(QObject *parent)
{
    QTranslator *translator = new QTranslator(parent);
    QString locale = Qmmp::systemLanguageID();
    translator->load(QString(":/mono_plugin_") + locale);
    return translator;
}
