/*
 * Copyright (C) 2021 CutefishOS Team.
 *
 * Author:     Kate Leet <kate@cutefishos.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "updatorhelper.h"
#include "upgradeablemodel.h"
#include <QSettings>
#include <QDBusInterface>
#include <QDBusPendingCall>
#include <QTimer>
#include <QDebug>

const static QString s_dbusName = "com.cutefish.Session";
const static QString s_pathName = "/Session";
const static QString s_interfaceName = "com.cutefish.Session";

UpdatorHelper::UpdatorHelper(QObject *parent)
    : QObject(parent)
    , m_checkProgress(0)
    , m_backend(nullptr)  // Temporarily disabled for Qt6 migration
    , m_trans(nullptr)
{
    // m_backend->init();  // Temporarily disabled for Qt6 migration

    QSettings settings("/etc/cutefish", QSettings::IniFormat);
    m_currentVersion = settings.value("Version").toString();

    QTimer::singleShot(100, this, &UpdatorHelper::checkUpdates);
}

UpdatorHelper::~UpdatorHelper()
{
}

void UpdatorHelper::checkUpdates()
{
    if (m_trans)
        return;

    // Temporarily disabled for Qt6 migration - QApt functionality
    // m_trans = m_backend->updateCache();
    // m_trans->setLocale(QLatin1String(setlocale(LC_MESSAGES, 0)));

    // Simulate update check completion
    QTimer::singleShot(2000, this, [=]() {
        m_checkProgress = 100;
        emit checkProgressChanged();
        emit checkUpdateFinished();
    });
}

void UpdatorHelper::upgrade()
{
    if (m_trans) {
        return;
    }

    m_statusDetails.clear();
    // Temporarily disabled for Qt6 migration - QApt functionality
    // m_trans = m_backend->upgradeSystem(QApt::FullUpgrade);
    // m_trans->setLocale(QLatin1String(setlocale(LC_MESSAGES, 0)));

    // Simulate upgrade process
    emit startingUpdate();
    
    QTimer::singleShot(3000, this, [=]() {
        m_statusDetails = "System upgrade completed (simulated for Qt6 migration)\n";
        emit statusDetailsChanged();
        emit updateFinished();
    });
}

void UpdatorHelper::reboot()
{
    QDBusInterface iface(s_dbusName, s_pathName, s_interfaceName, QDBusConnection::sessionBus());

    if (iface.isValid()) {
        iface.call("reboot");
    }
}

QString UpdatorHelper::version()
{
    return m_currentVersion;
}

QString UpdatorHelper::statusDetails()
{
    return m_statusDetails;
}

int UpdatorHelper::checkProgress()
{
    return m_checkProgress;
}
