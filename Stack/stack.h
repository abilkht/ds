#ifndef STACK_INCLUDED
#define STACK_INCLUDED  1

#include <iostream>
#include <initializer_list>

class stack
{
    size_t current_size;
    size_t current_capacity;
    
    double* data;
    // INVARIANÐ¢: has been allocated with size current_capacity.
    // 0 <= current_size <= current_capacity.
    
    void ensure_capacity( size_t c );
    // Ensure that stack has capacity of at least c.
    // This function is given, so you don't have to write it.
    
public:
    stack( );
    // Constructs empty stack.
    
    stack( const stack& s );
    
    ~stack( );
    
    const stack& operator = ( const stack& s );
    
    stack( std::initializer_list<double> d );
    // So that you can write s = { 1,2,3 };
    // You need d. size( ) and for( double d : s ) ....
    
    void push( double d );
    
    void pop( );
    
    void clear( );
    
    void reset( size_t s );
    
    double peek( ) const;
    
    size_t size( ) const;
    
    bool empty( ) const;
    
    friend std::ostream& operator << ( std::ostream& , const stack& );
};

std::ostream& operator << ( std::ostream& , const stack& );

void teststack();

#endif


