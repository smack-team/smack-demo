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

#ifndef CLIENT_H
#define CLIENT_H

#include <QtCore/QObject>
#include <QtNetwork/QLocalSocket>

class ServerDBus;

class Client : public QObject
{
    Q_OBJECT

public:

    /*!
      * \brief Constructor
      * \param parent The parent object.
      */
    explicit Client(QObject *parent = 0);

    /*!
      * \brief Destructor
      */
    ~Client();

public slots:

    /*!
      * \brief Start the client running.
      */
    void run();

private slots:

    /*!
      * \brief read a response from the daemon on the socket.
      */
    void readSocket();

private:
    //! A local socket with which to connect to the daemon
    QLocalSocket *clientSock;
    //! A dbus connection to the daemon
    ServerDBus *dbusClient;
};

#endif // CLIENT_H
