#include <stdio.h>

#include "buffer_list.h"

buffer_list_t buf;

void pop_test(int index)
{
    char str[50];
    int len;
    if (bl_pop_at(&buf, index, str, &len) >= 0)
    {
        str[len] = 0;
        printf("pop at [%d] str[%d] = %s\n", index, len, str);
    }
    else
    {
        printf("pop at [%d] fail\n", index);
    }
    //bl_dump(&buf);
}

void peek_test(int index)
{
    char str[50];
    int len;
    if (bl_peek_at(&buf, index, str, &len) >= 0)
    {
        str[len] = 0;
        printf("peek at [%d] str[%d] = %s\n", index, len, str);
    }
    else
    {
        printf("peek at [%d] fail\n", index);
    }
    //bl_dump(&buf);
}

int main(int argc, char *argv[])
{
    printf("***************  main start ***************\n");

    bl_init(&buf);
    bl_push(&buf, "aaaaa", 5);
    bl_push(&buf, "bbbbbb", 6);
    bl_push(&buf, "ccccccc", 7);
    bl_push(&buf, "dddddddddd", 10);
    bl_push(&buf, "eeeee", 5);

    bl_push_at(&buf, 5, "fffff", 6);
    bl_push_at(&buf, 5, "gggggggg", 8);
    bl_push_at(&buf, 3, "hhh", 3);

    bl_dump(&buf);

    pop_test(0);
    pop_test(0);
    pop_test(0);
    pop_test(0);

    bl_dump(&buf);

    peek_test(5);
    peek_test(4);
    peek_test(3);
    peek_test(2);
    peek_test(1);
    peek_test(0);

    bl_clear(&buf);

    bl_dump(&buf);

    printf("**************** main end ****************\n");

    return 0;
}