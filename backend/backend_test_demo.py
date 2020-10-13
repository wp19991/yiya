import requests
import json
import datetime

print("当前日期：",datetime.datetime.now().strftime("%F"))

def query_todo_items_test(id):
    url = "http://127.0.0.1:12223/query_todo_items"
    postData = {"user_id": "{}".format(str(id))}
    url_text_json = json.loads(requests.post(url, data=postData).text)

    print("user_id =",str(id)," have:")
    for i in url_text_json["data"]:
        print(i)

def add_todo_items_test(userid, context, finish_date="2020-10-12"):
    url = "http://127.0.0.1:12223/add_todo_item"
    postData = {"user_id": "{}".format(str(userid)),
                "context": "{}".format(str(context)),
                "finish_date": "{}".format(str(finish_date))}
    url_text_json = json.loads(requests.post(url, data=postData).text)
    print(url_text_json)
    query_todo_items_test(userid)


def delete_todo_items_test(userid, context, finish_date="2020-10-12"):
    url = "http://127.0.0.1:12223/delete_todo_item"
    postData = {"user_id": "{}".format(str(userid)),
                "context": "{}".format(str(context)),
                "finish_date": "{}".format(str(finish_date))}
    url_text_json = json.loads(requests.post(url, data=postData).text)
    print(url_text_json)
    query_todo_items_test(userid)


# query_todo_items_test("2")
delete_todo_items_test("2","test2")
# add_todo_items_test("2","test2")
