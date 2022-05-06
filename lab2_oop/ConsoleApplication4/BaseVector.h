#pragma once

class BaseVector
{
public:
	BaseVector();
	BaseVector(const int size);
	~BaseVector();

	int size() const;
	bool is_empty() const;

protected:
	int elem_count;

};

