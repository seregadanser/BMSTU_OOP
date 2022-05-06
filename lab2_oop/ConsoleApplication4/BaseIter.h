#pragma once
class BaseIter
{
public:
    BaseIter();
    BaseIter(const BaseIter&);
    ~BaseIter();

protected:
    int index;
    int elem_count;
};

