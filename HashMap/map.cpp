
#include "map.h"

// From previous task:
bool equal(const std::string& s1, const std::string& s2)
{
   if (s1.size() == s2.size())
   {
      for (size_t i = 0; i < s1.size(); ++i)
      {
         if (tolower(s1[i]) != tolower(s2[i]))
            return false;
      }
      return true;
   }

   return false;
}

// Hash function
size_t hash(const std::string& s)
{
   size_t h = 0;
   
   for (char c : s)
   {
      h = h * 349 + tolower(c);
   }

   return h;
}

// Finding element by key in const list of pairs
map::listofpairs::const_iterator 
map::find(const listofpairs& lst, const std::string& key)
{
   auto p = lst.begin();
   while (p != lst.end() && !equal(p->first, key))
      ++p;
   return p;
}

// Finding element by key in list of pairs
map::listofpairs::iterator
map::find(listofpairs& lst, const std::string& key)
{
   auto p = lst.begin();
   while (p != lst.end() && !equal(p->first, key))
      ++p;
   return p;
}


#if 1
// Searching element by key in map
bool map::contains_key(const std::string& key) const
{
   auto ls = getbucket(key);
   return find(ls, key) != ls.end();
}

// Element insertion into map
bool map::insert(const std::string& key, unsigned int val)
{
   if (!contains_key(key))
   {
      getbucket(key).push_back({key, val});
      map_size += 1;
      check_rehash();
      return true;
   }

   return false;
}

// Element access and/or modification and/or creation in map
unsigned int& map::operator[] (const std::string& key)
{
   unsigned int val = 0;
   listofpairs::iterator el;

   if (insert(key, val) || !insert(key, val))
      el = find(getbucket(key), key);
   
   return el->second;
}

// Element access and/or modification in map
unsigned int& map::at(const std::string& key)
{
   auto& ls = getbucket(key);
   auto el = find(ls, key);

   if (el == ls.end())
      throw std::out_of_range("at(): string not found");

   return el->second;
}

// Element access in map
unsigned int map::at(const std::string& key) const
{
   auto ls = getbucket(key);
   auto el = find(ls, key);

   if (el == ls.end())
      throw std::out_of_range("at(): string not found");

   return el->second;
}

// Rehashing function
void map::rehash(size_t newbucketsize)
{
   size_t index = 0;

   if (newbucketsize < 4)
      newbucketsize = 4;
   
   std::vector<listofpairs> newbuckets{newbucketsize};

   for (auto& i : buckets)
   {
      for (auto& el : i)
      {
         index = hash(el.first) % newbucketsize;
         newbuckets[index].push_back(el);
      }
   }
   buckets = newbuckets;
}

// Checking for necessity of rehash
void map::check_rehash()
{
   if (loadfactor() > max_load_factor)
      rehash(buckets.size() * 2);
}

// Element removal from map
bool map::remove(const std::string& key)
{
   auto& ls = getbucket(key);
   auto el = find(ls, key);

   if (el != ls.end())
   {
      ls.remove(*el);
      map_size -= 1;
      return true;
   }

   return false;
}
#endif

// Stdev calculation
double map::standarddev() const  
{
   double sum = 0.0;
   double lf = loadfactor();

   for (const auto& l : buckets)
   {
      double dif = l.size() - lf;
      sum += dif * dif;
   }

   return sqrt(sum / buckets. size());
}

// Clearing map content
void map::clear() 
{
   for (auto& l : buckets)
      l.clear();

   map_size = 0; 
}


#if 1
// Printing content of map
std::ostream& map::print( std::ostream& out ) const
{
   for (size_t i = 0; i < buckets.size(); ++i)
   {
      out << "bucket[" << i << "]:\t{";
      for (auto el = buckets[i].begin(); el != buckets[i].end(); ++el)
      {
         if (el != buckets[i].begin())
            out << ",";
         out << " " << el->first << "/" << el->second;
      }
      out << " }\n";
   }

   return out;
}
#endif

// Printing statistics
std::ostream& map::printstatistics(std::ostream& out) const
{
   out << "set size =            " << size( ) << "\n";
   out << "load factor =         " << loadfactor( ) << " ( max = " << 
                                      max_load_factor << " )\n";
   out << "standard deviation =  " << standarddev( ) << "\n";
   return out;
}


