/**
 * this is a buffer list:
 *      pop <- { [0] [1] [2] ... [n] } <- push
 *                |               |
 *              head            tail
 * that means buffer[0] live longest.
*/
#ifndef __BUFFER_LIST_H__
#define __BUFFER_LIST_H__

#include <pthread.h>

typedef struct buffer
{
    struct buffer *next;
    int len;
    void *data;
} buffer_t;

typedef struct buffer_list
{
    int total;
    buffer_t *head;
    buffer_t *tail;
    pthread_mutex_t mutex;
} buffer_list_t;

void buffer_list_init(buffer_list_t *buflist);
int buffer_list_push(buffer_list_t *buflist, const void *data, int len);
int buffer_list_push_at(buffer_list_t *buflist, int index, const void *data, int len);
int buffer_list_pop(buffer_list_t *buflist, void *data, int *len);
int buffer_list_pop_at(buffer_list_t *buflist, int index, void *data, int *len);
int buffer_list_peek(buffer_list_t *buflist, void *data, int *len);
int buffer_list_peek_at(buffer_list_t *buflist, int index, void *data, int *len);
int buffer_list_clear(buffer_list_t *buflist);
int buffer_list_total(buffer_list_t *buflist);

int buffer_list_dump(buffer_list_t *buflist);

#endif