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

#ifndef ENGINE_H
#define ENGINE_H

#include <QtCore/QObject>
#include <QtNetwork/QLocalServer>

class DBusService;
class ConfigWriter;

class Engine : public QObject
{
    Q_OBJECT

public:

    /*!
      * \brief Default constructor
      * \param parent The parent Object.
      */
    explicit Engine(QObject *parent = 0);

    /*!
      * \brief Destructor
      */
    ~Engine();

    /*!
      * \brief Start the engine running.
      * \returns true on success, false otherwise.
      */
    bool initialize();

    /*!
      * \brief set the internal state of the application.
      * \param state hte state to use
      * \returns true on success, False otherwise.
      */
    bool setState(int state);

private slots:

    /*!
      * \brief Accept incomming socket connections, and work with them.
      */
    void handleConnection();

private: // methods

    /*!
      * \brief Register for a DBus connection and start the service
      * \returns true If the D-Bus could be started correctly, flase otherwise.
      */
    bool startDBus();

private:
    //! The D-Bus interface.
    DBusService *dbusService;
    //! A Unix socket used for IPC
    QLocalServer *sockServer;
};

#endif // ENGINE_H
