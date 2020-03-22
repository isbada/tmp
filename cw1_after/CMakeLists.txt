project(HW1)
add_executable(main main.c BOOK_MANAGMENT.c USER_MANAGMENT.c)
add_executable(test_book unity.c BOOK_MANAGMENT.c test_for_book.c)
add_executable(test_user unity.c USER_MANAGMENT.c test_for_user.c)