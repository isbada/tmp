#include "unity.h"
#include <stdio.h>
#include <string.h>
#include "BOOK_MANAGMENT.h"

void setUp(void) 
{
}

void tearDown(void) 
{
}

void test_function_load_books(void) 
{
	FILE *fp= fopen("not_exist.txt", "r");
	TEST_ASSERT_EQUAL(NULL, fp);
	TEST_ASSERT_EQUAL(-1, load_books(fp)); 
	fp = fopen("books.txt", "r");
	TEST_ASSERT_NOT_EQUAL(NULL, fp);
	TEST_ASSERT_EQUAL(0, load_books(fp));
	fclose(fp);
}

void test_function_search_books(void)
{
	struct BookArray result1 = find_book_by_author("name1");
	TEST_ASSERT_EQUAL(3, result1.length);
	struct BookArray result2 = find_book_by_title("book1");
	TEST_ASSERT_EQUAL(1, result2.length);
	TEST_ASSERT_EQUAL_STRING("book1", result2.array[0].title);
}

void test_function_store_books(void)
{
	FILE *fp = fopen("books1.txt", "w");
	int rt = store_books(fp);
	fclose(fp);
	TEST_ASSERT_EQUAL(0, rt);
}

void test_function_add_book(void)
{
	struct Book book;
	book.title = "book4";
	book.authors = "name2,name3,name4";
	book.year = 1222;
	book.copies = 6;
	int rt = add_book(book);
	TEST_ASSERT_EQUAL(0, rt);
}

void test_function_remove_books(void)
{
	struct Book book;
	book.title = "book2";
	book.authors = "name1,name2,name3";
	book.year = 2020;
	book.copies = 1;
	int rt = remove_book(book);
	TEST_ASSERT_EQUAL(0, rt);
	struct BookArray result = find_book_by_author("name1");
	TEST_ASSERT_EQUAL(2, result.length);
	rt = remove_book(book);
	TEST_ASSERT_EQUAL(-1, rt);
}


void test_function_borrow_return_books(void)
{
	struct Book book;
	book.title = "book1";
	book.authors = "name1,name2,name3";
	book.year = 2019;
	int rt = borrow_book(book);
	TEST_ASSERT_EQUAL(0, rt);
	rt = borrow_book(book);
	TEST_ASSERT_EQUAL(0, rt);
	rt = borrow_book(book);
	TEST_ASSERT_EQUAL(0, rt);
	rt = borrow_book(book);
	TEST_ASSERT_EQUAL(-1, rt);
	rt = return_book(book);
	TEST_ASSERT_EQUAL(0, rt);
	rt = return_book(book);
	TEST_ASSERT_EQUAL(0, rt);
}

// not needed when using generate_test_runner.rb
int main(void) {
	UNITY_BEGIN();
	RUN_TEST(test_function_load_books);
	RUN_TEST(test_function_search_books);
	RUN_TEST(test_function_add_book);
	RUN_TEST(test_function_borrow_return_books);
	RUN_TEST(test_function_remove_books);
	RUN_TEST(test_function_store_books);
	return UNITY_END();
}