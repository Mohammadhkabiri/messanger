#include "function.h"

User *create_User_node(char *username, char *password) /*function to create user with Username and password*/
{
    User *new_node = (User *)malloc(sizeof(User)); /*give a memory from heap to create usernode*/
    strcpy(new_node->Username, username);          /*copy the username that user input in the username of user*/
    strcpy(new_node->Password, password);          /*copy the password that user input in the password of user*/
    new_node->islogin = 0;                         /*initilize this variable beacuse nobody logged in at first*/
    new_node->next = NULL;
    return new_node; /*return the newnode -output the function*/
}

void add_user(User **head, User **tail, char *username, char *password) /*function to add new user to the userlist*/
{
    User *new_node = create_User_node(username, password);
    if (*head == NULL)
    { /*if the list is empty add a new user to haed and tail*/
        *head = new_node;
        *tail = new_node;
    }
    else
    {
        (*tail)->next = new_node; /*if the list is not empty add the newuser at the end of list*/
        *tail = new_node;         /*to point the new node created*/
    }
}
int check_username(User *head, char *username) /*function to check if the username already exist*/
{
    User *temp = head;
    while (temp != NULL) /*loop to go forward the userlinklist*/
    {
        if (!strcmp(temp->Username, username)) /*to go next in the nodelist*/
        {
            return 0; /*return 0  if the username matched with one of the username in the list*/
        }
        temp = temp->next;
    }
    return 1; /*return 1 if the username doesnt match*/
}

void signup(User **user_head, User **user_tail) /*function to signup a person*/
{
    char Username[MAX_CHARACTER]; /*array to keep the username of users*/
    char Password[MAX_CHARACTER]; /*array to keep the password of the users*/

    printf("Username: ");
    scanf("%s", Username);
    printf("Password: ");
    scanf("%s", Password);

    if (check_username(*user_head, Username)) /*check if the username is true and not used before*/
    {
        add_user(user_head, user_tail, Username, Password); /*add the new user with giving the head of user linklist,tail of user linklist , username and password */
        printf("User %s successfully registered!\n", Username);
    }
    else /*if the username used before by someone else*/
    {
        printf("Error: Username %s already exists.\n", Username);
    }
}

void load_user(User **head, User **tail) /*function to signup the user with the information of file*/
{
    char fileName[MAX_CHARACTER];
    printf("Enter filename: ");
    scanf("%s", fileName);

    if (strcmp(fileName, INPUT_FILE)) /*check if the inputed filename and filename don,t matched */
    {
        printf("Error: Unable to open file %s.\n", fileName);
        return;
    }

    FILE *input = fopen(INPUT_FILE, "r");
    if (input == NULL) /*check if the inputed file is null or an error accoured when we wan,t to open file*/
    {
        printf("Error: Could not open file %s.\n", INPUT_FILE);
        return;
    }

    char User_Password_file[MAX_FILE_CHARACTER]; /*array to keep the characters in the file*/
    char Username[MAX_CHARACTER];                /*array to keep the username of the person that we want to signup from the file*/
    char Password[MAX_CHARACTER];                /*array to keep the password of the people that we want to signup from the file*/
    int line = 1;                                /*initilize the line of the file*/
    int counter = 0;                             /*initilize the user that successfuly registered*/

    while (fgets(User_Password_file, sizeof(User_Password_file), input))
    {
        int length = strlen(User_Password_file);    /*to calculate the eachline characters*/
        if (User_Password_file[length - 1] == '\n') /*to continiue from the file and read all characters in that with fgets*/
        {
            User_Password_file[length - 1] = '\0';
        }

        if (sscanf(User_Password_file, "%s %s", Username, Password) == 2) /*check if sscanf successfuly get the strings*/
        {
            if (check_username(*head, Username)) /*check if the username did,nt used before*/
            {
                add_user(head, tail, Username, Password); /*add the user to userlinklist*/
                counter++;                                /*increment this variable to know how many people signed up from the file information*/
            }
            else
            {
                printf("Warning: Username '%s' already exists. Skipping line %d.\n", Username, line);
            }
        }
        else
        {
            printf("Warning: Invalid format in line %d. Skipping.\n", line);
        }
        line++; /*increment the line variable to know the line that will be read*/
    }
    printf("Users successfully loaded from %s, %d user(s) added.\n", INPUT_FILE, counter);
    fclose(input); /*close the file after finish the work with the file*/
}

