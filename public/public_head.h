#pragma once
#include <bits/stdc++.h>

using BYTE = unsigned char;
using WORD = unsigned short;
using UINT = unsigned int;
using UL = unsigned long;
using ULL = unsigned long long;

template <class T>
struct ENC
{
    using C = const T;
    using CR = const T &;
    using R = T &;
    using P = T *;
    using CP = T const *;
    using PCR = T *const &;
    using CPCR = T const *const &;
};

void RecordLog(const char *name, const char *content, ...) {}
#define CHECK_ERR_RET_VOID(con)                                                           \
    if (con)                                                                              \
    {                                                                                     \
        RecordLog(__FUNCTION__, "line %d execute (%s) return positive!", __LINE__, #con); \
        return;                                                                           \
    }
#define CHECK_ERR_RET_VAL(con, val)                                                       \
    if (con)                                                                              \
    {                                                                                     \
        RecordLog(__FUNCTION__, "line %d execute (%s) return positive!", __LINE__, #con); \
        return val;                                                                       \
    }
#define CHECK_COND_RET_VOID(con) \
    if (con)                     \
    {                            \
        return;                  \
    }
#define CHECK_COND_RET_VAL(con, val) \
    if (con)                         \
    {                                \
        return val;                  \
    }
#define CHECK_COND_CONTINUE(con) \
    if (con)                     \
    {                            \
        continue;                \
    }
#define CHECK_COND_BREAK(con) \
    if (con)                  \
    {                         \
        break;                \
    }