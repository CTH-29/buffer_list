#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "buffer_list.h"

buffer_t *buffer_new(const void *data, int len)
{
    buffer_t *new = (buffer_t *)malloc(sizeof(buffer_t));
    new->data = malloc(len);
    memcpy(new->data, data, len);
    new->len = len;
    new->next = NULL;
    return new;
}

buffer_t *buffer_new2(void *data, int len)
{
    buffer_t *new = (buffer_t *)malloc(sizeof(buffer_t));
    new->data = data;
    new->len = len;
    new->next = NULL;
    return new;
}

void buffer_destroy(buffer_t *buf)
{
    if (buf)
    {
        free(buf->data);
        free(buf);
    }
}

void buffer_destroy2(buffer_t *buf)
{
    if (buf)
    {
        free(buf);
    }
}

void bl_init(buffer_list_t *bl)
{
    bl->total = 0;
    bl->head = NULL;
    bl->tail = NULL;
    pthread_mutex_init(&(bl->mutex), NULL);
}

int bl_push(buffer_list_t *bl, const void *data, int len)
{
    if (bl)
    {
        pthread_mutex_lock(&(bl->mutex));
        if (bl->total == 0)
        {
            bl->head = buffer_new(data, len);
            bl->tail = bl->head;
        }
        else
        {
            bl->tail->next = buffer_new(data, len);
            bl->tail = bl->tail->next;
        }
        bl->total++;
        pthread_mutex_unlock(&(bl->mutex));
        return bl->total;
    }
    return -1;
}

int bl_push_at(buffer_list_t *bl, int index, const void *data, int len)
{
    int i;
    buffer_t *prev_tmp;
    buffer_t *next_tmp;
    if (bl)
    {
        if (index >= 0 && index <= bl->total)
        {
            pthread_mutex_lock(&(bl->mutex));
            prev_tmp = bl->head;
            if (index == 0)
            {
                bl->head = buffer_new(data, len);
                bl->head->next = prev_tmp;
                if (bl->tail == NULL)
                    bl->tail = bl->head;
            }
            else
            {
                if (index == bl->total)
                {
                    bl->tail->next = buffer_new(data, len);
                    bl->tail = bl->tail->next;
                }
                else
                {
                    for (i = 0; i < index - 1; i++)
                        prev_tmp = prev_tmp->next;
                    next_tmp = prev_tmp->next;
                    prev_tmp->next = buffer_new(data, len);
                    prev_tmp->next->next = next_tmp;
                }
            }
            bl->total++;
            pthread_mutex_unlock(&(bl->mutex));
            return bl->total;
        }
    }
    return -1;
}

int bl_pop(buffer_list_t *bl, void *data, int *len)
{
    if (bl)
    {
        if (bl->total > 0)
        {
            pthread_mutex_lock(&(bl->mutex));
            *len = bl->head->len;
            memcpy(data, bl->head->data, bl->head->len);
            buffer_t *head_tmp = bl->head;
            bl->head = bl->head->next;
            buffer_destroy(head_tmp);
            bl->total--;
            pthread_mutex_unlock(&(bl->mutex));
        }
        return bl->total;
    }
    return -1;
}

int bl_pop_at(buffer_list_t *bl, int index, void *data, int *len)
{
    int i;
    buffer_t *prev_tmp;
    buffer_t *next_tmp;
    if (bl)
    {
        if (bl->total > 0 && index >= 0 && index < bl->total)
        {
            pthread_mutex_lock(&(bl->mutex));
            if (index == 0)
            {
                prev_tmp = bl->head;
                *len = prev_tmp->len;
                memcpy(data, prev_tmp->data, prev_tmp->len);
                if (bl->total == 1)
                {
                    bl->head = NULL;
                    bl->tail = NULL;
                }
                else
                {
                    bl->head = prev_tmp->next;
                }
                buffer_destroy(prev_tmp);
            }
            else
            {
                prev_tmp = bl->head;
                for (i = 0; i < index - 1; i++)
                    prev_tmp = prev_tmp->next;
                next_tmp = prev_tmp->next->next;
                *len = prev_tmp->next->len;
                memcpy(data, prev_tmp->next->data, prev_tmp->next->len);
                buffer_destroy(prev_tmp->next);
                prev_tmp->next = next_tmp;
            }
            bl->total--;
            pthread_mutex_unlock(&(bl->mutex));
            return bl->total;
        }
    }
    return -1;
}

int bl_peek(buffer_list_t *bl, void *data, int *len)
{
    if (bl)
    {
        pthread_mutex_lock(&(bl->mutex));
        if (bl->total > 0)
        {
            *len = bl->head->len;
            memcpy(data, bl->head->data, bl->head->len);
        }
        pthread_mutex_unlock(&(bl->mutex));
        return bl->total;
    }
    return -1;
}

int bl_peek_at(buffer_list_t *bl, int index, void *data, int *len)
{
    int i;
    buffer_t *peek_tmp;
    if (bl)
    {
        if (bl->total > 0 && index >= 0 && index < bl->total)
        {
            pthread_mutex_lock(&(bl->mutex));
            peek_tmp = bl->head;
            for (i = 0; i < index; i++)
                peek_tmp = peek_tmp->next;
            *len = peek_tmp->len;
            memcpy(data, peek_tmp->data, peek_tmp->len);
            pthread_mutex_unlock(&(bl->mutex));
            return bl->total;
        }
    }
    return -1;
}

