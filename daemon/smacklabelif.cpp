#include "smacklabelif.h"
#include <QList>
#include <QVariant>
#include <QLatin1String>

namespace Constants
{
    //! DBus service
    static const QLatin1String DBusService("org.freedesktop.DBus");
    //! DBus path
    static const QLatin1String DBusPath("/");
    //! The interface the methods belongs to
    const char * const DBusInterface("org.freedesktop.DBus");
    //! The method to call to get the connection label
    static const QLatin1String DBusMethod("GetConnectionSmackContext");
}

SmackLabelIf::SmackLabelIf(QObject *parent)
  : QDBusAbstractInterface(Constants::DBusService, Constants::DBusPath, Constants::DBusInterface,
                           QDBusConnection::sessionBus(), parent)
{
}

SmackLabelIf::~SmackLabelIf()
{

}

QDBusPendingReply<QString> SmackLabelIf::getConnectionLabel(const QString &service)
{
    QList<QVariant> argumentList;
    argumentList << qVariantFromValue(service);
    return asyncCallWithArgumentList(Constants::DBusMethod, argumentList);
}
