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

#ifndef SVWM_FACTOR
#define SVWM_FACTOR 2
#endif

/*
    SVWM_FACTOR have to be int.
*/

/* standart functions for vector class */

void *svwm_vector(int size, int size_of_instance);

int svwm_free(void *ptr);

int svwm_bytesize(void *ptr);

int svwm_size(void *ptr);

int svwm_maxsize(void *ptr);

int svwm_capacity(void *ptr);

void *svwm_insert(void *ptr, int position, void *instance);

int svwm_erase(void *ptr, int position);

void *svwm_pushback(void *ptr, void *instance);

void svwm_popback(void *ptr);

/* specified functions */

void *svwm_pb_char(void *ptr, char instance);

void *svwm_pb_int(void *ptr, int instance);

void *svwm_pb_float(void *ptr, float instance);

void *svwm_pb_double(void *ptr, double instance);
