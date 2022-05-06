#include "BaseVector.h"

BaseVector::BaseVector()
{
	elem_count = 0;
}

BaseVector::BaseVector(const int size)
{
	elem_count = size;
}

BaseVector::~BaseVector()
{
	elem_count = 0;
}

int BaseVector::size() const
{
	return elem_count;
}

bool BaseVector::is_empty() const 
{
	return !elem_count;
}
