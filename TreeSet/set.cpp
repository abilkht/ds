
#include "set.h"


void print(std::ostream& out, const treenode* n, size_t indent)
{

   for (size_t i = 0; i != indent; ++ i)
      out << "|  "; 
   if (n)
   {
      out << (n -> val) << "\n";
      print(out, n -> left, indent + 1);
      print(out, n -> right, indent + 1); 
   }
   else
      out << "#\n"; 
}


void checksorted( 
          treenode* n, 
          const std::string* lowerbound, 
          const std::string* upperbound)
{
   while (n) 
   {
      if (lowerbound && !before(*lowerbound, n -> val))
      {
         std::cout << "value " << (n -> val);
         std::cout << " is not above lower bound " << *lowerbound << "\n";
         std::abort( );
      }

      if (upperbound && !before(n -> val, *upperbound))
      {
         std::cout << "value " << (n -> val);
         std::cout << "is not below upperbound " << *upperbound << "\n";
         std::abort( );
      }

      checksorted(n -> left, lowerbound, &(n -> val));
      lowerbound = & (n -> val);
      n = n -> right;
   }
} 


// Used by copy constructor and assignment:

void writecopy(treenode** to, treenode* from)
{
   while (from)
   {
      *to = new treenode{from->val};

      writecopy(& (*to)->left, from->left);
      to = & (*to)->right;
      from = from->right;
   }
}

// Used by destructor:

void deallocate(treenode* n)
{
   while (n)
   {
      deallocate(n->left);
      treenode* bye = n;
      n = n->right;
      delete bye;
   }
}


// Used to compare performance
size_t log_base2 (size_t s)
{
   return s > 1 ? log_base2(s / 2) + 1 : 0;
}

// From previous task:

bool equal(const std::string& s1, const std::string& s2)
{
   if (s1.size() == s2.size())
   {
      for (size_t i = 0; i != s1.size(); ++i)
      {
         if (std::tolower(s1[i]) != std::tolower(s2[i]))
            return false;
      }
      return true;
   }

    return false;
}

// Must be written for task 5(part 2) :

bool before(const std::string& s1, const std::string& s2)
{
   for (size_t i = 0; i != s1.size() && i != s2.size(); ++i)
   {
      if (std::tolower(s1[i]) < std::tolower(s2[i]))
         return true;
      if (std::tolower(s1[i]) > std::tolower(s2[i]))
         return false;
   }
   if (s1.size() < s2.size())
      return true;

   return false;
}


const treenode* find(const treenode* n, const std::string& el)
{
   if (!n)
      return nullptr;
   if (!before(n->val, el) && !before(el, n->val))
      return n;
   else if (!before(n->val, el))
      return find(n->right, el);
   else if (before(n->val, el))
      return find(n->left, el);
}

treenode** find(treenode** n, const std::string& el)
{
   if (!(*n))
      return n;
   if (!before((*n)->val, el) && !before(el, (*n)->val))
      return n;
   else if (before((*n)->val, el))
      return find(&((*n)->right), el);
   else if (!before((*n)->val, el))
      return find(&((*n)->left), el);
}
// Insert n at the right most position in into: 

void rightinsert (treenode** into, treenode* n)
{
   if (!(*into))
      *into = n;
   else if (!((*into)->right))
      (*into)->right = n;
   else if ((*into)->right)
      rightinsert(&((*into)->right), n);
}


size_t size(const treenode* n)
{
   if (!n)
      return 0;
   else
      return size(n->left) + size(n->right) + 1;
}

size_t height(const treenode* n)
{
   size_t lh = 0;
   size_t rh = 0;
   if (!n)
   {
      return 0;
   }
   else if (!(n->left) && !(n->right))
   {
      return 1;
   }
   else
   {
      lh = height(n->left);
      rh = height(n->right);

      if (lh > rh)
      {
         lh += 1;
         return lh;
      }
      else
      {
         rh += 1;
         return rh;
      }   
   }
}

 
bool set::insert(const std::string& el)
{
   treenode **k = find(&tr, el);

   if (!(*k))
   {
      *k = new treenode(el);
      return true;
   }
   else
   {
      return false;
   }
}

bool set::contains(const std::string& el) const 
{
   return find(tr, el) != nullptr; 
}


bool set::remove(const std::string& el)
{
   treenode **tr_remove = find(&tr, el);

   if (!(*tr_remove))
   {
      return false;
   }
   else
   {
      if (!((*tr_remove)->left) && !((*tr_remove)->right))
      {
         delete *tr_remove;
         *tr_remove = nullptr;
      }
      else if ((*tr_remove)->left && (*tr_remove)->right)
      {
         rightinsert(&((*tr_remove)->left), (*tr_remove)->right);
         treenode *tr_bye = *tr_remove;
         *tr_remove = (*tr_remove)->left;
         delete tr_bye;
      }
      else if ((*tr_remove)->left && !((*tr_remove)->right))
      {
         treenode *tr_bye2 = *tr_remove;
         *tr_remove = (*tr_remove)->left;
         delete tr_bye2;
      }
      else if (!((*tr_remove)->left) && (*tr_remove)->right)
      {
         rightinsert(&((*tr_remove)->left), (*tr_remove)->right);
         treenode *tr_bye3 = *tr_remove;
         *tr_remove = (*tr_remove)->left;
         delete tr_bye3;
      }
      return true;
   }
  
}


void set::checksorted( ) const
{
   ::checksorted( tr, nullptr, nullptr );
      // :: are needed because the other checksorted is not in the class. 
}


std::ostream& set::print(size_t indent, std::ostream& out) const
{
   ::print( out, tr, indent );
   return out;
}


