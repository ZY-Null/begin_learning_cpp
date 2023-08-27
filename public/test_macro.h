#pragma once

#define EXPECT_EQ(a, b) \
    if (a != b)         \
        printf("\033[31mfunc %s, line:%d: test eq fail! (%s)!=(%s)!\033[0m]\n", __FUNCTION__, __LINE__, #a, #b);
#define EXPECT_NE(a, b) \
    if (a != b)         \
        printf("\033[31mfunc %s, line:%d: test ne fail! (%s)==(%s)!\033[0m]\n", __FUNCTION__, __LINE__, #a, #b);