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

void bl_init(buffer_list_t *bl);
int bl_push(buffer_list_t *bl, const void *data, int len);
int bl_push_at(buffer_list_t *bl, int index, const void *data, int len);
int bl_pop(buffer_list_t *bl, void *data, int *len);
int bl_pop_at(buffer_list_t *bl, int index, void *data, int *len);
int bl_peek(buffer_list_t *bl, void *data, int *len);
int bl_peek_at(buffer_list_t *bl, int index, void *data, int *len);

int bl_push2(buffer_list_t *bl, void *data, int len);
int bl_push2_at(buffer_list_t *bl, int index, void *data, int len);
int bl_pop2(buffer_list_t *bl, void **data, int *len);
int bl_pop2_at(buffer_list_t *bl, int index, void **data, int *len);
int bl_peek2(buffer_list_t *bl, void **data, int *len);
int bl_peek2_at(buffer_list_t *bl, int index, void **data, int *len);

int bl_clear(buffer_list_t *bl);
int bl_total(buffer_list_t *bl);

int bl_dump(buffer_list_t *bl);

#endif