/*
 * Temporary QApt compatibility header for Qt6 migration
 * This file provides minimal definitions to allow compilation
 * while the QApt dependency is being replaced with Qt6-compatible alternatives
 */

#ifndef QAPLTEMPORARY_H
#define QAPLTEMPORARY_H

#include <QObject>

// Minimal QApt enums and types for compilation
namespace QApt {
    enum TransactionStatus {
        RunningStatus,
        FinishedStatus
    };

    enum TransactionError {
        Success
    };

    enum UpgradeType {
        FullUpgrade
    };

    class Backend : public QObject
    {
        Q_OBJECT
    public:
        Backend(QObject *parent = nullptr) : QObject(parent) {}
        bool init() { return true; }
        void reloadCache() {}
        QList<class Package*> upgradeablePackages() const { return QList<class Package*>(); }
        class Transaction* updateCache() { return nullptr; }
        class Transaction* upgradeSystem(UpgradeType) { return nullptr; }
    };

    class Package : public QObject
    {
        Q_OBJECT
    public:
        QString name() const { return QString(); }
        QString availableVersion() const { return QString(); }
        qint64 downloadSize() const { return 0; }
    };

    class Transaction : public QObject
    {
        Q_OBJECT
    public:
        Transaction(QObject *parent = nullptr) : QObject(parent) {}
        void setLocale(const QString &) {}
        void run() {}
        void cancel() {}
        TransactionError error() const { return Success; }
        QString errorDetails() const { return QString(); }

    signals:
        void progressChanged(int progress);
        void statusChanged(TransactionStatus status);
        void statusDetailsChanged(const QString &statusDetails);
    };
}

#endif // QAPLTEMPORARY_H
