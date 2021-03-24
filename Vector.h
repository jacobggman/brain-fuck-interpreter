#pragma once
#include <vector>
#include <list>
#include <tuple>

using size_type = typename int;

#define START_CAPACITY 2
#define UP_BY 2

template <class Type>
class Vector
{
private:
	std::list<std::vector<Type>*> values;
	size_type size = 0;
	size_type capacity = 0;

private:
	// return the vector and how much iter's it cost
	std::tuple<std::vector<Type>*, size_type> getVector(size_type index) {
		size_type maxIndex = START_CAPACITY;
		auto vector = values.begin();
		size_type i = 0;
		while (true)
		{
			if (maxIndex > index)
			{
				return std::make_tuple(*vector, i);
			}
			maxIndex = maxIndex * UP_BY;
			vector++;
			i++;
		}
	}

	Type& get(const size_type index) {
		auto selectedVector = getVector(index);
		// index % 2 + index // 2
		// 0 - > 0
		// 1 - > 1  // end of 1
		// 2 - > 0
		// 3 - > 1	// end of 2
		// 4 - > 0
		// 5 - > 1
		// 6 - > 2
		// 7 - > 3	// end of 3
		// 8 - > 0
		// 9 - > 1
		// 10 - > 2
		// 11 - > 3
		// 12 - > 4
		// 13 - > 5
		// 14 - > 6
		// 15 - > 7	// end of 4
		auto vector = std::get<0>(selectedVector);

		return (*vector)[index - myPow(2, std::get<1>)];
	}

	static int myPow(int x, unsigned int p)
	{
		if (p == 0) return 1;
		if (p == 1) return x;

		int tmp = myPow(x, p / 2);
		if (p % 2 == 0) return tmp * tmp;
		else return x * tmp * tmp;
	}

public:
	Vector() {
		reserve(START_CAPACITY);
	}
	Vector(const size_type size) {
		reserve(size);
	}
	~Vector() {
		for (auto& value : values)
		{
			delete value;
		}
	}

	void reserve(const size_type newCapacity) {
		while (newCapacity > this->capacity)
		{
			std::vector<Type>* selectedVector = new std::vector<Type>();
			size_type newAddSize = this->capacity == 0 ? START_CAPACITY : this->capacity * UP_BY - this->capacity;
			selectedVector->reserve(newAddSize);
			this->capacity += newAddSize;
			values.push_back(selectedVector);
		}
	}
	void push(const Type value) {
		reserve(this->size + 1);

		std::vector<Type>* selectedVector = std::get<0>(getVector(this->size));
		selectedVector->push_back(value);

		size++;
	}

	const Type& operator[](const size_type index) const {
		return get(index);
	}

	Type& operator[](const size_type index) {
		return get(index);
	}
};
