// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef DFILEINFO_H
#define DFILEINFO_H

#include <QObject>
#include <QUrl>
#include <QVariant>
#include <QScopedPointer>

#include <DError>

#include "dtkio_global.h"
#include "dtkiotypes.h"

DCORE_USE_NAMESPACE
DIO_BEGIN_NAMESPACE
class DFileFuture;
class DFileInfoPrivate;
class DFileInfo : public QObject
{
public:
    explicit DFileInfo(const QUrl &url, QObject *parent = nullptr);
    ~DFileInfo();

    QUrl url() const;
    void setQueryAttributes(const QByteArray &attributes);
    void setQueryInfoFlags(const FileQueryInfoFlags flags);
    QByteArray queryAttributes() const;
    FileQueryInfoFlags queryInfoFlag() const;

    bool initQuerier();
    QVariant attribute(AttributeID id, bool *success = nullptr) const;
    QVariant attribute(const QByteArray &key, const AttributeType type) const;
    bool hasAttribute(AttributeID id) const;
    bool hasAttribute(const QByteArray &key) const;
    bool exists() const;
    bool refresh();
    Permissions permissions() const;

    [[nodiscard]] DFileFuture *initQuerierAsync(int ioPriority, QObject *parent = nullptr);
    [[nodiscard]] DFileFuture *attributeAsync(AttributeID id, int ioPriority, QObject *parent = nullptr) const;
    [[nodiscard]] DFileFuture *attributeAsync(const QByteArray &key, const AttributeType type, int ioPriority, QObject *parent = nullptr) const;
    [[nodiscard]] DFileFuture *existsAsync(int ioPriority, QObject *parent = nullptr) const;
    [[nodiscard]] DFileFuture *refreshAsync(int ioPriority, QObject *parent = nullptr);
    [[nodiscard]] DFileFuture *permissionsAsync(int ioPriority, QObject *parent = nullptr);

    DError lastError() const;

private:
    QScopedPointer<DFileInfoPrivate> d;
};
DIO_END_NAMESPACE

#endif   // DFILEINFO_H