int bl_push2(buffer_list_t *bl, void *data, int len)
{
    if (bl)
    {
        pthread_mutex_lock(&(bl->mutex));
        if (bl->total == 0)
        {
            bl->head = buffer_new2(data, len);
            bl->tail = bl->head;
        }
        else
        {
            bl->tail->next = buffer_new2(data, len);
            bl->tail = bl->tail->next;
        }
        bl->total++;
        pthread_mutex_unlock(&(bl->mutex));
        return bl->total;
    }
    return -1;
}

int bl_push2_at(buffer_list_t *bl, int index, void *data, int len)
{
    int i;
    buffer_t *prev_tmp;
    buffer_t *next_tmp;
    if (bl)
    {
        if (index >= 0 && index <= bl->total)
        {
            pthread_mutex_lock(&(bl->mutex));
            prev_tmp = bl->head;
            if (index == 0)
            {
                bl->head = buffer_new2(data, len);
                bl->head->next = prev_tmp;
                if (bl->tail == NULL)
                    bl->tail = bl->head;
            }
            else
            {
                if (index == bl->total)
                {
                    bl->tail->next = buffer_new2(data, len);
                    bl->tail = bl->tail->next;
                }
                else
                {
                    for (i = 0; i < index - 1; i++)
                        prev_tmp = prev_tmp->next;
                    next_tmp = prev_tmp->next;
                    prev_tmp->next = buffer_new2(data, len);
                    prev_tmp->next->next = next_tmp;
                }
            }
            bl->total++;
            pthread_mutex_unlock(&(bl->mutex));
            return bl->total;
        }
    }
    return -1;
}


int bl_pop2(buffer_list_t *bl, void **data, int *len)
{
    if (bl)
    {
        if (bl->total > 0)
        {
            pthread_mutex_lock(&(bl->mutex));
            *len = bl->head->len;
            *data = bl->head->data;
            buffer_t *head_tmp = bl->head;
            bl->head = bl->head->next;
            buffer_destroy2(head_tmp);
            bl->total--;
            pthread_mutex_unlock(&(bl->mutex));
        }
        return bl->total;
    }
    return -1;
}

int bl_pop2_at(buffer_list_t *bl, int index, void **data, int *len)
{
    int i;
    buffer_t *prev_tmp;
    buffer_t *next_tmp;
    if (bl)
    {
        if (bl->total > 0 && index >= 0 && index < bl->total)
        {
            pthread_mutex_lock(&(bl->mutex));
            if (index == 0)
            {
                prev_tmp = bl->head;
                *len = prev_tmp->len;
                *data = prev_tmp->data;
                if (bl->total == 1)
                {
                    bl->head = NULL;
                    bl->tail = NULL;
                }
                else
                {
                    bl->head = prev_tmp->next;
                }
                buffer_destroy2(prev_tmp);
            }
            else
            {
                prev_tmp = bl->head;
                for (i = 0; i < index - 1; i++)
                    prev_tmp = prev_tmp->next;
                next_tmp = prev_tmp->next->next;
                *len = prev_tmp->next->len;
                memcpy(data, prev_tmp->next->data, prev_tmp->next->len);
                buffer_destroy2(prev_tmp->next);
                prev_tmp->next = next_tmp;
            }
            bl->total--;
            pthread_mutex_unlock(&(bl->mutex));
            return bl->total;
        }
    }
    return -1;
}

int bl_peek2(buffer_list_t *bl, void **data, int *len)
{
    if (bl)
    {
        pthread_mutex_lock(&(bl->mutex));
        if (bl->total > 0)
        {
            *len = bl->head->len;
            *data = bl->head->data;
        }
        pthread_mutex_unlock(&(bl->mutex));
        return bl->total;
    }
    return -1;
}

int bl_peek2_at(buffer_list_t *bl, int index, void **data, int *len)
{
    int i;
    buffer_t *peek_tmp;
    if (bl)
    {
        if (bl->total > 0 && index >= 0 && index < bl->total)
        {
            pthread_mutex_lock(&(bl->mutex));
            peek_tmp = bl->head;
            for (i = 0; i < index; i++)
                peek_tmp = peek_tmp->next;
            *len = peek_tmp->len;
            *data = peek_tmp->data;
            pthread_mutex_unlock(&(bl->mutex));
            return bl->total;
        }
    }
    return -1;
}

int bl_clear(buffer_list_t *bl)
{
    if (bl)
    {
        pthread_mutex_lock(&(bl->mutex));
        buffer_t *head_tmp = bl->head;
        while (head_tmp != NULL)
        {
            head_tmp = bl->head->next;
            buffer_destroy(bl->head);
            bl->head = head_tmp;
        }
        bl->total = 0;
        bl->head = NULL;
        bl->tail = NULL;

        pthread_mutex_unlock(&(bl->mutex));
        return 0;
    }
    return -1;
}

int bl_total(buffer_list_t *bl)
{
    if (bl)
        return bl->total;
    return -1;
}

int bl_dump(buffer_list_t *bl)
{
    int index = 0;
    printf("\nbuffer list dump, total[%d] head[%p] tail[%p]\n", bl->total, bl->head, bl->tail);
    buffer_t *head_tmp = bl->head;
    while (head_tmp != NULL)
    {
        printf("buffer[%d] this[%p] next[%p] str[%d] = %s\n", index++, head_tmp, head_tmp->next, head_tmp->len, (char *)head_tmp->data);
        head_tmp = head_tmp->next;
    }
    printf("\n");
    return 0;
}