void login(User *user_head, User **logged_in_user, int *login_status) /*function to login a peson*/
{
    char Username[MAX_CHARACTER]; /*array to keep the username characters*/
    char Password[MAX_CHARACTER]; /*array to keep the password characters*/

    if (*login_status) /*check if some one is login give a apppropite notif*/
    {
        printf("Error: There is an open session, please logout first.\n");
        return;
    }

    printf("Username: ");
    scanf("%s", Username);
    printf("Password: ");
    scanf("%s", Password);

    User *temp = user_head;
    while (temp != NULL) /*loop to go forward in the user linklist*/
    {
        if (!strcmp(temp->Username, Username) && !strcmp(temp->Password, Password)) /*check if password and username matched*/
        {
            *logged_in_user = temp;
            (*logged_in_user)->islogin = 1; /*change the paramater of the */
            *login_status = 1;              /*change the login status*/
            printf("User %s logged in successfully.\n", Username);
            return;
        }
        temp = temp->next;
    }
    printf("Error: Invalid username or password.\n");
}

Chat *create_Chat_node(char *name, User *user1, User *user2) /*function to create newchat with chat name and 2 user*/
{
    Chat *new_node = (Chat *)malloc(sizeof(Chat)); /*give a memory from heap to create new chat node*/
    strcpy(new_node->chat_name, name);             /*copy the name in chatname of chatnode*/
    new_node->user1 = user1;
    new_node->user2 = user2;
    new_node->messages_head = NULL;
    new_node->messages_tail = NULL;
    new_node->next = NULL;
    return new_node;
}

void add_chat(Chat **head, Chat **tail, char *name, User *user1, User *user2) /*function to add newchat to the chatlist*/
{
    Chat *new_node = create_Chat_node(name, user1, user2); /*take user 1 and user 2 to create a chat beetween them with name of name variable*/
    if (*head == NULL)                                     /*check if the chatlist is empty put newnode in both head and tail*/
    {
        *head = new_node;
        *tail = new_node;
    }
    else
    {
        (*tail)->next = new_node;
        *tail = new_node;
    }
}

void newchat(Chat **chat_head, Chat **chat_tail, User *logged_in_user, User *user_head) /*funct*/
{
    int repeat = 0;
    if (logged_in_user == NULL) /*check if nobody currently logged in*/
    {
        printf("Error: No user is currently logged in.\n");
        return;
    }

    char chat_name[MAX_CHARACTER]; /*array to keep the username characters*/
    char Username[MAX_CHARACTER];  /*array to keep the password characters*/

    printf("Enter chat name: ");
    scanf("%s", chat_name);
    printf("Enter username to chat with: ");
    scanf("%s", Username);

    User *chat_user = NULL;                                       /*initilize the person that logged in person want to chat with*/
    for (User *temp = user_head; temp != NULL; temp = temp->next) /*loop to go forward the user linklist*/
    {
        if (!strcmp(temp->Username, Username)) /*check if the username matched*/
        {
            if (temp != logged_in_user) /*check the inputed username and logged in user are diffrent*/
            {
                chat_user = temp;
                break;
            }
            else
            {
                printf("Error: You cannot create a chat with yourself.\n");
                return;
            }
        }
    }

    for (Chat *temp = *chat_head; temp != NULL; temp = temp->next) /*loop to go forward the chat linklist*/
    {
        if (!strcmp(temp->chat_name, chat_name)) /*check if the inputed chatname and chat name are same */
        {
            printf("Error: Chat with name %s already exists.\n", temp->chat_name);
            repeat = 1;
        }
    }

    if (chat_user != NULL && !repeat) /*if a chat user is valid and the chatname was not already exist*/
    {
        add_chat(chat_head, chat_tail, chat_name, logged_in_user, chat_user);
        printf("Chat with the name %s created between %s and %s successfully.\n", chat_name, logged_in_user->Username, chat_user->Username);
    }
    else if (chat_user == NULL) /*check if the user you wanna chat with is not valid*/
    {
        printf("Error: User %s not found.\n", Username);
    }
}

