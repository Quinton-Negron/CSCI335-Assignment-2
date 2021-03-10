// Hannan Abid

#include "quadratic_probing.h"
#include "linear_probing.h"
#include "double_probing.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//@param: hash table to be populated and statistically analyzed
//@param: words file name used to populate hash table
//@param: query file name used to search hash table
template <typename HashTableType>
void TestFunctionForHashTable(HashTableType &hash_table, const string &words_filename, const string &query_filename) {
  cout << "TestFunctionForHashTables..." << endl;
  cout << "Words filename: " << words_filename << endl;
  cout << "Query filename: " << query_filename << endl;
  hash_table.MakeEmpty();

  string query;
  string element;
  fstream wordsfile;
  fstream queryfile;
  queryfile.open(query_filename);
  if(queryfile.fail())
  {
    cout << "Could not open " << query_filename << endl;
    return;
  }

  wordsfile.open(words_filename);
  if(wordsfile.fail())
  {
    cout << "Could not open " << words_filename << endl;
    return;
  }

  cout << "Inserting words into the HashTable..." << endl << endl;

  while(getline(wordsfile,element))//Iterate through wordsfile and add elements to hash table
  {
    if(element != "")
    {
        hash_table.Insert(element);
    }

  }

  //compute Statistics
  cout << "Statistics for this Hash Table:" << endl;
  cout << "Elements in table: " << hash_table.NumberofItems() << endl;
  cout << "Size of the table: " << hash_table.TableSize() << endl;
  cout << "Load Factor: " << hash_table.LoadFactor() << endl;
  cout << "Number of Collisions: " << hash_table.CollisionNumber() << endl;
  cout << "Average Number of Collisions: " << hash_table.AverageCollisions() << endl;
  cout << endl;

  //Quering words from queryfile
  cout << "Beginning seaching for query words:" << endl;
  while(getline(queryfile, query)) //Iterate through queryfile and search for words and number of probes used
  {
    cout << query << ": ";
    if(hash_table.Contains(query))
    {
      cout << "Found in " << hash_table.getProbeNumber(query) << " probes" << endl;
    }
    else
    {
      cout << "Not found in " << hash_table.getProbeNumber(query) << " probes" << endl;
    }
  }

}

// Sample main for program create_and_test_hash
int
main(int argc, char **argv) {
  if (argc != 4) {
    cout << "Usage: " << argv[0] << " <wordsfilename> <queryfilename> <flag>" << endl;
    return 0;
  }

  const string words_filename(argv[1]);
  const string query_filename(argv[2]);
  const string param_flag(argv[3]);

  if (param_flag == "linear") {
    cout << "I will run the linear Hash code" << endl;
     HashTableLinear<string> linear_probing_table;
     TestFunctionForHashTable(linear_probing_table, words_filename, query_filename);
  } else if (param_flag == "quadratic") {
    cout << "I will run the quadratic Hash code" << endl;
    HashTable<string> quadratic_probing_table;
    TestFunctionForHashTable(quadratic_probing_table, words_filename, query_filename);
  } else if (param_flag == "double") {
    cout << "I will run the double Hash code" << endl;
    HashTableDouble<string> double_probing_table;
    TestFunctionForHashTable(double_probing_table, words_filename, query_filename);
  } else {
    cout << "Uknown tree type " << param_flag << " (User should provide linear, quadratic, or double)" << endl;
  }
  return 0;
}
