#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>

using namespace std;
struct Letter
{
    int number;
    char character;
};

int main()
{
    int units = 1000000;
    int loops = 10;
    int inserts = 0;
    int erases = 0;
    int errors = 0;
    clock_t t;

    struct Letter *test_arr = (struct Letter *)calloc(units, sizeof(struct Letter));

    vector<Letter *> test_vec;
    printf("At the start: size:%d, max_size:%d, capacity:%d, errors:%d\n", test_vec.size(), test_vec.max_size(), test_vec.capacity(), errors);

    t = clock();
    for (int loop = 0; loop < loops; loop++)
    {
        for (int i = 0; i < units; i++)
        {
            struct Letter *tmp = test_arr + i;
            tmp->number = i + 1;
            tmp->character = (char)'A' + i % 10 + loop % 10;
            test_vec.push_back(tmp);
            inserts++;
        }
        for (int i = units - 1; i > -1; i--)
        {
            if (test_vec[i]->number != i + 1 || test_vec[i]->character != (char)'A' + i % 10 + loop % 10)
                ++errors;
            test_vec.pop_back();
            ++erases;
        }
    }
    t = clock() - t;

    free(test_arr);
    printf("At the end: size:%d, max_size:%d, capacity:%d, errors:%d\n", test_vec.size(), test_vec.max_size(), test_vec.capacity(), errors);
    printf("inserts:%d, erases:%d = %d operations.\n", inserts, erases, inserts + erases);


    printf("It took me %d clicks (%f seconds).\n", (int)t, ((double)t) / CLOCKS_PER_SEC);
    return 0;
}