#include "USER_MANAGMENT.h"
#include <string.h>
#include <stdlib.h>

struct UserArray user_list;
struct User current_user;
int is_login = 0;
int store_users(FILE * file)
{
	if (file)
	{
		for (unsigned int i = 0; i < user_list.length; i++)
		{
			fprintf_s(file, "%s %s %d\n", user_list.array[i].username, user_list.array[i].password, user_list.array[i].type);
		}
		free(user_list.array);
		return 0;
	}
	return -1;
}

int load_users(FILE * file)
{
	user_list.array = (struct User*)malloc(sizeof(struct User) * MAX_MUN_USER);
	user_list.length = 0;
	for (int i = 0; i < MAX_MUN_USER; i++)
	{
		memset(user_list.array[i].username, 0, sizeof(user_list.array[i].username));
		memset(user_list.array[i].password, 0, sizeof(user_list.array[i].password));
		user_list.array[i].type = 0;
	}
	if (file)
	{
		char username[MAX_CHAR], password[MAX_CHAR];
		memset(username, 0, sizeof(username));
		memset(password, 0, sizeof(password));
		int type = 0;
		int rt = fscanf(file, "%s %s %d\n", username, password, &type);
		while (rt != -1)
		{
			int id = user_list.length;
			strcpy(user_list.array[id].username, username);
			strcpy(user_list.array[id].password, password);
			user_list.array[id].type = type;
			user_list.length++;
			rt = fscanf(file, "%s %s %d\n", username, password, &type);
		}
	}
	return 0;
}

int user_register(struct User user)
{
	int index = search_user(user.username);
	if (index != -1)
	{
		return -1;
	}
	else if (user.type != 1 && user.type != 0)
	{
		return -1;
	}
	else
	{
		int id = user_list.length;
		strcpy(user_list.array[id].username, user.username);
		strcpy(user_list.array[id].password, user.password);
		user_list.array[id].type = user.type;
		user_list.length++;
		return 0;
	}
}

int user_login(struct User user)
{
	int index = search_user(user.username);
	if (index == -1)
	{
		is_login = 0;
		return -1;
	}
	if (0 == strcmp(user.password, user_list.array[index].password))
	{
		current_user = user;
		is_login = 1;
		return user_list.array[index].type;
	}
}

int search_user(const char * user_name)
{
	for (int i = 0; i < user_list.length; i++)
	{
		if (0 == strcmp(user_name, user_list.array[i].username))
		{
			return i;
		}
	}
	return -1;
}
