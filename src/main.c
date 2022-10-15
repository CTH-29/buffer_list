#include <stdio.h>

#include "buffer_list.h"

buffer_list_t buf;

void pop_test(int index)
{
    char str[50];
    int len;
    if (buffer_list_pop_at(&buf, index, str, &len) >= 0)
    {
        str[len] = 0;
        printf("pop at [%d] str[%d] = %s\n", index, len, str);
    }
    else
    {
        printf("pop at [%d] fail\n", index);
    }
    //buffer_list_dump(&buf);
}

void peek_test(int index)
{
    char str[50];
    int len;
    if (buffer_list_peek_at(&buf, index, str, &len) >= 0)
    {
        str[len] = 0;
        printf("peek at [%d] str[%d] = %s\n", index, len, str);
    }
    else
    {
        printf("peek at [%d] fail\n", index);
    }
    //buffer_list_dump(&buf);
}

int main(int argc, char *argv[])
{
    printf("***************  main start ***************\n");

    buffer_list_init(&buf);
    buffer_list_push(&buf, "aaaaa", 5);
    buffer_list_push(&buf, "bbbbbb", 6);
    buffer_list_push(&buf, "ccccccc", 7);
    buffer_list_push(&buf, "dddddddddd", 10);
    buffer_list_push(&buf, "eeeee", 5);

    buffer_list_push_at(&buf, 5, "fffff", 6);
    buffer_list_push_at(&buf, 5, "gggggggg", 8);
    buffer_list_push_at(&buf, 3, "hhh", 3);

    buffer_list_dump(&buf);

    pop_test(0);
    pop_test(0);
    pop_test(0);
    pop_test(0);

    buffer_list_dump(&buf);

    peek_test(5);
    peek_test(4);
    peek_test(3);
    peek_test(2);
    peek_test(1);
    peek_test(0);

    buffer_list_clear(&buf);

    buffer_list_dump(&buf);

    printf("**************** main end ****************\n");

    return 0;
}