#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "struct.h"

/*users function*/
User *create_User_node(char *username, char *password);                  /*function to create a user*/
int check_username(User *head, char *username);                          /*function to check if the username already exist*/
void add_user(User **head, User **tail, char *username, char *password); /*function to put the new user and the end of user linklist*/
void signup(User **user_head, User **user_tail);                         /*fucntion to signup the new user*/
void login(User *user_head, User **logged_in_user, int *login_status);   /*function to loggin the person with information of that*/
void load_user(User **head, User **tail);                                /*function to signup the user with the file information*/

/*chats function*/
Chat *create_Chat_node(char *name, User *user1, User *user2);                            /*function to create chat*/
void add_chat(Chat **head, Chat **tail, char *name, User *user1, User *user2);           /*function to add created chat at the end of chat linklist*/
void newchat(Chat **chat_head, Chat **chat_tail, User *logged_in_user, User *user_head); /*function to add newchat with 2 person*/
int selectchat(Chat *chat_head, User *logged_in_user, Chat **current_chat);              /*function to select 1 chat beetween the chats of 1 person*/

/*message functions*/
Message *create_message_node(char *content, char *author);         /*function to create message */
void add_message_to_chat(Chat *chat, char *content, char *author); /*function to add the message to specific chat*/
void sendmessage(Chat *current_chat, User *logged_in_user);        /*function to sendmessage to someone in the specific chat*/
void show_chat(Chat *chat);                                        /*function to show the messages of the specific chat*/
void check_showchat(Chat *current_chat);                           /*function to check if chat is selected show the chat*/
void free_users(User *head);                                       /*function to free the allocted memory of the chat*/
void free_chats(Chat *head);                                       /*function to free the allocated memory of the chats*/
void command(char *Command);                                       /*function to handle the command */

#endif