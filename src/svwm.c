/*
MIT License
Copyright (c) 2021 Kaifolog
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

// The official repository: <https://github.com/Kaifolog/SVWM>.

/*
    SVWM - simple vector without macroses
*/

#include "svwm.h"
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <math.h>

struct svwm_head
{
    int size;
    int size_of_instance;
    int empty;
};

/* standart functions for vector class */

void *svwm_vector(int size, int size_of_instance)
{
    if (size_of_instance < 0)
        assert(0);

    void *tech_ptr;
    struct svwm_head *head_tech_ptr;
    if (size > 0)
    {
        tech_ptr = malloc(((size * SVWM_FACTOR) * size_of_instance) + sizeof(struct svwm_head));
        head_tech_ptr = (struct svwm_head *)tech_ptr;
        head_tech_ptr->size = size;
        head_tech_ptr->empty = size;
    }
    else
    {
        tech_ptr = malloc(((1) * size_of_instance) + sizeof(struct svwm_head));
        head_tech_ptr = (struct svwm_head *)tech_ptr;
        head_tech_ptr->size = 0;
        head_tech_ptr->empty = 1;
    }
    head_tech_ptr->size_of_instance = size_of_instance;
    return head_tech_ptr + 1;
}

int svwm_free(void *ptr)
{
    struct svwm_head *head_tech_ptr = (struct svwm_head *)ptr;
    free(head_tech_ptr - 1);
    return 1;
}

int svwm_bytesize(void *ptr)
{
    struct svwm_head *head_tech_ptr = (struct svwm_head *)ptr;
    head_tech_ptr--;
    return (head_tech_ptr->size * head_tech_ptr->size_of_instance);
}

int svwm_size(void *ptr)
{
    struct svwm_head *head_tech_ptr = (struct svwm_head *)ptr;
    head_tech_ptr--;
    return head_tech_ptr->size;
}

int svwm_maxsize(void *ptr)
{
    struct svwm_head *head_tech_ptr = (struct svwm_head *)ptr;
    head_tech_ptr--;
    return head_tech_ptr->size + head_tech_ptr->empty;
}

int svwm_capacity(void *ptr)
{
    struct svwm_head *head_tech_ptr = (struct svwm_head *)ptr;
    head_tech_ptr--;
    return head_tech_ptr->empty;
}

void *svwm_insert(void *ptr, int position, void *instance)
{
    struct svwm_head *head_tech_ptr = (struct svwm_head *)ptr;
    head_tech_ptr--;
    char *char_tech_ptr = (char *)ptr;

    if (head_tech_ptr->empty > 0)
    {
        char *buffer = (char *)malloc((head_tech_ptr->size - position) * head_tech_ptr->size_of_instance);
        memcpy(buffer, (char_tech_ptr + (position * head_tech_ptr->size_of_instance)), (head_tech_ptr->size - position) * head_tech_ptr->size_of_instance);
        memcpy((char_tech_ptr + (position * head_tech_ptr->size_of_instance)), (char *)instance, head_tech_ptr->size_of_instance);
        memcpy((char_tech_ptr + ((position + 1) * head_tech_ptr->size_of_instance)), buffer, (head_tech_ptr->size - position) * head_tech_ptr->size_of_instance);
        free(buffer);
        head_tech_ptr->size++;
        head_tech_ptr->empty--;
        return ptr;
    }
    else
    {
        void *new_ptr = malloc(((head_tech_ptr->size) * SVWM_FACTOR * head_tech_ptr->size_of_instance) + sizeof(struct svwm_head));
        memcpy(new_ptr, head_tech_ptr, ((head_tech_ptr->size) * head_tech_ptr->size_of_instance) + sizeof(struct svwm_head));
        struct svwm_head *new_head_tech_ptr = (struct svwm_head *)new_ptr;
        new_head_tech_ptr->empty = head_tech_ptr->size;
        free(head_tech_ptr);
        svwm_insert(new_head_tech_ptr + 1, position, instance);
    }
}

int svwm_erase(void *ptr, int position)
{
    char *char_tech_ptr = (char *)ptr;
    struct svwm_head *head_tech_ptr = (struct svwm_head *)ptr;
    head_tech_ptr--;
    char *buffer = (char *)malloc((head_tech_ptr->size - (1 + position)) * head_tech_ptr->size_of_instance);
    memcpy(buffer, (char_tech_ptr + ((position + 1) * head_tech_ptr->size_of_instance)), (head_tech_ptr->size - (1 + position)) * head_tech_ptr->size_of_instance);
    memcpy((char_tech_ptr + ((position)*head_tech_ptr->size_of_instance)), buffer, (head_tech_ptr->size - (1 + position)) * head_tech_ptr->size_of_instance);
    free(buffer);
    head_tech_ptr->empty++;
    head_tech_ptr->size--;
    return 1;
}

void *svwm_pushback(void *ptr, void *instance)
{
    struct svwm_head *head_tech_ptr = (struct svwm_head *)ptr;
    head_tech_ptr--;
    ptr = svwm_insert(ptr, head_tech_ptr->size, instance);
    return ptr;
}

void svwm_popback(void *ptr)
{
    struct svwm_head *head_tech_ptr = (struct svwm_head *)ptr;
    head_tech_ptr--;
    head_tech_ptr->size--;
    head_tech_ptr->empty++;
}

/* specified functions */

void *svwm_pb_char(void *ptr, char instance)
{
    return svwm_pushback(ptr, &instance);
}

void *svwm_pb_int(void *ptr, int instance)
{
    return svwm_pushback(ptr, &instance);
}

void *svwm_pb_float(void *ptr, float instance)
{
    return svwm_pushback(ptr, &instance);
}

void *svwm_pb_double(void *ptr, double instance)
{
    return svwm_pushback(ptr, &instance);
}