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
        arrayclass(const arrayclass& other);

        bool full() const
        {
            return m_size >= m_capacity;
        }
        bool empty() const
        {
            return m_size == 0;
        }
        int get_capacity() const
        {
            return m_capacity;
        }
        int get_size() const
        {
            return m_size;
        }
        const_iterator begin()
        {
            return m_array;
        }
        const_iterator end()
        {
            return m_array + m_size;
        }
        T at(int index) const
        {
            if (index >= m_size || index < 0)
                throw out_of_range("index out of range");
            return m_array[index];
        }
        ~arrayclass()
        {
            if (m_array != nullptr)
                delete[] m_array;
        }
    protected:
        T* m_array;		// dynamic array
        int m_size;		// number of elements used
    private:
        int m_capacity; // number of elements allocated
};

//-----------------------------------------------------------------------------
template<class T> arrayclass<T>::arrayclass(int size) :
        m_capacity(size), m_size(0), m_array(nullptr)
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
template<class T> arrayclass<T>::arrayclass(const arrayclass& other)
{
    m_array = nullptr;
    m_size = other.m_size;
    m_capacity = other.m_capacity;
    if (m_size > 0)
        m_array = new T[m_size];
    for (int i = 0; i < m_size; ++i)
    {
        m_array[i] = other.m_array[i];
    }
}

//-----------------------------------------------------------------------------
template<class T>
class arrayStack: public arrayclass<T>
{
    public:
        arrayStack(int size = 0) :
                arrayclass<T>(size)
        {
        }
        arrayStack(const arrayStack& other) :
                arrayclass<T>(other)
        {
        }
        void push(T item)
        {
            if (this->full())
                throw domain_error("array is full");
            this->m_array[this->m_size++] = item;
        }
        ////////finish writing the definition for pop() below //////////// (5 points)
        T pop()
        {
            if (this->m_size <= 0)
            {
                ostringstream oss;
                oss << "cannot pop an arrayStack empty.";
                throw domain_error(oss.str().c_str());
            }
            return this->m_array[--this->m_size];
        }

};
//

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
        // The program dynamically allocates memory for st to be an array of two elements
        st = new arrayStack<long>*[numElements];
        // the first of which points to a dynamically allocated arrayStack with a capacity of 3
        st[0] = new arrayStack<long>(3);
        // the second of which points to a dynamically allocated arrayStack with a capacity of 2
        st[1] = new arrayStack<long>(2);
        // The program uses a loop to fill the arrayStack at st[0] with 3, 4, and 5
        for (int i = 0; i < 3; ++i)
        {
            st[0]->push(element++);
        }
        // and the arrayStack at st[1] with 6 and 7
        for (int i = 0; i < 2; ++i)
        {
            st[1]->push(element++);
        }

        // The program uses a for loop to go through both elements of the array
        for (int i = 0; i < numElements; ++i)
        {
            // Using an inner for loop, the program should use a const_iterator to print each element of the arrayStack to cout
            for (arrayclass<long>::const_iterator it = st[i]->begin(); it != st[i]->end(); ++it)
            {
                cout << *it << " ";
            }
            cout << endl;
            // Using an inner while loop, pop each element of each arrayStack, add “one” to it, and push it on to SingleStack.
            while (!st[i]->empty())
            {
                singleStack.push(st[i]->pop() + 1);
            }
            //Using an inner while loop, pop each element of SingleStack and push it back on to the original arrayStack
            while (!singleStack.empty())
            {
                st[i]->push(singleStack.pop());
            }
            // Use the copy function (from <algorithm>) to print each element of the arrayStack to the console (cout) with ‘|’ as a delimiter
            arrayStack<long> copyArray(*st[i]);
            for (int index = 0; index < copyArray.get_size(); ++index)
            {
                cout << copyArray.at(index) << "|";
            }
            cout << endl;
        }
        //The program cleans up all allocated memory
        for (int i = 0; i < numElements; ++i)
        {
            if(st[i] != nullptr)
                delete st[i];
        }
        if(st != nullptr)
            delete[] st;
    } catch (exception& e)
    {
        cerr << "Caught: " << e.what() << endl;
        exitCode = EXIT_FAILURE;
    }
    return exitCode;
}
