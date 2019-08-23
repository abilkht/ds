
#ifndef QUEUE_INCLUDED 
#define QUEUE_INCLUDED  1

#include <iostream>
#include <initializer_list>

struct queue
{
   size_t current_size; 
   size_t current_capacity; 
   size_t begin;
   size_t end;   

   double* data; 
      // INVARIANТ: I wrote a function checkinvariant( ) const 
      // which checks the invariant as much as possible. Use this
      // function in your tests. 

   void ensure_capacity (size_t c);
      // Ensure that queue has capacity of at least c.
      // This function is given, so you don't have to write it. 

   // Return i+1, but 0 if we reach current_capacity.
 
   size_t next (size_t i) const 
   {
      i = i + 1; 
      if (i == current_capacity)
         i = 0; 
      return i;
   }

   void checkinvariant () const;
      // Call this function often during your tests. We will
      // call it during checking!

   void printfields (std::ostream&) const;
      // Print the fields current_size, current_capacity,
      // begin, end. It should be used for debugging. 

public: 
   queue ();               
      // Constructs empty queue. 

   queue (const queue& q);

   ~queue ();

   const queue& operator = (const queue& q);

   queue (std::initializer_list<double> init);
      // So that you can write q = { 1,2,3 };
      // You can use init. size( ) to see the size, and
      // for( double d : init ) to go through all
      // elements in the initializer_list.

   void push (double d);  

   void pop ();

   void clear ();

   double peek () const;

   size_t size () const { return current_size; } 

   bool empty () const { return current_size == 0; } 
   
   friend std::ostream& operator << (std::ostream& , const queue&); 
}; 

std::ostream& operator << (std::ostream& , const queue&);

#endif


