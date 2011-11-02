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
#include "smacklabelif.h"

DBusService::DBusService(Engine *parent)
    :   QObject(parent),
      engine(parent)
{
    labelIf = new SmackLabelIf(this);
}

DBusService::~DBusService()
{
}

bool DBusService::setState(int state)
{
    if (state >= SmackDemo::Undefined)
        sendErrorReply(QDBusError::NotSupported, "Unknown state requested");

    //Determine the name of the service that has connected to us
    QString serviceName = message().service();

    // ask dbus to get the smack context of the connected service
    QDBusPendingReply<QString> reply;
    reply = labelIf->getConnectionLabel(serviceName);

    reply.waitForFinished();
    if (!reply.isValid())
    {
        qDebug() << reply.error().message();
        return false;
    }

    // we now know the context of the connected client so we could do further checks
    // and enable or disable features based on that context.
    /*
      #include <sys/smack.h>
      :

      switch (state)
      {
      case SmackDemo::ReStart:
            if (!hasPermissionToSet(reply.value(), restartLabel)
                Set some error condition on the DBusConnection and return it to the client
      break;
      :
      :
      }
      */

    // lets just print it out
    qDebug() << "The Dbus label is :  " << reply.value();


    // If it gets this far the client is allowed to set the state with the
    if (engine->setState(state))
    {
        emit stateChanged(state);
        return true;
    }
    return false;
}
