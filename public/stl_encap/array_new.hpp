#include <stdexcept>
template <class T, size_t ST_SIZE>
class MyArrayBase
{
private:
    T m_arrData[ST_SIZE];

public:
    MyArrayBase():
        m_arrData{}
    {}
    MyArrayBase(T const &data):
        MyArrayBase()
    {
        for(auto &val : m_arrData)
        {
            val = data;
        }
    }
    virtual ~MyArrayBase() = default;
    MyArrayBase(MyArrayBase const &other)
    {
        for(size_t i{0}; i < ST_SIZE; i++)
        {
            this->m_arrData[i] = other.m_arrData[i];
        }
    }

    T &operator[](int const &i)
    {
        return this->m_arrData[GetIndex(i)];
    }

    T const &operator[](int const &i) const
    {
        return this->m_arrData[GetIndex(i)];
    }

protected:
    virtual size_t GetIndex(int const &i) const
    {
        int index = 0;
        if(i < 0)
        {
            index = ST_SIZE + i;
        }
        else
        {
            index = i;
        }
        if(index < 0 || index >= ST_SIZE)
        {
            throw std::out_of_range("艾斯你个衰仔！");
        }
        return index;
    }
};


template <class T>
class MyArrayBase<T, 0>
{};

/*
instead start with 0, this array start with 1
such as port1, port2... slot1, slot2
many array stand for entity usually with begin index 1 rather than 0
*/
template <class T, size_t ST_SIZE>
class CEntityArray: public MyArrayBase<T, ST_SIZE>
{
public:
    CEntityArray():
        MyArrayBase<T, ST_SIZE>()
    {}
    CEntityArray(T const &val):
        MyArrayBase<T, ST_SIZE>(val)
    {}

protected:
    virtual size_t GetIndex(int const &i)  const
    {
        int index = 0;
        if(i < 0)
        {
            index = ST_SIZE + i;
        }
        else
        {
            index = i - 1;
        }
        if(index < 0 || index >= ST_SIZE)
        {
            throw std::out_of_range("艾斯你个衰仔！");
        }
        return index;
    }
};

/*
a array with a const length
using Push to "add" a new data and "pop" the oldest(head) data
by using a cursor to show current head pos
every Push action actually wirte new data at head pos and move cursor to next pos(return to 0 if at end)
*/
template <class T, size_t ST_SIZE>
class CCycleArray : public MyArrayBase<T, ST_SIZE>
{
private:
    size_t m_stCursor;

public:
    CCycleArray():
        MyArrayBase<T, ST_SIZE>(),
        m_stCursor{0}
    {}
    CCycleArray(T const &val):
        MyArrayBase<T, ST_SIZE>(val),
        m_stCursor{0}
    {}
    void Push(T const &data)
    {
        (*this)[0] = data;
        m_stCursor = ((m_stCursor + 1) % ST_SIZE);
    }

protected:
    virtual size_t GetIndex(int const &i)  const
    {
        int index = 0;
        if(i < 0)
        {
            index = ST_SIZE + i;
        }
        else
        {
            index = i;
        }
        if(index < 0 || index >= ST_SIZE)
        {
            throw std::out_of_range("艾斯你个衰仔！");
        }
        index = ((index + m_stCursor) % ST_SIZE);
        return index;
    }
};