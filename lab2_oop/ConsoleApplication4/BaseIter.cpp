#include "BaseIter.h"

BaseIter::BaseIter()
{
	index = 0;
	elem_count = 0;
}

BaseIter::BaseIter(const BaseIter& iter)
{
    index = iter.index;
	elem_count = iter.elem_count;
}

BaseIter::~BaseIter()
{
	index = 0;
	elem_count = 0;
}