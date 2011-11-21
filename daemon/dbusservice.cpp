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

#include "dbusservice.h"
#include "engine.h"
#include "smack-demo-common.h"

#include <DBusSmackContext>
#include <SmackQt>

DBusService::DBusService(Engine *parent)
    :   QObject(parent),
      engine(parent)
{
}

DBusService::~DBusService()
{
}

bool DBusService::setState(int state)
{
    if (state >= SmackDemo::Undefined)
        sendErrorReply(QDBusError::NotSupported, "Unknown state requested");

    //Determine the name of the service that has connected to us
    QString clientLabel = SmackQt::DBusSmackContext::getCallerSmackContext(*this);

    if (clientLabel.isEmpty())
        return false;

    qDebug() << "The Dbus label is :  " << clientLabel;

    // we now know the context of the connected client so we could do further checks
    // and enable or disable features based on that context.

    if (state == SmackDemo::ReStart)
    {
        if (!isAllowedReStart(clientLabel))
            return false; //TODO set some error return string to notify the client
    }

    // If it gets this far the client is allowed to set the state with the
    if (engine->setState(state))
    {
        emit stateChanged(state);
        return true;
    }
    return false;
}

bool DBusService::isAllowedReStart(const QString &clientLabel)
{
    QString selfLabel = SmackQt::Smack::getOwnContext();

    return SmackQt::Smack::hasAccess(clientLabel, selfLabel, QLatin1String("W"));
}
