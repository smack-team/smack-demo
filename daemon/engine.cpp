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

#include "engine.h"
#include "dbusservice.h"
#include "dbusserviceifadaptor.h"
#include "smack-demo-common.h"

#include <SmackQt>
#include <QtNetwork/QLocalSocket>

Engine::Engine(QObject *parent)
    :  QObject(parent),
      dbusService(NULL),
      sockServer(NULL)
{
    qRegisterMetaType<SmackDemo::State>("SmackDemo::State");
}

Engine::~Engine()
{
}

bool Engine::initialize()
{
    // start a local socket server
    sockServer = new QLocalServer(this);
    // clean up the old instance if it exists.
    sockServer->removeServer(SmackDemo::serverName);

    if (!sockServer->listen(SmackDemo::serverName))
    {
        qCritical() << "Falied to start the LocalServer: " << sockServer->errorString();
        return false;
    }

    connect(sockServer, SIGNAL(newConnection()), this, SLOT(handleConnection()));

    //initiate our dbus service
    return startDBus();
}

bool Engine::startDBus()
{
    if (dbusService)
        return true;

    dbusService = new DBusService(this);
    new DBusServiceIfAdaptor(dbusService);

    QDBusConnection connection = QDBusConnection::sessionBus();
    if (!connection.registerObject("/", dbusService))
    {
        qCritical() << "Failed to register Object for DBus: " << connection.lastError().message();
        return false;
    }

    if (!connection.registerService("com.smack.demo"))
    {
        qCritical() << "Failed to register for DBus Service: " << connection.lastError().message();
        return false;
    }

    return true;
}

void Engine::handleConnection()
{
    QLocalSocket *sockClient = sockServer->nextPendingConnection();
    connect(sockClient, SIGNAL(disconnected()), sockClient, SLOT(deleteLater()));

    QString label = SmackQt::Smack::getSocketPeerContext(sockClient->socketDescriptor());

    if (label.isEmpty())
    {
        qDebug() << "Could not read the label of the socket";
        return;
    }

    qDebug() << "The socket label is : " << label;

    //COULD DO - test if that label is allowed to write to us

    bool result = false;
    qint32 state = SmackDemo::Undefined;

    if (sockClient->waitForReadyRead())
    {
        QDataStream stream(sockClient);
        quint8 version;
        stream >> version;

        if (version == 1)
        {
            // read the state from the client and attempt to set it
            stream >> state;
            result = setState(state);
        }
    }
    else
    {
        qDebug() << "There is no data available on the socket ??";
    }

    // Now write the result back to the client
    QByteArray data;
    QDataStream replyStream(&data, QIODevice::WriteOnly);
    replyStream << (quint8)1; // version
    replyStream << (qint32)state;
    replyStream << (bool)(result);

    sockClient->write(data);
    sockClient->flush();
    sockClient->disconnectFromServer();
}

bool Engine::setState(int state)
{
    if (state >= SmackDemo::Undefined)
        return false;

    qDebug() << "setState() = " << state;

    return true;
}
