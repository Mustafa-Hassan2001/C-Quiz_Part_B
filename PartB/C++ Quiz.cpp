#include <iostream>
#include <iomanip>
#include <sstream>
#include <cstdlib>
#include <iterator>
#include <algorithm>
#include <exception>
#include <stdexcept>
#include <new>

using namespace std;
//-----------------------------------------------------------------------------
template<class T>
class arrayclass
{
public:
	typedef const T* const_iterator;
	arrayclass(int size = 0);
	////// copy constructor declaration goes here //////////////////(5 points)


	bool full() const { return m_size >= m_capacity; }
	bool empty() const { return m_size == 0; }
	int get_capacity() const { return m_capacity; }
	int get_size() const { return m_size; }
	const_iterator begin() { return m_array; }
	const_iterator end() { return m_array + m_size; }
	T at(int index) const {
		if (index >= m_size || index < 0)
			throw out_of_range("index out of range");
		return m_array[index];
	}
	~arrayclass() { if (m_array != nullptr) delete[] m_array; }
protected:
	T* m_array;		// dynamic array
	int m_size;		// number of elements used
private:
	int m_capacity; // number of elements allocated
};


//-----------------------------------------------------------------------------
template<class T> arrayclass<T>::arrayclass(int size)
	:m_capacity(size), m_size(0), m_array(nullptr)
{
	if (size < 0)
	{
		ostringstream oss;
		oss << "cannot create an arrayclass of capacity " << size;
		throw domain_error(oss.str().c_str());
	}
	if (size > 0)
		m_array = new T[size];
}

//-----------------------------------------------------------------------------
////// copy constructor definition goes below //////////////////////(10 points)













//-----------------------------------------------------------------------------
template<class T>
class arrayStack : public arrayclass<T>
{
public:
	arrayStack(int size = 0) : arrayclass(size) { }
	arrayStack(const arrayStack& other) : arrayclass(other) { }
	void push(T item) {
		if (full()) throw domain_error("array is full");
		m_array[m_size++] = item;
	}
	////////finish writing the definition for pop() below //////////// (5 points)	
	T pop() {

	};

}; // 

	//-----------------------------------------------------------------------------
	int main(void) ////////////// (60 points)
	{
		arrayStack<long> **st = nullptr;
		arrayStack<long> singleStack(5);
		long element = 3L;   // element to put in arrayclass
		int numElements = 2; // number of elements in st
		int exitCode = EXIT_SUCCESS;
		try
		{


		}

		
	}