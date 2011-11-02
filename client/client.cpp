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

#include "client.h"
#include "serverdbus.h"

#include "../daemon/smack-demo-common.h"

#include <QtCore/QDataStream>

Client::Client(QObject *parent)
    :   QObject(parent),
      clientSock(NULL),
      dbusClient(NULL)
{
}

Client::~Client()
{
}

void Client::run()
{
    // Connect via Dbus and set the state
    // call all usable states
    dbusClient = new ServerDBus(this);
    dbusClient->setState(SmackDemo::Running);
    dbusClient->setState(SmackDemo::Stopped);
    dbusClient->setState(SmackDemo::ReStart);
    dbusClient->setState(SmackDemo::Clean);

    // perform a write using the Socket connection
    clientSock = new QLocalSocket(this);
    connect(clientSock, SIGNAL(readyRead()), this, SLOT(readSocket()));
    clientSock->connectToServer(SmackDemo::serverName);

    QByteArray data;
    QDataStream stream(&data, QIODevice::WriteOnly);
    stream << (quint8)1; // version
    stream << (qint32)(0);

    clientSock->write(data);
    clientSock->flush();
}

void Client::readSocket()
{
    QDataStream response(clientSock);

    if (clientSock->bytesAvailable() > 0)
    {
        quint8 version;
        response >> version;

        if (version == 1)
        {
            bool success;
            qint32 state;
            response >> state;
            response >> success;
            qDebug() << "Received response from socket for state (" << state << "): " << success;
        }
    }
}
