
#include "queue.h"


void queue::ensure_capacity (size_t c)
{
   if ( current_capacity < c )
   {
      // New capacity will be the greater of c and
      // 2 * current_capacity. 

      if (c < 2 * current_capacity)
         c = 2 * current_capacity;

      if (c < 8) 
         c = 8;
 
      double* newdata = new double[c];
      for (size_t s = 0; s < current_size; ++s)
      {
         newdata[s] = data[begin];
         begin = next(begin);
      }

      current_capacity = c;
      begin = 0;
      end = current_size;

      delete[] data;
      data = newdata;
   }
}


void queue::printfields (std::ostream& out) const
{
   out << "   current_size =     " << current_size << "\n";
   out << "   current_capacity = " << current_capacity << "\n";
   out << "   begin =            " << begin << "\n";
   out << "   end =              " << end << "\n";
}

void queue::checkinvariant () const 
{

   if (current_capacity == 0)
   {
      std::cout << "current capacity == 0\n";
      printfields(std::cout);
      std::abort();
   }

   if (begin >= current_capacity)
   {
      std::cout << "begin >= current_capacity\n";
      printfields(std::cout);
      std::abort();
   }

   if (end >= current_capacity)
   {
      std::cout << "end >= current_capacity\n";
      printfields(std::cout); 
      std::abort();
   }

   if (current_size > current_capacity)
   {
      std::cout << "current_size > current_capacity\n";
      printfields(std::cout); 
      std::abort();
   }

   if((begin + current_size) % current_capacity != end)
   {
      std::cout <<
         "distance between begin and end does not fit to current_size\n";
      printfields(std::cout);
      std::abort();
   }
}
 


// It's a present for you:

std::ostream& operator << (std::ostream& out, const queue& q)
{
   out << "[";
   size_t i = q.begin; 
   for (size_t s = 0; s < q.size(); ++ s)
   {
      if (s) out << ", ";
      else out << " ";
      out << q.data[i];

      i = q.next(i);
   }
   out << " ]";
   return out;
}

/* Default constructor */
queue::queue ()
   : current_size(0)
   , current_capacity(1)
   , begin(0)
   , end(0)
   , data(new double[current_capacity])
{ }

/* Copy constructor */
queue::queue (const queue& q)
   : current_size(q.current_size)
   , current_capacity(q.current_capacity)
   , begin(q.begin)
   , end(q.end)
   , data(new double[current_capacity])
{
   for (size_t i = begin; i != end; ++i)
      data[i] = q.data[i];
}

/* Destructor */
queue::~queue ()
{
   delete[] data;
}

/* Assignment operator */
const queue& queue::operator = (const queue& q)
{
   if (current_size != q.current_size)
   {
      delete[] data;
      current_size = q.current_size;
      data = new double[current_size];
      ensure_capacity(current_size);
      begin = q.begin;
      end = q.end;
   }
   for (size_t i = begin; i != end; ++i)
      data[i] = q.data[i];
   return q;
}

/* Initializer */
queue::queue (std::initializer_list<double> init)
   : queue()
{
   for (double n : init)
      push(n);
}

/* Push to the queue */
void queue::push (double d)
{
   if (current_size + 1 == current_capacity)
      ensure_capacity(current_size + 2);
   data[end] = d; //*(data + end) = d;
   current_size += 1;
   end = next(end);
}

/* Remove the first element of the queue */
void queue::pop ()
{
   if (empty())
   {
      throw std::runtime_error("pop: queue is empty");
   }
   else
   {
      begin = next(begin);
      current_size -= 1;
   }
}

/* Empty the queue */
void queue::clear ()
{
   current_size = 0;
}

/* The first element of the queue */
double queue::peek () const
{
   if (empty())
      throw std::runtime_error("peek: queue is empty");
   else
      return data[begin];
}
