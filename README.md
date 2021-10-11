# <h1 align="center">SVWM - Simple Vector Without Macroses</h1>

<p align="center">
<img src="https://img.shields.io/badge/C-99-ff69b4">
<img src="https://img.shields.io/badge/License-MIT-brightgreen">
</p>


## Motivation

There are many C99 vector implementation, but all of them are complicated for understanding because of macroses.
I have sacrificed strong typing for simplicity. So, my implementation is pretty ~~useless~~ simple. 


## Test
[ [`test.c`](test.c) ]
```c
int main()
{
    int units = 10000;
    int loops = 1000;
    int inserts = 0;
    int erases = 0;
    int errors = 0;
    clock_t t;
    ...
    t = clock();
    ...
    t = clock() - t;
    ...
    printf("It took me %d clicks (%f seconds).\n", (int)t, ((double)t) / CLOCKS_PER_SEC);
    return 0;
}
```
<summary>Output</summary>

```
At the start: size:0, max_size:1, capacity:1, errors:0
At the end: size:0, max_size:16384, capacity:16384, errors:0
inserts:10000000, erases:10000000 = 20000000 operations.
It took me 324 clicks (0.314000 seconds).
```
<summary>The same test with std::vector</summary>

```
At the start: size:0, max_size:-1, capacity:0, errors:0
At the end: size:0, max_size:-1, capacity:1048576, errors:0
inserts:10000000, erases:10000000 = 20000000 operations.
It took me 227 clicks (0.227000 seconds).
```

## Build
>To build it you have to use CMake with gcc.<p>
You have to execute commands from __\$project folder\$/bin__ folder.



#### **Windows:**
```
cmake ../ && cmake --build ./ && start ./Debug/svwm_test.exe
```

#### **UNIX-like:**
```
cmake ../ && cmake --build ./ && ./svwm_test
```
