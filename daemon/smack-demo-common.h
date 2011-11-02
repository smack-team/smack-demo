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

#ifndef SMACKCOMMON_H
#define SMACKCOMMON_H

#include <QtCore/QMetaType>
#include <QtCore/QDataStream>

namespace SmackDemo {

/*!
  * \enum State
  * \brief Enumeration of the valid states that the engine can be in
  */
enum State
{
    Running = 0,             /*!< Running - Start the engine running if it is not already doing so. */
    Stopped,                 /*!< Stopped - Stop a running engine */
    ReStart,                 /*!< ReStart - Restart the engine, and re read any settings */
    Clean,                   /*!< Clean - Erase all saved data in the engine */
    Undefined                /*!< Undefined - The state of the lock is unknown or the lock does not exist */
};

//! The address that hte daemon will use
const char * const serverName = "/tmp/smack-demo.socket";

}

//! Serialization for \a SmackDemo::State
inline QDataStream &operator<<(QDataStream& stream, const SmackDemo::State &state)
{
    stream << static_cast<int>(state);
    return stream;
}

//! Deserialization for \a SmackDemo::State
inline QDataStream &operator>>(QDataStream& stream, SmackDemo::State &state)
{
    int value;
    stream >> value;
    state = static_cast<SmackDemo::State>(value);
    return stream;
}

Q_DECLARE_METATYPE(SmackDemo::State);

#endif // SMACKCOMMON_H
