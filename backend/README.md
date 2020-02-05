# Yiya TODOs API文档

## 1. 介绍
### 1.1 依赖
`Yiya`的后端采用python flask开发，数据库使用mysql, 缓存使用Redis.

## 2. 数据表设计
### 2.1 账号表
account table  
- user_id
- username
- phone_number
- email_addr
- password

### 2.2 用户信息表
user_info table
- user_id
- gender
- age
- region

### 2.3 todo_item表
todo_item table
- todo_item_id
- user_id
- text               # md text
- status             # done or todo
- created_date
- created_time
- finish_date

## 3. 架构设计


## 4. API文档
### 4.1 login
Params:
- username
- password

### 4.2 add_todo_item
Params:
- user_id
- text
- finish_date


### 4.3 update_todo_item
Params:
- todo_item_id
- text
- status
- finish_date

## 4.4 query_todo_items
Params:
- user_id
- finish_dates
- status

## 4.5 export_day_summary
Params:
- suer_id
- date

## 4.6 export_week_summary
Params:
- user_id
- start_date
