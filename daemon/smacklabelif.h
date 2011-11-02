#ifndef SMACKLABELIF_H
#define SMACKLABELIF_H

#include <QDBusAbstractInterface>
#include <QDBusPendingReply>
#include <QString>

class SmackLabelIf : public QDBusAbstractInterface
{
    Q_OBJECT

public:
    explicit SmackLabelIf(QObject *parent = 0);

  /*!
    * \brief Destructor
    */
  ~SmackLabelIf();

public Q_SLOTS: // METHODS

  /*!
    * \brief Get DBus connection label
    * \param service Service name to be checked
    * \returns The label of the connection if it exists
    */
  QDBusPendingReply<QString> getConnectionLabel(const QString &service);
};

#endif // SMACKLABELIF_H
