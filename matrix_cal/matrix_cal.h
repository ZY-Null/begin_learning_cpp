#pragma once
#include "../public/public_head.h"
namespace NSMatrix
{
    template <class T>
    bool GetMatrixSize(const std::vector<std::vector<T>> &matrix, ENC<UINT>::R x, ENC<UINT>::R y)
    {
        x = 0;
        y = 0;
        auto _x = matrix.size();
        if (0 == _x)
        {
            return false;
        }
        auto _y = matrix[0].size();
        bool ret = true;
        for (auto i = 1; i < x; i++)
        {
            auto cur_size = matrix[i].size();
            if (_y != cur_size)
            {
                ret = false;
            }
            _y = _y < cur_size ? cur_size : _y;
        }
        x = _x;
        y = _y;
        return ret;
    }
    template <class T>
    bool GetMatrixSize(const std::vector<T> &matrix, ENC<UINT>::R x, ENC<UINT>::R y)
    {
        x = 0;
        y = 0;
        auto _x = matrix.size();
        if (0 == _x)
        {
            return false;
        }
        x = _x;
        y = 1;
        return true;
    }
    template <class T>
    void PrintMatrix(const std::vector<std::vector<T>> &matrix)
    {
        auto x = matrix.size();
        if (0 == x)
        {
            return;
        }
        auto y = matrix[0].size();
        for (auto i = 1; i < x; i++)
        {
            y = y < matrix[i].size() ? matrix[i].size() : y;
        }
        for (auto i = 0; i < x; i++)
        {
            for (auto j = 0; j < y; j++)
            {
                if (j >= matrix[i].size())
                {
                    continue;
                }
                std::cout << matrix[i][j] << " ";
            }
            std::cout << std::endl;
        }
        return;
    };

    template <class T>
    void PrintMatrix(const std::vector<T> &matrix)
    {
        auto x = matrix.size();
        if (0 == x)
        {
            return;
        }
        for (auto i = 0; i < x; i++)
        {
            std::cout << matrix[i] << " ";
        }
        std::cout << std::endl;
        return;
    };

    template <class T>
    std::vector<std::vector<T>> transposition(const std::vector<std::vector<T>> &src)
    {
        auto x = src.size();
        if (0 == x)
        {
            return typename std::vector<std::vector<T>>(0);
        }
        auto y = src[0].size();
        for (auto i = 1; i < x; i++)
        {
            y = y < src[i].size() ? src[i].size() : y;
        }
        typename std::vector<std::vector<T>> dst(y, std::vector<T>(x));
        for (auto i = 0; i < x; i++)
        {
            for (auto j = 0; j < y; j++)
            {
                if (j >= src[i].size())
                {
                    continue;
                }
                dst[j][i] = src[i][j];
            }
        }
        return std::move(dst);
    }

    template <class T>
    std::vector<std::vector<T>> transposition(const std::vector<T> &src)
    {
        auto x = src.size();
        if (0 == x)
        {
            return typename std::vector<std::vector<T>>(0);
        }
        typename std::vector<std::vector<T>> dst(x, std::vector<T>(1));
        for (auto i = 0; i < x; i++)
        {

            dst[i][0] = src[i];
        }
        return std::move(dst);
    }

    template <class T>
    std::vector<std::vector<T>> multiply(const std::vector<std::vector<T>> &left, const std::vector<std::vector<T>> &right)
    {
        UINT x1, x2, y1, y2;
        CHECK_COND_RET_VAL((!GetMatrixSize(left, x1, y1)), std::vector<std::vector<T>>(0));
        CHECK_COND_RET_VAL((!GetMatrixSize(right, x2, y2)), std::vector<std::vector<T>>(0));
        CHECK_COND_RET_VAL((y1 != x2), std::vector<std::vector<T>>(0));
        std::vector<std::vector<T>> res(x1, std::vector<T>(y2));
        for (auto i = 0; i < x1; i++)
        {
            for (auto j = 0; j < y2; j++)
            {
                for (auto k = 0; k < y1; k++)
                {
                    res[i][j] += (left[i][k] * right[k][j]);
                }
            }
        }
        return res;
    }
}