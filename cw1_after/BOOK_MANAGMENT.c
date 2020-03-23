#include "BOOK_MANAGMENT.h"
#include <stdlib.h>
#include <string.h>

static struct BookArray book_list;
#define MAX_NUM_BOOK	1000
int store_books(FILE * file)
{
	if (file)
	{
		unsigned int i = 0;
		for (i = 0; i < book_list.length; i++)
		{
			fprintf_s(file, "&%s;%s %d %d\n", book_list.array[i].title, book_list.array[i].authors, book_list.array[i].year, book_list.array[i].copies);
		}
		fputc('#', file);
		for (i = 0; i < MAX_NUM_BOOK; i++)
		{
			free(book_list.array[i].authors);
			free(book_list.array[i].title);
		}
		free(book_list.array);
		return 0;
	}
	return -1;
}

int load_books(FILE * file)
{
	book_list.array = (struct Book*)malloc(sizeof(struct Book) * MAX_NUM_BOOK);
	book_list.length = 0;
	unsigned int i = 0;
	for (i = 0; i < MAX_NUM_BOOK; i++)
	{
		book_list.array[i].year = 0;
		book_list.array[i].copies = 0;
		book_list.array[i].authors = (char*)malloc(sizeof(char) * CHAR_LIMIT_BOOK);
		book_list.array[i].title = (char*)malloc(sizeof(char) * CHAR_LIMIT_BOOK);
	}
	if (file)
	{
		char title[CHAR_LIMIT_BOOK], authors[CHAR_LIMIT_BOOK];
		memset(title, 0, sizeof(title));
		memset(authors, 0, sizeof(authors));
		unsigned int year = 0, copies = 0;
		char rt = fgetc(file);
		while (rt != '#')
		{
			int index = 0; rt = fgetc(file);
			while (rt != ';')
			{
				title[index++] = rt;
				rt = fgetc(file);
			}
			fscanf(file, "%s %d %d\n", authors, &year, &copies);
			int id = book_list.length;
			book_list.array[id].year = year;
			book_list.array[id].copies = copies;
			strcpy(book_list.array[id].authors, authors);
			strcpy(book_list.array[id].title, title);
			book_list.length++;
			rt = fgetc(file);
		}
		return 0;
	}
	return -1;
}

int add_book(struct Book book)
{
	if (book_list.length >= MAX_NUM_BOOK) return -1;
	else
	{
		int id = -1;
		unsigned int i = 0;
		for (i = 0; i < book_list.length; i++)
		{
			if (0 == strcmp(book_list.array[i].title, book.title) &&
				0 == strcmp(book_list.array[i].authors, book.authors) &&
				book_list.array[i].year == book.year)
			{
				id = i; break;
			}
		}
		if (id == -1)
		{
			int id = book_list.length;
			book_list.array[id].year = book.year;
			book_list.array[id].copies = book.copies;
			strcpy(book_list.array[id].authors, book.authors);
			strcpy(book_list.array[id].title, book.title);
			book_list.length++;
		}
		else
		{
			book_list.array[id].copies += book.copies;
		}
		return 0;
	}
}

int remove_book(struct Book book)
{
	int id = -1;
	unsigned int i = 0;
	for (i = 0; i < book_list.length; i++)
	{
		if (0 == strcmp(book_list.array[i].title, book.title) &&
			0 == strcmp(book_list.array[i].authors, book.authors) &&
			book_list.array[i].year == book.year)
		{
			id = i; break;
		}
	}
	if (id == -1)
	{
		return -1;
	}
	else
	{
		unsigned int size = book_list.length;
		strcpy(book_list.array[id].title, book_list.array[size].title);
		strcpy(book_list.array[id].authors, book_list.array[size].authors);
		book_list.array[id].copies = book_list.array[size].copies;
		book_list.array[id].year = book_list.array[size].year;
		book_list.length--;
		return 0;
	}
}

int borrow_book(struct Book book)
{
	int id = -1;
	unsigned int i = 0;
	for (i = 0; i < book_list.length; i++)
	{
		if (0 == strcmp(book_list.array[i].title, book.title) &&
			0 == strcmp(book_list.array[i].authors, book.authors) &&
			book_list.array[i].year == book.year)
		{
			id = i; break;
		}
	}
	if (id == -1)
	{
		return -1;
	}
	else if (book_list.array[id].copies <= 0)
	{
		return -1;
	}
	else
	{
		book_list.array[id].copies--;
		return 0;
	}
}

int return_book(struct Book book)
{
	int id = -1;
	unsigned int i = 0;
	for (i = 0; i < book_list.length; i++)
	{
		if (0 == strcmp(book_list.array[i].title, book.title) &&
			0 == strcmp(book_list.array[i].authors, book.authors) &&
			book_list.array[i].year == book.year)
		{
			id = i; break;
		}
	}
	if (id == -1)
	{
		return -1;
	}
	else
	{
		book_list.array[id].copies++;
		return 0;
	}
}

struct BookArray find_book_by_title(const char * title)
{
	struct BookArray result;
	result.array = (struct Book*)malloc(sizeof(struct Book) * MAX_NUM_BOOK);
	result.length = 0;
	unsigned int i = 0;
	for (i = 0; i < book_list.length; i++)
	{
		if (0 == strcmp(book_list.array[i].title, title))
		{
			int id = result.length;
			result.array[id].year = book_list.array[i].year;
			result.array[id].copies = book_list.array[i].copies;
			result.array[id].title = (char*)malloc(sizeof(char) * CHAR_LIMIT_BOOK);
			result.array[id].authors = (char*)malloc(sizeof(char) * CHAR_LIMIT_BOOK);
			strcpy(result.array[id].title, book_list.array[i].title);
			strcpy(result.array[id].authors, book_list.array[i].authors);
			result.length++;
		}
	}
	if (result.length == 0)
	{
		free(result.array);
		result.array = NULL;
	}
	return result;
}

struct BookArray find_book_by_author(const char * author)
{
	struct BookArray result;
	result.array = (struct Book*)malloc(sizeof(struct Book) * MAX_NUM_BOOK);
	result.length = 0;
	unsigned int i = 0;
	for (i = 0; i < book_list.length; i++)
	{
		if (strstr(book_list.array[i].authors, author))
		{
			int id = result.length;
			result.array[id].year = book_list.array[i].year;
			result.array[id].copies = book_list.array[i].copies;
			result.array[id].title = (char*)malloc(sizeof(char) * CHAR_LIMIT_BOOK);
			result.array[id].authors = (char*)malloc(sizeof(char) * CHAR_LIMIT_BOOK);
			strcpy(result.array[id].authors, book_list.array[i].authors);
			strcpy(result.array[id].title, book_list.array[i].title);
			result.length++;
		}
	}
	if (result.length == 0)
	{
		free(result.array);
		result.array = NULL;
	}
	return result;
}

struct BookArray find_book_by_year(unsigned int year)
{
	struct BookArray result;
	result.array = (struct Book*)malloc(sizeof(struct Book) * MAX_NUM_BOOK);
	result.length = 0;
	unsigned int i = 0;
	for (i = 0; i < book_list.length; i++)
	{
		if (year == book_list.array[i].year)
		{
			int id = result.length;
			result.array[id].year = book_list.array[i].year;
			result.array[id].copies = book_list.array[i].copies;
			strcpy_s(result.array[id].authors, strlen(book_list.array[i].authors), book_list.array[i].authors);
			strcpy_s(result.array[id].title, strlen(book_list.array[i].title), book_list.array[i].title);
			result.length++;
		}
	}
	if (result.length == 0)
	{
		free(result.array);
		result.array = NULL;
	}
	return result;
}
