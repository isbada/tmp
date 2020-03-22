#include "unity.h"
#include <stdio.h>
#include <string.h>
#include "USER MANAGMENT.h"

void setUp(void) 
{
}

void tearDown(void) 
{
}

void test_function_load_users(void) 
{
	FILE *fp = fopen("users.txt", "r");
	TEST_ASSERT_EQUAL(0, load_users(fp));
	fclose(fp);
	fp = NULL;
	TEST_ASSERT_EQUAL(fp, NULL);
	TEST_ASSERT_EQUAL(0, load_users(fp));
}

void test_function_store_users(void)
{
	FILE *fp = fopen("users1.txt", "w");
	int rt = store_users(fp);
	fclose(fp);
	TEST_ASSERT_EQUAL(0, rt);
}

void test_function_user_register_and_login(void)
{
	struct User user;
	strcpy(user.username, "user1");
	strcpy(user.password, "123456");
	user.type = TYPE_USER;

	int rt = user_login(user);
	TEST_ASSERT_EQUAL(-1, rt);
	rt = user_register(user);
	TEST_ASSERT_EQUAL(0, rt);
	rt = user_register(user);
	TEST_ASSERT_EQUAL(-1, rt);
	rt = user_login(user);
	TEST_ASSERT_EQUAL(0, rt);
}

void test_function_search_user(void)
{
	struct User user;
	strcpy(user.username, "user2");
	strcpy(user.password, "123456");
	user.type = TYPE_USER;

	int index = search_user(user.username);
	TEST_ASSERT_EQUAL(-1, index);
	user_register(user);
	index = search_user(user.username);
	TEST_ASSERT_EQUAL(1, index);
}

// not needed when using generate_test_runner.rb
int main(void) {
	UNITY_BEGIN();
	RUN_TEST(test_function_load_users);
	RUN_TEST(test_function_user_register_and_login);
	RUN_TEST(test_function_search_user);
	RUN_TEST(test_function_store_users);
	return UNITY_END();
}