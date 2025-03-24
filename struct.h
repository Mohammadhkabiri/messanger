#ifndef STRUCTS_H
#define STRUCTS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIGNUP "signup"            /*define signup command */
#define LOGIN "login"              /*define login command*/
#define LOGOUT "logout"            /*define logout command */
#define EXIT "exit"                /*define exit command*/
#define NEW_CHAT "newChat"         /*define newchat command*/
#define SELECT_CHAT "selectChat"   /*define selectchat command*/
#define SEND_MESSAGE "sendMessage" /*define sendmessage command*/
#define SHOW_CHAT "showChat"       /*define showchat command*/
#define INPUT_FILE "inform.txt"    /*define the filename*/
#define LOAD_USER "loadUser"       /*define loaduser command*/
#define MAX_CHARACTER 50
#define MAX_MESSAGE_CONTENT 256
#define MAX_FILE_CHARACTER 256

typedef struct User
{
    char Username[MAX_CHARACTER];
    char Password[MAX_CHARACTER];
    int islogin;
    struct User *next;
} User;

typedef struct Userlist
{
    User *head;
} Userlist;

typedef struct message /*message struct*/
{
    char content[MAX_MESSAGE_CONTENT];
    char author[MAX_CHARACTER];
    struct message *next;
} Message;

typedef struct Chat
{
    char chat_name[MAX_CHARACTER];
    struct User *user1;
    struct User *user2;
    Message *messages_head;
    Message *messages_tail;
    struct Chat *next;
} Chat;

typedef struct Chatlist
{
    Chat *head;
} Chatlist;

typedef struct System
{
    User *logged_in_user;
    Userlist user_list;
    Chat *current_chat;
} System;

#endif
