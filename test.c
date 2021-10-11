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

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "src/svwm.h"

struct Letter
{
    int number;
    char character;
};

int main()
{
    int units = 10000;
    int loops = 1000;
    int inserts = 0;
    int erases = 0;
    int errors = 0;
    clock_t t;

    struct Letter *test_arr = (struct Letter *)calloc(units, sizeof(struct Letter));

    struct Letter **test_vec = (struct Letter **)svwm_vector(0, sizeof(struct Letter *));
    printf("At the start: size:%d, max_size:%d, capacity:%d, errors:%d\n", svwm_size(test_vec), svwm_maxsize(test_vec), svwm_capacity(test_vec), errors);

    t = clock();
    for (int loop = 0; loop < loops; loop++)
    {
        for (int i = 0; i < units; i++)
        {
            struct Letter *tmp = test_arr + i;
            tmp->number = i + 1;
            tmp->character = (char)'A' + i % 10 + loop % 10;
            test_vec = (struct Letter **)svwm_pushback(test_vec, &tmp);
            inserts++;
        }
        for (int i = units - 1; i > -1; i--)
        {
            if (test_vec[i]->number != i + 1 || test_vec[i]->character != (char)'A' + i % 10 + loop % 10)
                ++errors;
            svwm_popback(test_vec);
            ++erases;
        }
    }
    t = clock() - t;

    free(test_arr);
    printf("At the end: size:%d, max_size:%d, capacity:%d, errors:%d\n", svwm_size(test_vec), svwm_maxsize(test_vec), svwm_capacity(test_vec), errors);
    printf("inserts:%d, erases:%d = %d operations.\n", inserts, erases, inserts + erases);

    svwm_free(test_vec);

    printf("It took me %d clicks (%f seconds).\n", (int)t, ((double)t) / CLOCKS_PER_SEC);
    return 0;
}