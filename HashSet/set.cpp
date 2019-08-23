
#include "set.h"

bool equal(const std::string& s1, const std::string& s2)
{
   if (s1.size() == s2.size())
   {
      for (size_t i = 0; i < s1.size(); ++i)
      {
         if (std::tolower(s1[i]) != std::tolower(s2[i]))
            return false;
      }
      return true;
   }

   return false;
}

size_t hash(const std::string& st)
{
   size_t hash = 0;
   size_t pow = 1;
   
   for (size_t i = 0; i < st.size(); ++i)
   {
      hash += (std::tolower(st[i]) - 'a' + 1) * pow;
      pow *= 31;
   }
   
   return hash;
}

bool set::contains(const std::string& s) const
{
   for (size_t i = 0; i < buckets.size(); ++i)
   {
      for (auto& el : buckets[i])
      {
         if (equal(el, s))
            return true;
      }
   }

   return false;
}

bool set::simp_insert(const std::string& s)
{
   size_t index = 0;

   if (!contains(s))
   {
      index = hash(s) % buckets.size();
      buckets[index].push_back(s);
      set_size += 1;
      return true;
   }

   return false;
}


bool set::insert(const std::string& s)
{
   if (simp_insert(s))
   {
      if (loadfactor() == max_load_factor)
      {
         rehash(buckets.size() * 2);
      }
      return true;
   }

   return false;
}


void set::rehash(size_t newbucketsize)
{
   if (newbucketsize < 4)
   {
      newbucketsize = 4;
   }
   std::vector< std::list< std::string >> newbuckets =
      std::vector< std::list< std::string >> (newbucketsize);

   for (size_t i = 0; i < buckets.size(); ++i)
   {
      newbuckets[i] = buckets[i];
   }
   buckets = newbuckets;
}


bool set::remove(const std::string& s)
{
   size_t index = 0;

   if (contains(s))
   {
      index = hash(s) % buckets.size();
      buckets[index].remove(s);
      set_size -= 1;
      return true;
   }

   return false;
}


void set::clear()
{
   for (size_t i = 0; i < buckets.size(); ++i)
   {
      buckets[i].clear();
   }
}


std::ostream& set::print(std::ostream& out) const
{  
   for (size_t i = 0; i < buckets.size(); ++i)
   {
      out << "bucket[" << i << "]:\t{";
      for (auto el = buckets[i].begin(); el != buckets[i].end(); ++el)
      {
         if (el != buckets[i].begin())
            out << ",";
         out << " " << *el;
      }
      out << " }\n";
   }

   return out;
}



std::ostream& set::printstatistics(std::ostream& out) const
{
   std::cout << "set size =            " << size( ) << "\n";
   std::cout << "load factor =         " << loadfactor( ) << " ( max = " << max_load_factor << " )\n";
   std::cout << "standard deviation =  " << standarddev( ) << "\n";
   return out;
}