int selectchat(Chat *chat_head, User *logged_in_user, Chat **current_chat) /*function to selectchat*/
{
    char chat_name2[MAX_CHARACTER];
    if (logged_in_user == NULL) /*check if someone is not logged in now*/
    {
        printf("Enter chat name: ");
        scanf("%s", chat_name2);
        printf("Error: No user is currently logged in.\n");
        return 0;
    }

    char chat_name[MAX_CHARACTER]; /*array to keep the chat name characters*/
    printf("Enter chat name: ");
    scanf("%s", chat_name);

    for (Chat *temp = chat_head; temp != NULL; temp = temp->next) /*loop to go forward the chat linklist*/
    {
        if (!strcmp(temp->chat_name, chat_name) &&
            (temp->user1 == logged_in_user || temp->user2 == logged_in_user)) /*check if inputed chatname and one of the chat in the chatlist are matched and the user that want to select can access that*/
        {
            *current_chat = temp;
            printf("Chat %s has been selected as the current chat successfully.\n", chat_name);
            return 1;
        }
    }
    printf("Error: Chat %s not found for User %s.\n", chat_name, logged_in_user->Username);
    return 0;
}

Message *create_message_node(char *content, char *author) /*function to create message node*/
{
    Message *new_node = (Message *)malloc(sizeof(Message));
    strcpy(new_node->content, content); /*copy the content of message in the part of messagecontent*/
    strcpy(new_node->author, author);   /*copy the author in the messageaithor*/
    new_node->next = NULL;
    return new_node; /*return the newmessage node for the output of function*/
}

void add_message_to_chat(Chat *chat, char *content, char *author) /*function to add new message to chat*/
{
    Message *new_node = create_message_node(content, author); /*create message node with content and author*/
    if (chat->messages_head == NULL)
    {
        chat->messages_head = new_node;
        chat->messages_tail = new_node;
    }
    else
    {
        chat->messages_tail->next = new_node;
        chat->messages_tail = new_node;
    }
}

void sendmessage(Chat *current_chat, User *logged_in_user) /*function to sendMessage*/
{
    if (current_chat == NULL)
    {
        printf("Error: No chat selected.Please select a chat first.\n");
        return;
    }

    char message_content[MAX_MESSAGE_CONTENT];
    if (!strcmp(current_chat->user1->Username, logged_in_user->Username)) /*to know which one of person in the chat will recieve the message in the chat*/
    {
        printf("Reciever : %s \n", current_chat->user2->Username);
    }
    else if (!strcmp(current_chat->user2->Username, logged_in_user->Username))
    {
        printf("Reciever : %s \n", current_chat->user1->Username);
    }
    printf("Enter message: ");
    getchar();                                          /*to empty stdin before take strings with fgets*/
    fgets(message_content, MAX_MESSAGE_CONTENT, stdin); /*to get the message from the user*/
    message_content[strcspn(message_content, "\n")] = '\0';

    add_message_to_chat(current_chat, message_content, logged_in_user->Username); /*call function to add this chat with the information logged in person username , message content , and the chat we want to send message in that*/
    printf("Message sent successfully.\n");
}

void show_chat(Chat *chat) /*function to show the messages of the chat*/
{
    Message *temp = chat->messages_head;
    if (temp == NULL) /*if no messagenode availble in the chat*/
    {
        printf("No messages in this chat.\n");
        return;
    }
    printf("Messages in Chat '%s':\n", chat->chat_name);
    while (temp != NULL) /*loop to go forward the chat linklist*/
    {
        printf("%s: %s\n", temp->author, temp->content);
        temp = temp->next;
    }
}

