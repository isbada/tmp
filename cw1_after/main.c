#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "USER_MANAGMENT.h"
#include "BOOK_MANAGMENT.h"

void load_data()
{
	FILE *fp = fopen("users.txt", "r");
	load_users(fp);
	if(fp) fclose(fp);
	fp = fopen("books.txt", "r");
	load_books(fp);
	if (fp) fclose(fp);
}

void store_data()
{
	FILE *fp = fopen("users.txt", "w");
	store_users(fp);
	if (fp) fclose(fp);
	fp = fopen("books.txt", "w");
	store_books(fp);
	if (fp) fclose(fp);
}

int login()
{
	int current_type = 0;
	int login_waiting = 1;
	while (login_waiting)
	{
		printf("Welcome to the library!\n1. Login\n2. Register\nPlease input your choice:");
		int sel = 0;
		while (sel != 1 && sel != 2)
		{
			scanf("%d", &sel);
			printf("\n");
		}

		if (sel == 1)
		{
			struct User user;
			printf("user name:");
			scanf("%s", user.username);
			printf("password:");
			scanf("%s", user.password);
			user.type = user_login(user);
			if (-1 == user.type)
			{
				printf("login failed!\n\n");
			}
			else
			{
				printf("login success!\n\n");
				login_waiting = 0;
				current_type = user.type;
			}
		}
		else
		{
			struct User user;
			printf("Select your role\n0. User\n1. Librarian\n");
			scanf("%d", &user.type);
			printf("set your user name:");
			scanf("%s", user.username);
			char password1[MAX_CHAR], password2[MAX_CHAR];
			printf("set your password:");
			scanf("%s", password1);
			printf("confirm your password:");
			scanf("%s", password2);
			while (0 != strcmp(password1, password2))
			{
				printf("your password is different from the first time!\n");
				printf("set your password:");
				scanf("%s", password1);
				printf("confirm your password:");
				scanf("%s", password2);
			}
			strcpy(user.password, password1);
			if (0 != user_register(user))
			{
				printf("register failed!\n");
			}
			else
			{
				printf("register success!\n");
			}
		}
	}
	return current_type;
}

int menu(int type)
{
	int cmd = -1;
	if (0 == type)
	{
		while (cmd < 0 || cmd>3)
		{
			printf("\nMenu\n1. Search for books\n2. Borrow book\n3. Return book\n0. Quit\nselect your choice:");
			scanf("%d", &cmd);
		}
	}
	else
	{
		while (cmd < 0 || cmd>5)
		{
			printf("\nMenu\n1. Search for books\n2. Borrow book\n3. Return book\n4. Add book\n5. Remove book\n0. Quit\nselect your choice:");
			scanf("%d", &cmd);
		}
	}
	return cmd;
}

void book_search()
{
	int sel = -1;
	while (sel < 1 || sel>3)
	{
		printf("\nSearch type:\n1. by title\n2. by author\n3. by year\ninput your choice:");
		scanf("%d", &sel);
	}
	struct BookArray result;
	if (sel == 1)
	{
		printf("please input title:");
		char title[CHAR_LIMIT_BOOK];
		scanf("%s", title); 
		result = find_book_by_title(title);
	}
	else if (sel == 2)
	{
		printf("please input author:");
		char author[CHAR_LIMIT_BOOK];
		scanf("%s", author);
		result = find_book_by_author(author);
	}
	else
	{
		printf("please input year:");
		int year;
		scanf("%d", &year);
		result = find_book_by_year(year);
	}
	if (result.length == 0)
	{
		printf("no book has been found!\n");
	}
	else
	{
		printf("\nResult list:\n", result.length);
		for (int i = 0; i < result.length; i++)
		{
			printf("No.%d\ntitle:%s\nauthors:%s\nyear:%d\ncopies:%d\n\n", i + 1, result.array[i].title, result.array[i].authors, result.array[i].year, result.array[i].copies);
			free(result.array[i].title);
			free(result.array[i].authors);
		}
		free(result.array);
	}
}

void book_borrow()
{
	struct Book book;
	book.title = (char*)malloc(sizeof(char) * CHAR_LIMIT_BOOK);
	book.authors = (char*)malloc(sizeof(char) * CHAR_LIMIT_BOOK);

	printf("input title:");
	scanf("%s", book.title);

	printf("input authors:");
	scanf("%s", book.authors);

	printf("input year:");
	scanf("%d", &book.year);

	book.copies = 1;

	int rt = borrow_book(book);

	free(book.title);
	free(book.authors);
	if (0 == rt) printf("The book has been successfully borrowed.\n");
	else printf("Borrow failed.");
}

void book_return()
{
	struct Book book;
	book.title = (char*)malloc(sizeof(char) * CHAR_LIMIT_BOOK);
	book.authors = (char*)malloc(sizeof(char) * CHAR_LIMIT_BOOK);

	printf("input title:");
	scanf("%s", book.title);

	printf("input authors:");
	scanf("%s", book.authors);

	printf("input year:");
	scanf("%d", &book.year);

	book.copies = 1;

	int rt = return_book(book);

	free(book.title);
	free(book.authors);
	if (0 == rt) printf("The book has been successfully returned.\n");
	else printf("Return failed.");
}

void book_add()
{
	struct Book book;
	book.title = (char*)malloc(sizeof(char) * CHAR_LIMIT_BOOK);
	book.authors = (char*)malloc(sizeof(char) * CHAR_LIMIT_BOOK);

	printf("input title:");
	scanf("%s", book.title);

	printf("input authors:");
	scanf("%s", book.authors);

	printf("input year:");
	scanf("%d", &book.year);

	printf("input copies:");
	scanf("%d", &book.copies);

	int rt = add_book(book);

	free(book.title);
	free(book.authors);
	if (0 == rt) printf("The book has been successfully added.\n");
	else printf("Added failed.");
}

void book_remove()
{
	struct Book book;
	book.title = (char*)malloc(sizeof(char) * CHAR_LIMIT_BOOK);
	book.authors = (char*)malloc(sizeof(char) * CHAR_LIMIT_BOOK);

	printf("input title:");
	scanf("%s", book.title);

	printf("input authors:");
	scanf("%s", book.authors);

	printf("input year:");
	scanf("%d", &book.year);

	int rt = remove_book(book);

	free(book.title);
	free(book.authors);
	if (0 == rt) printf("The book has been successfully removed.\n");
	else printf("Remove failed.");
}

void main()
{
	load_data();
	int user_type = login();
	int running = 1;
	while (running)
	{
		int cmd = menu(user_type);
		switch (cmd)
		{
		case 0:
			running = 0;
			break;
		case 1:
			book_search();
			break;
		case 2:
			book_borrow();
			break;
		case 3:
			book_return();
			break;
		case 4:
			book_add();
			break;
		case 5:
			book_remove();
			break;
		default:
			break;
		}
	}
	store_data();
}