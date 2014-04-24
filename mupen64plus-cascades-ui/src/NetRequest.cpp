/*
 * Copyright (c) 2011-2012 Research In Motion Limited.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "NetRequest.hpp"

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QDebug>

/*
 * Default constructor
 */
TwitterRequest::TwitterRequest(QObject *parent)
    : QObject(parent)
{
}

/*
 * TwitterRequest::requestTimeline(const QString &screenName)
 *
 * Makes a network call to retrieve the twitter feed for the specified screenname
 */
//! [0]
void TwitterRequest::requestTimeline(const QString &romName)
{
    QNetworkAccessManager* networkAccessManager = new QNetworkAccessManager(this);

    //const QString queryUri = QString::fromLatin1("http://api.twitter.com/1/statuses/user_timeline.json?include_entities=true&include_rts=true&screen_name=%1").arg(screenName);
    //const QString queryUri = QString::fromLatin1("http://api.archive.vg/2.0/Archive.search/json/7TTRM4MNTIKR2NNAGASURHJOZJ3QXQC5/final+fantasy+vii");
    QString queryUri = QString::fromLatin1("http://thegamesdb.net/api/GetGame.php?name=");
    queryUri.append( romName );

    //Try and sanitize string a bit
    int index = queryUri.indexOf("(");

    if(index > 0){
    	queryUri.truncate(index);
    } else {
    	queryUri.truncate(queryUri.lastIndexOf("."));
    }

    queryUri.append( QString::fromLatin1("&platform=Nintendo+64") );

    qDebug() << "BOXART URL: " << queryUri;

    QNetworkRequest request(queryUri);

    QNetworkReply* reply = networkAccessManager->get(request);

    connect(reply, SIGNAL(finished()), this, SLOT(onTimelineReply()));
}
//! [0]

void TwitterRequest::requestVersion()
{
    QNetworkAccessManager* networkAccessManager = new QNetworkAccessManager(this);
    QString queryUri = QString::fromLatin1("https://raw.githubusercontent.com/tredpath/Mupen64Plus-BB10/master/mupen64plus-cascades-ui/VERSION");

    QNetworkRequest request(queryUri);

    QNetworkReply* reply = networkAccessManager->get(request);

    connect(reply, SIGNAL(finished()), this, SLOT(onVersionReply()));
}

/*
 * TwitterRequest::onTimelineReply()
 *
 * Callback handler for QNetworkReply finished() signal
 */
//! [1]
void TwitterRequest::onTimelineReply()
{
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());

    QString response;
    bool success = false;
    if (reply) {
        if (reply->error() == QNetworkReply::NoError) {
            const int available = reply->bytesAvailable();
            if (available > 0) {
                const QByteArray buffer = reply->readAll();
                response = QString::fromUtf8(buffer);
                qDebug() << "RESPONSE: " << response;
                success = true;
            }
        } else {
            response =  tr("Error: %1 status: %2").arg(reply->errorString(), reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toString());
        }

        reply->deleteLater();
    }

    if (response.trimmed().isEmpty()) {
        response = tr("Twitter request failed. Check internet connection");
    }

    emit complete(response, success);
}
//! [1]

void TwitterRequest::onVersionReply()
{
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());

    QString response;
    bool success = false;
    if (reply) {
        if (reply->error() == QNetworkReply::NoError) {
            const int available = reply->bytesAvailable();
            if (available > 0) {
                const QByteArray buffer = reply->readAll();
                response = QString::fromUtf8(buffer);
                qDebug() << "RESPONSE: " << response;
                success = true;
            }
        } else {
            response =  tr("Error: %1 status: %2").arg(reply->errorString(), reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toString());
        }

        reply->deleteLater();
    }

    if (response.trimmed().isEmpty()) {
        response = tr("Twitter request failed. Check internet connection");
        success = false;
    }

    emit complete(response, success);
}
