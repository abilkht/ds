#include "stack.h"

// Use this method for all your reallocations:

void stack::ensure_capacity (size_t c)
{
    if (current_capacity < c)
    {
        // New capacity will be the greater of c and
        // 2 * current_capacity.
        
        if (c < 2 * current_capacity)
            c = 2 * current_capacity;
        
        double* newdata = new double[ c ];
        for (size_t i = 0; i != current_size; ++ i)
            newdata[i] = data[i];
        
        current_capacity = c;
        delete[] data;
        data = newdata;
    }
}

/* Default Constructor */
stack::stack ()
    : current_size(0)
    , current_capacity(0)
    , data(new double[current_size])
{ }

/* Copy Constructor */
stack::stack (const stack& s)
    : current_size(s.current_size)
    , current_capacity(s.current_capacity)
    , data(new double[current_size])
{
    for (size_t i = 0; i != current_size; ++i)
        data[i] = s.data[i];
}

/* Destructor */
stack::~stack ()
{
    delete[] data;
}

/* Assignment operator */
const stack& stack::operator = (const stack& s)
{
    if (current_size != s.current_size)
    {
        delete[] data;
        current_size = s.current_size;
        data = new double[current_size];
        ensure_capacity(current_size);
    }
    
    for (size_t i = 0; i != s.current_size; ++i)
        data[i] = s.data[i];
    return s;
}

/* Initializer */
stack::stack (std::initializer_list<double> d)
{
    current_size = d.size();
    current_capacity = d.size();
    data = new double[current_size];
    size_t element = 0;
    
    for (double num : d)
    {
        data[element] = num;
        ++element;
    }
}

/* Push to the stack */
void stack::push (double d)
{
    if (current_size == current_capacity)
        ensure_capacity(current_size + 1);
    data[current_size] = d;
    current_size += 1;
}

/* Remove the last element of the stack */
void stack::pop ()
{
    if (!current_size)
        throw std::runtime_error("pop: stack is empty");
    else
        current_size -= 1;
}

/* Empty the stack */
void stack::clear ()
{
    current_size = 0;
}

/* Remove last elements until it has size s */
void stack::reset (size_t s)
{
    while (s < current_size)
    {
        current_size -= 1;
    }
}

/* Top of the stack */
double stack::peek () const
{
    if (!current_size)
        throw std::runtime_error("peek: stack is empty");
    else
        return data[current_size - 1];
}

/* Size of the stack */
size_t stack::size () const
{
    return current_size;
}

/* Whether the stack is empty or not */
bool stack::empty () const
{
    return !current_size;
}

/* Display the stack */
std::ostream& operator << (std::ostream& out, const stack& s)
{
    out << "[ ";
    for (size_t i = 0; i != s.current_size; ++i)
    {
        if (i != 0)
            out << ", ";
        
        out << s.data[i];
    }
    out << " ]";
    return out;
}

/* Testing the stack */
void teststack ()
{
    stack s1 = {1, 2, 3, 4, 5};
    stack s2 = s1; //CC
    
    for (unsigned int j = 0; j < 30; ++ j)
        s2.push(j * j);
    
    s1 = s2; // Assignment.
    s2.push(8);
    s1 = s1; // Self assignment.
    s1 = { 100,101,102,103 };
    // Works because the compiler inserts constructor and
    // calls assignment with the result.
    std::cout << "S1: " << s1 << "\n";
    std::cout << "S2: " << s2 << "\n";
    std::cout << "Size of s2: "<< s2.size() << std::endl;
    std::cout << "Is empty s2: "<< s2.empty() << std::endl;
}