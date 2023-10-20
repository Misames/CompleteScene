#pragma once

template <typename V>
struct ReverseWrapper
{
    V &vec;
    ReverseWrapper(V &v) : vec(v) {}

    typename V::reverse_iterator begin() { return vec.rbegin(); }
    typename V::reverse_iterator end() { return vec.rend(); }
};

template <typename T>
ReverseWrapper<T> MakeReverse(T &v)
{
    return ReverseWrapper<T>(v);
}