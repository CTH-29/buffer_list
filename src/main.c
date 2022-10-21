#include <stdio.h>
#include <string.h>

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
}

void pop2_test(int index)
{
    char *str;
    int len;
    if (bl_pop2_at(&buf, index, (void **)&str, &len) >= 0)
    {
        str[len] = 0;
        printf("pop at [%d] str[%d] = %s\n", index, len, str);
    }
    else
    {
        printf("pop at [%d] fail\n", index);
    }
}

void peek2_test(int index)
{
    char *str;
    int len;
    if (bl_peek2_at(&buf, index, (void **)&str, &len) >= 0)
    {
        str[len] = 0;
        printf("peek at [%d] str[%d] = %s\n", index, len, str);
    }
    else
    {
        printf("peek at [%d] fail\n", index);
    }
}

#define TEST_FUNC 0

int main(int argc, char *argv[])
{
    printf("***************  main start ***************\n");


    bl_init(&buf);
#if TEST_FUNC
    bl_push(&buf, "aaaaa", 5);
    bl_push(&buf, "bbbbbb", 6);
    bl_push(&buf, "ccccccc", 7);
    bl_push(&buf, "dddddddddd", 10);
    bl_push(&buf, "eeeee", 5);
    bl_push_at(&buf, 5, "fffff", 6);
    bl_push_at(&buf, 5, "gggggggg", 8);
    bl_push_at(&buf, 3, "hhh", 3);
#else
    bl_push2(&buf, strdup("aaaaa"), 5);
    bl_push2(&buf, strdup("bbbbbb"), 6);
    bl_push2(&buf, strdup("ccccccc"), 7);
    bl_push2(&buf, strdup("dddddddddd"), 10);
    bl_push2(&buf, strdup("eeeee"), 5);
    bl_push2_at(&buf, 5, strdup("fffff"), 6);
    bl_push2_at(&buf, 5, strdup("gggggggg"), 8);
    bl_push2_at(&buf, 3, strdup("hhh"), 3);
#endif

    bl_dump(&buf);

#if TEST_FUNC
    pop_test(0);
    pop_test(0);
    pop_test(0);
    pop_test(0);
#else
pop2_test(0);
    pop2_test(0);
    pop2_test(0);
    pop2_test(0);
#endif
    

    bl_dump(&buf);

#ifdef TEST_FUNC
    peek_test(5);
    peek_test(4);
    peek_test(3);
    peek_test(2);
    peek_test(1);
    peek_test(0);
#else
    peek2_test(5);
    peek2_test(4);
    peek2_test(3);
    peek2_test(2);
    peek2_test(1);
    peek2_test(0);
#endif

    bl_clear(&buf);

    bl_dump(&buf);

    printf("**************** main end ****************\n");

    return 0;
}