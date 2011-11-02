/*
 * This file is part of smack-demo
 *
 * Copyright (C) 2011 Brian McGillion
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * version 2.1 as published by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 * 02110-1301 USA
 *
 * Author: Brian McGillion <brian.mcgillion@intel.com>
 */

#include "serverdbus.h"
#include "clientdbusif.h"

#include <QtCore/QtDebug>
#include <QtDBus/QDBusPendingReply>
#include <QtDBus/QDBusPendingCallWatcher>

ServerDBus::ServerDBus(QObject *parent)
    :   QObject(parent),
      interface(NULL)
{
    interface = new ClientDbusIf(QLatin1String("com.smack.demo"), QLatin1String("/"),
                               QDBusConnection::sessionBus(), this);

    connect(interface, SIGNAL(stateChanged(int)), this, SLOT(stateChanged(int)));
}

ServerDBus::~ServerDBus()
{
}

void ServerDBus::setState(SmackDemo::State state)
{
    if (!interface)
    {
        qCritical() << "Interface not initialized ??";
        return;
    }

    QDBusPendingReply<bool> reply = interface->setState(static_cast<int>(state));
    QDBusPendingCallWatcher *watcher = new QDBusPendingCallWatcher(reply, this);

    connect(watcher, SIGNAL(finished(QDBusPendingCallWatcher*)),
            this, SLOT(replyReceived(QDBusPendingCallWatcher*)), Qt::QueuedConnection);
}

void ServerDBus::replyReceived(QDBusPendingCallWatcher *watcher)
{
    QDBusPendingReply<bool> reply = *watcher;
    if (reply.isError())
    {
        qDebug() << "Error received from the daemon:  " << reply.reply().errorMessage();
    }
    else
    {
        bool response = reply.argumentAt<0>();
        qDebug() << "Received response from daemon: " << response;
    }

    watcher->deleteLater();
}

void ServerDBus::stateChanged(int state)
{
    qDebug() << "Signal received from server for state change: " << state;
}
