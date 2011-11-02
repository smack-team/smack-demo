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
 * Author: Brian McGillion <brian.mcgillion@symbio.com>
 */

#ifndef SERVERDBUS_H
#define SERVERDBUS_H

#include "../daemon/smack-demo-common.h"

#include <QtCore/QObject>

QT_FORWARD_DECLARE_CLASS(QDBusPendingCallWatcher);
class ClientDbusIf;

class ServerDBus : public QObject
{
    Q_OBJECT

public:

    /*!
      * \brief Constructor
      * \param parent The parent object
      */
    explicit ServerDBus(QObject *parent = 0);

    /*!
      * \brief Destructor
      */
    ~ServerDBus();

public slots:

    /*!
      * \brief set the state of the daemon.
      * \param state The desired state to use.
      */
    void setState(SmackDemo::State state);

    /*!
      * \brief listen for the signal from the server saying that that the state is changed
      * \param state The value of the state that is changed
      */
    void stateChanged(int state);

private slots:

    /*!
      * \brief The response of our setState request has arrived.
      * \param watcher A call watcher that was created to wait for the response from the Daemon
      */
    void replyReceived(QDBusPendingCallWatcher *watcher);

private:
    //! The DBus interface for the daemon.
    ClientDbusIf *interface;
};

#endif // SERVERDBUS_H
