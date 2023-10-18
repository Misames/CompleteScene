#pragma once

template <typename V>
struct ReverseWrapper
{
    V &vec;
    ReverseWrapper(V &v) : vec(v) {}

    typename V::ReverseIterator begin() { return vec.rbegin(); }
    typename V::ReverseIterator end() { return vec.rend(); }
};

template <typename T>
ReverseWrapper<T> MakeReverse(T &v)
{
    return ReverseWrapper<T>(v);
}