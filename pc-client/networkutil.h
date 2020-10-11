#ifndef NETWORKUTIL_H
#define NETWORKUTIL_H

#include <QNetworkReply>
#include <QNetworkAccessManager>

#include <memory>
#include <assert.h>
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

    void setUserId(const QString &user_id) {
        this->user_id_ = user_id;
    }

    QString getUserId() const {
        return user_id_;
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

    void addTodoItem(const QString &user_id, const QString &context) {
        auto add_todo_item_url = URL + "/add_todo_item";
        QByteArray bytes;
        bytes.append("user_id=" + user_id);
        bytes.append("&context=" + context);
        QDate d;
        auto finish_date = d.currentDate().toString("yyyy-MM-dd");
        bytes.append("&finish_date=" + finish_date);
        QNetworkRequest request {QUrl {add_todo_item_url}};
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
        request.setHeader(QNetworkRequest::ContentLengthHeader, bytes.size());
        manager_->post(request, bytes);
    }

    void queryTodoItems(const QString &user_id) {
        auto query_todo_items_url = URL + "/query_todo_items";
        QByteArray bytes;
        bytes.append("user_id=" + user_id);
        QNetworkRequest request {QUrl {query_todo_items_url}};
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
        request.setHeader(QNetworkRequest::ContentLengthHeader, bytes.size());
        manager_->post(request, bytes);
    }

public slots:
    void Finish(QNetworkReply * reply) {
        QByteArray reply_bytes = reply->readAll();
        // Parse to json.
        QJsonObject json_object = QJsonDocument::fromJson(reply_bytes).object();
        auto it = json_object.find("request_type");
        assert(it != json_object.end());
        assert(it.value().isString());

        if (it.value() == "login") {
            emit loginReplied(json_object);
        } else if (it.value() == "add_todo_item") {
            emit addTodoItemReplied(json_object);
        } else if (it.value() == "query_todo_items") {
            emit queryTodoItemsReplied(json_object);
        }

        reply->deleteLater();
    }

signals:
    void loginReplied(QJsonObject replied_json);

    void addTodoItemReplied(QJsonObject replied_json);

    void queryTodoItemsReplied(QJsonObject replied_json);

private:
    NetworkUtil() {
        manager_.reset(new QNetworkAccessManager());
        connect(manager_.get(), &QNetworkAccessManager::finished, this, &NetworkUtil::Finish);
    }

    NetworkUtil(const NetworkUtil &) = delete ;


private:
    std::unique_ptr<QNetworkAccessManager> manager_;

    QString user_id_ = "";

//    const QString URL = "http://106.12.110.108:12223";
    const QString URL = "http://127.0.0.1:12223";
};

#endif // NETWORKUTIL_H
