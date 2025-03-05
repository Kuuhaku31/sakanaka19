
// test_list.cpp

#include "list.h"

#include <iostream>

int
main()
{
    std::cout << "Hello, test_list!" << std::endl;

    float thetas[8] = { 1, 2, 3, 4, 5, 6, 7, 8 };
    int   is_fs[8]  = { 0, 0, 1, 1, 1, 1, 0, 0 };

    int first      = -1;
    int next_is_fs = -1;
    for(int i = 7; i >= 0; i--)
    {
        if(is_fs[i])
        {
            if(next_is_fs == -1)
            {
                next_is_fs = first = i;
                continue;
            }

            is_fs[i]     = next_is_fs;
            next_is_fs   = i;
            is_fs[first] = i;
        }
    }

    for(int i = 0; i < 8; i++)
    {
        std::cout << thetas[i] << " " << is_fs[i] << std::endl;
    }

    return 0;
}
