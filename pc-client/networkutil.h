#ifndef NETWORKUTIL_H
#define NETWORKUTIL_H

#include <QNetworkReply>
#include <QNetworkAccessManager>

#include <memory>

#include <QObject>
#include <QTextCodec>
#include <QJsonDocument>
#include <QJsonObject>

enum class RequestType {
    LOGIN,
    ADD_TODO_ITEM
};

class NetworkUtil : public QObject
{
    Q_OBJECT
public:
//    explicit NetworkUtil(QObject *parent = nullptr);

    static NetworkUtil &instance() {
        static NetworkUtil instance;
        return instance;
    }

    void login(const QString &username, const QString &password) {
        auto login_url = URL + "/login";
        QByteArray bytes;
        bytes.append("username=" + username);
        bytes.append("&password=" + password);
        QNetworkRequest request {QUrl {login_url}};
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
        request.setHeader(QNetworkRequest::ContentLengthHeader, bytes.size());
        manager_->post(request, bytes);
    }

public slots:
    void Finish(QNetworkReply * reply) {
        QByteArray reply_bytes = reply->readAll();
        // Parse to json.
         QJsonObject json_object = QJsonDocument::fromJson(reply_bytes).object();
        emit httpReplied(json_object);
        reply->deleteLater();
    }

signals:
    void httpReplied(QJsonObject replied_json);

private:
    NetworkUtil() {
        manager_.reset(new QNetworkAccessManager());
        connect(manager_.get(), &QNetworkAccessManager::finished, this, &NetworkUtil::Finish);
    }

    NetworkUtil(const NetworkUtil &) = delete ;


private:
    std::unique_ptr<QNetworkAccessManager> manager_;

    const QString URL = "http://106.12.110.108:12223";
};

#endif // NETWORKUTIL_H
