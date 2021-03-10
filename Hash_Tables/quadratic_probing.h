//Hannan Abid

#ifndef QUADRATIC_PROBING_H
#define QUADRATIC_PROBING_H

#include <vector>
#include <algorithm>
#include <functional>
#include <iostream>


namespace {

// Internal method to test if a positive number is prime.
bool IsPrime(size_t n) {
  if( n == 2 || n == 3 )
    return true;

  if( n == 1 || n % 2 == 0 )
    return false;

  for( int i = 3; i * i <= n; i += 2 )
    if( n % i == 0 )
      return false;

  return true;
}


// Internal method to return a prime number at least as large as n.
int NextPrime(size_t n) {
  if (n % 2 == 0)
    ++n;
  while (!IsPrime(n)) n += 2;
  return n;
}

}  // namespace


// Quadratic probing implementation.
template <typename HashedObj>
class HashTable {
 public:
  enum EntryType {ACTIVE, EMPTY, DELETED};

  explicit HashTable(size_t size = 101) : array_(NextPrime(size))
    { MakeEmpty(); }

  bool Contains(const HashedObj & x) const {
    return IsActive(FindPos(x));
  }

  void MakeEmpty() {
    current_size_ = 0;
    for (auto &entry : array_)
      entry.info_ = EMPTY;
  }

  bool Insert(const HashedObj & x) {
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

  bool Insert(HashedObj && x) {
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

//////////////Added Functions/////////////////////////////////

  ///Return number of elements
  float NumberofItems() const
  {
    return current_size_;
  }


  ///Return Size of Hash table
  float TableSize() const
  {
    return array_.size();
  }

  //Load factor
  float LoadFactor() const
  {
    return NumberofItems()/TableSize();
  }

  //Number of Collisions
  float CollisionNumber() const
  {
    return number_of_collisions_;
  }

  //Average collisions
  float AverageCollisions() const
  {

    return CollisionNumber()/NumberofItems();
  }

  //@param: object to be probed
  //@return: number of probes used for object
  int getProbeNumber(const HashedObj &x) const
  {
    number_of_probes_ = 1;
    size_t offset = 1;
    size_t current_pos = InternalHash(x);

    while (array_[current_pos].info_ != EMPTY &&
	   array_[current_pos].element_ != x) {
      number_of_probes_++;
      current_pos += offset;  // Compute ith probe.
      offset += 2;
      if (current_pos >= array_.size())
	    current_pos -= array_.size();
    }
    return number_of_probes_;
  }



//////////////////////////////////////////////////////////////
 private:

  struct HashEntry {
    HashedObj element_;
    EntryType info_;

    HashEntry(const HashedObj& e = HashedObj{}, EntryType i = EMPTY)
    :element_{e}, info_{i} { }

    HashEntry(HashedObj && e, EntryType i = EMPTY)
    :element_{std::move(e)}, info_{ i } {}
  };


  std::vector<HashEntry> array_;
  size_t current_size_;
  mutable size_t number_of_collisions_ = 0;
  mutable size_t number_of_probes_ = 0 ;


  bool IsActive(size_t current_pos) const
  { return array_[current_pos].info_ == ACTIVE; }

  //@param: object to be hashed
  //@return: hash value of object
  size_t FindPos(const HashedObj & x) const {
    size_t offset = 1;
    size_t current_pos = InternalHash(x);

    while (array_[current_pos].info_ != EMPTY &&
	   array_[current_pos].element_ != x) {
      number_of_collisions_++;
      current_pos += offset;  // Compute ith probe using quadratic probing.
      offset += 2;
      if (current_pos >= array_.size())
	    current_pos -= array_.size();
    }
    return current_pos;
  }

  //Increase size of hash table and rehash values
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

#endif  // QUADRATIC_PROBING_H
