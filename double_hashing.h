//Quinton Negron
#ifndef DOUBLE_PROBING_H
#define DOUBLE_PROBING_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;

// Quadratic probing implementation.
template <typename HashedObj>
class HashTableDouble
{
public:
    
    enum EntryType {ACTIVE, EMPTY, DELETED};
     explicit HashTableDouble(size_t size = 101) : array_(NextPrime(size))
       { MakeEmpty(); }
     
    bool Contains(const HashedObj & x) const
    {
        return IsActive(FindPos(x));
    }
    void MakeEmpty()
    {
        //ever time we check a word we need to reset our collisions and probing. This ensures that the previous results are not mixed in with the new ones
        current_size_ = 0;
        copies = 0;
        collisions = 0;
        for (auto &entry : array_)
          entry.info_ = EMPTY;
     }

    bool Insert(const HashedObj & x)
    {
       // Insert x as active
       size_t current_pos = FindPos(x);
       if (IsActive(current_pos))
         return false;
       
       array_[current_pos].element_ = x;
       array_[current_pos].info_ = ACTIVE;
       
       // Rehash; see Section 5.5
       if (++current_size_ > array_.size() / 2)
         Rehash();
       return true;
    }
       
    bool Insert(HashedObj && x)
    {
       // Insert x as active
       size_t current_pos = FindPos(x);
       if (IsActive(current_pos))
         return false;
       
       array_[current_pos] = std::move(x);
       array_[current_pos].info_ = ACTIVE;

       // Rehash; see Section 5.5
       if (++current_size_ > array_.size() / 2)
         Rehash();

       return true;
     }

     bool Remove(const HashedObj & x) {
       size_t current_pos = FindPos(x);
       if (!IsActive(current_pos))
         return false;

       array_[current_pos].info_ = DELETED;
       return true;
     }
       
       double total_elements()
       {
           return current_size_;
       }
       
       double table_size()
       {
           return array_.size();
       }
       
       double total_collisions()
       {
           return collisions;
       }
       
       double total_copies()
       {
           return copies;
       }
    
    int rvalue(int value)
    {
        r = value;
    }
    
    int rvalur_output()
    {
        return r;
    }
       
    private:
     struct HashEntry
       {
       HashedObj element_;
       EntryType info_;
       
       HashEntry(const HashedObj& e = HashedObj{}, EntryType i = EMPTY)
       :element_{e}, info_{i} { }
       
       HashEntry(HashedObj && e, EntryType i = EMPTY)
       :element_{std::move(e)}, info_{ i } {}
     };
       

     std::vector<HashEntry> array_;
     size_t current_size_;
       mutable double copies;
       mutable double collisions;
    mutable int r;

     bool IsActive(size_t current_pos) const
     { return array_[current_pos].info_ == ACTIVE; }

     size_t FindPos(const HashedObj & x) const
     {
         static std::hash<HashedObj> hf;
         size_t count = 1;
         size_t offset = 1;
         size_t counter = 1;
         offset = counter * (r - (hf (x) % r));
         size_t current_pos = InternalHash(x);
           
         while (array_[current_pos].info_ != EMPTY &&
          array_[current_pos].element_ != x)
         {
             collisions++;
             current_pos += offset;  // Compute ith probe.
             count++;
             
             if (current_pos >= array_.size())
             {
                 current_pos -= array_.size();
             }
         }
         
         copies = std::move(count);//std::move is used as a way to take a static cast (count) and transfer it into an rvalue (copies). In short, this is an efficient way of handling the moves that occur when a word makes a collions (or probes in this case).
         return current_pos;
     }

     void Rehash() {
       std::vector<HashEntry> old_array = array_;

       // Create new double-sized, empty table.
       array_.resize(NextPrime(2 * old_array.size()));
       for (auto & entry : array_)
         entry.info_ = EMPTY;
       
       // Copy table over.
       current_size_ = 0;
       for (auto & entry :old_array)
         if (entry.info_ == ACTIVE)
       Insert(std::move(entry.element_));
     }
     
     size_t InternalHash(const HashedObj & x) const {
       static std::hash<HashedObj> hf;
       return hf(x) % array_.size( );
     }
};

#endif  // QUADRA
