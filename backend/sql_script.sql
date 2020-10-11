create database if not exists yiya_db;

use yiya_db;

create table if not exists table_user
(
	id bigint auto_increment,
	username varchar(255) not null,
	phone_number varchar(11) not null,
	email_addr varchar(255) null,
	password varchar(255) not null,
	gender bool,
    age int,
    region varchar(255),
	constraint table_user_pk
		primary key (id)
)
COMMENT '用户表';

create unique index account_phone_number_uindex
	on table_user (phone_number);

create unique index account_username_uindex
	on table_user (username);

create table if not exists table_todo_item
(
    id bigint auto_increment,
    user_id int  not null,
    context text null,
    status int  not null,
    created_date date not null,
    created_time time not null,
    finish_date date not null,
    constraint table_todo_item_pk
		primary key (id)
)
DEFAULT CHARSET=utf8mb4
COMMENT 'TODO Item表';
