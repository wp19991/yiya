from flask import request, Flask
import pymysql
import json


def response_ok(d):
    assert isinstance(d, dict) or isinstance(d, list)
    return json.dumps({"status": "OK", "data": d})


def response_error(error_msg, d):
    assert isinstance(d, dict)
    return json.dumps({"status": "Error", "error_msg": error_msg, "data": d})


app = Flask("Yiya-Server")
conn = pymysql.connect(host="127.0.0.1",
                       user="root",
                       password="123456",
                       database="yiya_db",
                       charset="utf8")


@app.route("/login", methods=["POST"])
def login():
    if "username" not in request.form:
        return response_error("user_name is not specified.", {})
    if "password" not in request.form:
        return response_error("password is not specified", {})

    username = request.form["username"]
    password = request.form["password"]
    sql = "SELECT * FROM table_user WHERE username='{}' and password='{}';".format(username, password)
    try:
        db_cursor = conn.cursor()
        result = db_cursor.execute(sql)
        if result == 1:
            results = db_cursor.fetchall()
            queried_username = results[0][1]
            if queried_username != username:
                return response_error("Unknown error.", {})
            return response_ok({})
        elif result == 0:
            return response_error("Username or password is not correct.", {})
        else:
            return response_error("Unknown error.", {})
    except Exception as e:
        return response_error(str(e), {})


@app.route("/add_todo_item", methods=["POST"])
def add_todo_item():
    # Check form contains the attrs.
    user_id = request.form["user_id"]
    context = request.form["context"]
    finish_date = request.form["finish_date"]

    sql = "INSERT INTO table_todo_item(user_id, status, context, finish_date, created_date, created_time)" \
          " VALUES('{}', {}, '{}', '{}', '{}', '{}')".format(user_id, 0, context, finish_date, "2020-09-08", "13:44:54")

    try:
        db_cursor = conn.cursor()
        result = db_cursor.execute(sql)
        conn.commit()
        if result != 1:
            return response_error("Unknown error", {})
        results = db_cursor.fetchall()
    except Exception as e:
        return response_error(str(e), {})
    print(sql)
    return response_ok({})


@app.route("/query_todo_items", methods=["POST"])
def query_todo_items():
    user_id = request.form["user_id"]
    finish_date = request.form["finish_date"]
    status = request.form["status"]

    sql = "SELECT * FROM table_todo_item WHERE user_id='{}' and finish_date='{}' and status={}".format(
        user_id, finish_date, status)
    try:
        db_cursor = conn.cursor(cursor=pymysql.cursors.DictCursor)
        result = db_cursor.execute(sql)
        if result == 0:
            return response_ok({})

        all_rows = db_cursor.fetchall()
        for row_dict in all_rows:
            id_value = row_dict.pop("id")
            row_dict["user_id"] = id_value
            created_date_value = row_dict.pop("created_date")
            row_dict["created_date"] = str(created_date_value)
            created_time_value = row_dict.pop("created_time")
            row_dict["created_time"] = str(created_time_value)
            finish_date_value = row_dict.pop("finish_date")
            row_dict["finish_date"] = str(finish_date_value)

        return response_ok(all_rows)
    except Exception as e:
        return response_error(str(e), {})


if __name__ == '__main__':
    app.run(port=12223)
