import requests
import json
import datetime

print("now_datetime", datetime.datetime.now().strftime("%F"))


def query_todo_items_test(userid):
    url = "http://127.0.0.1:12223/query_todo_items"
    postData = {"user_id": "{}".format(str(userid))}
    url_text_json = json.loads(requests.post(url, data=postData).text)

    print("user_id =", str(userid), " have:")
    for i in url_text_json["data"]:
        print(i)


def add_todo_items_test(userid, context, finish_date=datetime.datetime.now().strftime("%F")):
    url = "http://127.0.0.1:12223/add_todo_item"
    postData = {"user_id": "{}".format(str(userid)),
                "context": "{}".format(str(context)),
                "finish_date": "{}".format(str(finish_date))}
    url_text_json = json.loads(requests.post(url, data=postData).text)
    print(url_text_json)
    query_todo_items_test(userid)


def delete_todo_items_test(todo_item_id):
    url = "http://127.0.0.1:12223/delete_todo_item"
    postData = {"todo_item_id": "{}".format(str(todo_item_id))}
    url_text_json = json.loads(requests.post(url, data=postData).text)
    print(url_text_json)



delete_todo_items_test(todo_item_id="57")
query_todo_items_test(userid="2")
# add_todo_items_test(userid="2",context="test2")