void check_showchat(Chat *current_chat) /*function show chat*/
{
    if (current_chat == NULL) /*check if no chat selected to show the message of that*/
    {
        printf("Error: No chat selected.Please select a chat first.\n");
        return;
    }
    show_chat(current_chat);
}

void free_users(User *head) /*function to free the memory of the users*/
{
    User *temp;
    while (head != NULL) /*loop to go forward the users linklist*/
    {
        temp = head;
        head = head->next;
        free(temp); /*free the allocted memory*/
    }
}

void free_chats(Chat *head) /*function to free the memory of the chat*/

{
    Chat *temp;
    while (head != NULL) /*loop to go forward the chat linklist*/
    {
        temp = head;
        head = head->next;
        free(temp); /*free the allocated memory*/
    }
}

void command(char *Command) /*function to handle the command of the users*/
{
    int status = 1;       /*variable to know program is runing or not*/
    int login_status = 0; /*variable to check if someone logged in the program*/
    int select_status;    /*variable to check if chat is selected*/

    User *user_head = NULL, *user_tail = NULL; /*initialize the user head and user tail*/
    Chat *chat_head = NULL, *chat_tail = NULL; /*initialize the chat head and chat tail*/
    User *logged_in_user = NULL;               /*initialize the login person*/
    Chat *current_chat = NULL;                 /*initialize the current chat*/

    printf("Enter Command: ");
    while (status) /*check if the program is runing with status variable*/
    {
        scanf("%s", Command);
        if (!strcmp(Command, SIGNUP)) /*check if the command is signup*/
        {
            signup(&user_head, &user_tail);
        }
        else if (!strcmp(Command, LOGIN)) /*check if the command is login*/
        {
            login(user_head, &logged_in_user, &login_status);
        }
        else if (!strcmp(Command, LOGOUT)) /*check if the command is logout*/
        {
            if (logged_in_user != NULL) /*check if the user is already logged in*/
            {
                logged_in_user->islogin = 0;
                select_status = 0; /*set the selectedchat variable to 0 again after someone logout*/
                printf("User %s logged out successfully.\n", logged_in_user->Username);
                logged_in_user = NULL; /*set the logged in person to null beacuse no one is already logged in the program*/
                login_status = 0;
            }
            else
            {
                printf("Error: No user is currently logged in.\n");
            }
        }
        else if (!strcmp(Command, NEW_CHAT)) /*check if the command is newchat*/
        {
            newchat(&chat_head, &chat_tail, logged_in_user, user_head);
        }
        else if (!strcmp(Command, SELECT_CHAT)) /*check if the command is selectchat*/
        {
            select_status = selectchat(chat_head, logged_in_user, &current_chat);
        }
        else if (!strcmp(Command, SEND_MESSAGE)) /*check if the command is sendmessage*/
        {
            if (select_status)
            {
                sendmessage(current_chat, logged_in_user);
            }
            else
            {
                printf("Error: No chat selected.\n");
            }
        }
        else if (!strcmp(Command, SHOW_CHAT)) /*check if the command is showchat*/
        {
            if (select_status)
            {
                check_showchat(current_chat);
            }
            else
            {
                printf("Error: No chat selected.\n");
            }
        }
        else if (!strcmp(Command, EXIT)) /*check if the command is exit what should be done*/
        {
            status = 0;
            free_users(user_head); /*free users memory after exit the program*/
            free_chats(chat_head); /*free chats memory after exit the program*/
            break;
        }
        else if (!strcmp(Command, LOAD_USER)) /*check if the command is loaduser*/
        {
            load_user(&user_head, &user_tail);
        }
        else /*if user command not valid*/
        {
            printf("Unknown command.\n");
        }
        printf("Enter Command: ");
    }
}