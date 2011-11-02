#!/bin/bash

while [ $# -ge 1 ]; do
    case $1 in
	--iface)
	    qdbusxml2cpp -c DBusServiceIfAdaptor -a dbusserviceifadaptor.h:dbusserviceifadaptor.cpp ./daemon/com.smack.demo.xml
	    ;;
	--proxy)
	    qdbusxml2cpp -v -c ClientDbusIf -p clientdbusif.h:clientdbusif.cpp ./daemon/com.smack.demo.xml
	    ;;
    esac
    shift
done    

exit
