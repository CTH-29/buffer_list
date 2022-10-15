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

void buffer_destroy(buffer_t *buf)
{
    if (buf)
    {
        free(buf->data);
        free(buf);
    }
}

void buffer_list_init(buffer_list_t *buflist)
{
    buflist->total = 0;
    buflist->head = NULL;
    buflist->tail = NULL;
    pthread_mutex_init(&(buflist->mutex), NULL);
}

int buffer_list_push(buffer_list_t *buflist, const void *data, int len)
{
    if (buflist)
    {
        pthread_mutex_lock(&(buflist->mutex));
        if (buflist->total == 0)
        {
            buflist->head = buffer_new(data, len);
            buflist->tail = buflist->head;
        }
        else
        {
            buflist->tail->next = buffer_new(data, len);
            buflist->tail = buflist->tail->next;
        }
        buflist->total++;
        pthread_mutex_unlock(&(buflist->mutex));
        return buflist->total;
    }
    return -1;
}

int buffer_list_push_at(buffer_list_t *buflist, int index, const void *data, int len)
{
    int i;
    buffer_t *prev_tmp;
    buffer_t *next_tmp;
    if (buflist)
    {
        if (index >= 0 && index <= buflist->total)
        {
            pthread_mutex_lock(&(buflist->mutex));
            prev_tmp = buflist->head;
            if (index == 0)
            {
                buflist->head = buffer_new(data, len);
                buflist->head->next = prev_tmp;
                if (buflist->tail == NULL)
                    buflist->tail = buflist->head;
            }
            else
            {
                if (index == buflist->total)
                {
                    buflist->tail->next = buffer_new(data, len);
                    buflist->tail = buflist->tail->next;
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
            buflist->total++;
            pthread_mutex_unlock(&(buflist->mutex));
            return buflist->total;
        }
    }
    return -1;
}

int buffer_list_pop(buffer_list_t *buflist, void *data, int *len)
{
    if (buflist)
    {
        if (buflist->total > 0)
        {
            pthread_mutex_lock(&(buflist->mutex));
            *len = buflist->head->len;
            memcpy(data, buflist->head->data, buflist->head->len);
            buffer_t *head_tmp = buflist->head;
            buflist->head = buflist->head->next;
            buffer_destroy(head_tmp);
            buflist->total--;
            pthread_mutex_unlock(&(buflist->mutex));
        }
        return buflist->total;
    }
    return -1;
}

int buffer_list_pop_at(buffer_list_t *buflist, int index, void *data, int *len)
{
    int i;
    buffer_t *prev_tmp;
    buffer_t *next_tmp;
    if (buflist)
    {
        if (buflist->total > 0 && index >= 0 && index < buflist->total)
        {
            pthread_mutex_lock(&(buflist->mutex));
            if (index == 0)
            {
                prev_tmp = buflist->head;
                *len = prev_tmp->len;
                memcpy(data, prev_tmp->data, prev_tmp->len);
                if (buflist->total == 1)
                {
                    buflist->head = NULL;
                    buflist->tail = NULL;
                }
                else
                {
                    buflist->head = prev_tmp->next;
                }
                buffer_destroy(prev_tmp);
            }
            else
            {
                prev_tmp = buflist->head;
                for (i = 0; i < index - 1; i++)
                    prev_tmp = prev_tmp->next;
                next_tmp = prev_tmp->next->next;
                *len = prev_tmp->next->len;
                memcpy(data, prev_tmp->next->data, prev_tmp->next->len);
                buffer_destroy(prev_tmp->next);
                prev_tmp->next = next_tmp;
            }
            buflist->total--;
            pthread_mutex_unlock(&(buflist->mutex));
            return buflist->total;
        }
    }
    return -1;
}

int buffer_list_peek(buffer_list_t *buflist, void *data, int *len)
{
    if (buflist)
    {
        pthread_mutex_lock(&(buflist->mutex));
        if (buflist->total > 0)
        {
            *len = buflist->head->len;
            memcpy(data, buflist->head->data, buflist->head->len);
        }
        pthread_mutex_unlock(&(buflist->mutex));
        return buflist->total;
    }
    return -1;
}

int buffer_list_peek_at(buffer_list_t *buflist, int index, void *data, int *len)
{
    int i;
    buffer_t *peek_tmp;
    if (buflist)
    {
        if (buflist->total > 0 && index >= 0 && index < buflist->total)
        {
            pthread_mutex_lock(&(buflist->mutex));
            peek_tmp = buflist->head;
            for (i = 0; i < index; i++)
                peek_tmp = peek_tmp->next;
            *len = peek_tmp->len;
            memcpy(data, peek_tmp->data, peek_tmp->len);
            pthread_mutex_unlock(&(buflist->mutex));
            return buflist->total;
        }
    }
    return -1;
}

int buffer_list_clear(buffer_list_t *buflist)
{
    if (buflist)
    {
        pthread_mutex_lock(&(buflist->mutex));
        buffer_t *head_tmp = buflist->head;
        while (head_tmp != NULL)
        {
            head_tmp = buflist->head->next;
            buffer_destroy(buflist->head);
            buflist->head = head_tmp;
        }
        buflist->total = 0;
        buflist->head = NULL;
        buflist->tail = NULL;

        pthread_mutex_unlock(&(buflist->mutex));
        return 0;
    }
    return -1;
}

int buffer_list_total(buffer_list_t *buflist)
{
    if (buflist)
        return buflist->total;
    return -1;
}

int buffer_list_dump(buffer_list_t *buflist)
{
    int index = 0;
    printf("\nbuffer_list total[%d] head[%p] tail[%p]\n", buflist->total, buflist->head, buflist->tail);
    buffer_t *head_tmp = buflist->head;
    while (head_tmp != NULL)
    {
        printf("buffer[%d] this[%p] next[%p] str[%d] = %s\n", index++, head_tmp, head_tmp->next, head_tmp->len, (char *)head_tmp->data);
        head_tmp = head_tmp->next;
    }
    printf("\n");
    return 0;
}