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

#include <stdio.h>
#include "engine.h"

#include <QtCore/QCoreApplication>
#include <QtCore/QtDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    freopen("/tmp/smack-demo.log", "a+", stdout);
    freopen("/tmp/smack-demo.log", "a+", stderr);
    Engine engine(&a);

    if (!engine.initialize())
        qWarning("Unable to initialize the application.");

    return a.exec();
}
