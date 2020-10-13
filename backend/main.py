from flask import request, Flask
import pymysql
import json
import datetime


def response_ok(request_type, d):
    assert isinstance(request_type, str)
    assert isinstance(d, dict) or isinstance(d, list)
    return json.dumps({"status": "OK", "request_type": request_type, "data": d})


def response_error(request_type, error_msg, d):
    assert isinstance(request_type, str)
    assert isinstance(d, dict)
    return json.dumps({"status": "Error", "request_type": request_type, "error_msg": error_msg, "data": d})


app = Flask("Yiya-Server")
conn = pymysql.connect(host="127.0.0.1",
                       port=3306,
                       user="root",
                       #password="123456",
                       database="yiya_db",
                       charset="utf8")


@app.route("/login", methods=["POST"])
def login():
    if "username" not in request.form:
        return response_error("login", "user_name is not specified.", {})
    if "password" not in request.form:
        return response_error("login", "password is not specified", {})

    username = request.form["username"]
    password = request.form["password"]
    sql = "SELECT * FROM table_user WHERE username=%s and password=%s;"
    try:
        db_cursor = conn.cursor()
        result = db_cursor.execute(sql, [username, password])
        if result == 1:
            results = db_cursor.fetchall()
            user_id = results[0][0]
            queried_username = results[0][1]
            if queried_username != username:
                return response_error("login", "Unknown error.", {})
            return response_ok("login", {"user_id": str(user_id)})
        elif result == 0:
            return response_error("login", "Username or password is not correct.", {})
        else:
            return response_error("login", "Unknown error.", {})
    except Exception as e:
        return response_error("login", str(e), {})


@app.route("/add_todo_item", methods=["POST"])
def add_todo_item():
    # Check form contains the attrs.
    user_id = request.form["user_id"]
    context = request.form["context"]
    finish_date = request.form["finish_date"]
    if finish_date == "":
        finish_date = str(datetime.datetime.now().strftime("%F"))

    sql = "INSERT INTO table_todo_item(user_id, status, context, finish_date, created_date, created_time)" \
          " VALUES(%s, %s, %s,%s, %s, %s)"

    try:
        db_cursor = conn.cursor()
        result = db_cursor.execute(sql, [user_id, 0, context, finish_date, "2020-09-08", "13:44:54"])
        conn.commit()
        if result != 1:
            return response_error("add_todo_item", "Unknown error", {})
        results = db_cursor.fetchall()
    except Exception as e:
        return response_error("add_todo_item", str(e), {})
    print(sql)
    return response_ok("add_todo_item", {})


@app.route("/delete_todo_item", methods=["POST"])
def delete_todo_item():
    # Check form contains the attrs.
    todo_items_id = request.form["todo_items_id"]

    sql = "delete from table_todo_item where id=%s"
    try:
        db_cursor = conn.cursor()
        result = db_cursor.execute(sql, [todo_items_id])
        conn.commit()
        results = db_cursor.fetchall()
    except Exception as e:
        return response_error("delete_todo_item", str(e), {})
    print(sql)
    return response_ok("delete_todo_item", {})


@app.route("/query_todo_items", methods=["POST"])
def query_todo_items():
    user_id = request.form["user_id"]

    sql = "SELECT * FROM table_todo_item WHERE user_id=%s"
    try:
        db_cursor = conn.cursor(cursor=pymysql.cursors.DictCursor)
        result = db_cursor.execute(sql, [user_id])
        if result == 0:
            return response_ok("query_todo_items", {})

        all_rows = db_cursor.fetchall()
        for row_dict in all_rows:
            todo_items_id_value = row_dict.pop("id")
            row_dict["todo_items_id"] = todo_items_id_value
            created_date_value = row_dict.pop("created_date")
            row_dict["created_date"] = str(created_date_value)
            created_time_value = row_dict.pop("created_time")
            row_dict["created_time"] = str(created_time_value)
            finish_date_value = row_dict.pop("finish_date")
            row_dict["finish_date"] = str(finish_date_value)

        return response_ok("query_todo_items", all_rows)
    except Exception as e:
        return response_error("query_todo_items", str(e), {})


@app.route("/query_todo_items_with_conditions", methods=["POST"])
def query_todo_items_with_conditions():
    user_id = request.form["user_id"]
    finish_date = request.form["finish_date"]
    status = request.form["status"]

    sql = "SELECT * FROM table_todo_item WHERE user_id=%s and finish_date=%s and status=%s"
    try:
        db_cursor = conn.cursor(cursor=pymysql.cursors.DictCursor)
        result = db_cursor.execute(sql, [user_id, finish_date, status])
        if result == 0:
            return response_ok("query_todo_items_with_conditions", {})

        all_rows = db_cursor.fetchall()
        for row_dict in all_rows:
            todo_items_id_value = row_dict.pop("id")
            row_dict["todo_items_id"] = todo_items_id_value
            created_date_value = row_dict.pop("created_date")
            row_dict["created_date"] = str(created_date_value)
            created_time_value = row_dict.pop("created_time")
            row_dict["created_time"] = str(created_time_value)
            finish_date_value = row_dict.pop("finish_date")
            row_dict["finish_date"] = str(finish_date_value)

        return response_ok("query_todo_items_with_conditions", all_rows)
    except Exception as e:
        return response_error("query_todo_items_with_conditions", str(e), {})


if __name__ == '__main__':
    app.run(host="0.0.0.0", port=12223, debug=True)
