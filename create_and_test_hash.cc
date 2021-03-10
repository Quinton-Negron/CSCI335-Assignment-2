//Quinton Negron
#include "quadratic_probing.h"
#include "double_hashing.h"
#include "linear_probing.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

template <typename HashTableType>
void TestFunctionForDoubleHashTable(HashTableType &hash_table, const string &words_filename, const string &query_filename, const string r_value)
{
    hash_table.MakeEmpty();
    
    ifstream letter_filename;
    letter_filename.open(words_filename); //last 2 lines help us open the file
    string table = ""; //where we are going to place our data form teh file
    while(getline(letter_filename, table))
    {
        hash_table.Insert(table); // while collecting data, insert into hash_table
    }
    
    cout << "r_value: " << hash_table.rvalur_output() << endl;
    cout << "number_of_elements: " << hash_table.total_elements() << endl;
    cout << "size_of_table: " << hash_table.table_size() << endl;
    cout << "load_factor: "<< hash_table.total_elements()/hash_table.table_size() << endl;
    cout << "collisions: " << hash_table.total_collisions() << endl;
    cout << "avg_collisions: " << hash_table.total_collisions()/hash_table.total_elements() << endl;
    cout << endl;
    
    table = ""; //reuse table for the next file
    ifstream other_letter_filename;
    other_letter_filename.open(query_filename);
    while (getline(other_letter_filename, table))
    {
        if(hash_table.Contains(table) == false)
        {
            cout << table << " Not_Found " << hash_table.total_copies() << endl;
        }
        else
        {
            cout << table << " Found " << hash_table.total_copies() << endl;
        }
    }
}

template <typename HashTableType>
void TestFunctionForHashTable(HashTableType &hash_table, const string &words_filename, const string &query_filename)
{
    hash_table.MakeEmpty();
    
    ifstream letter_filename;
    letter_filename.open(words_filename); //last 2 lines help us open the file
    string table = ""; //where we are going to place our data form teh file
    while(getline(letter_filename, table))
    {
        hash_table.Insert(table); // while collecting data, insert into hash_table
    }
    
    cout << "number_of_elements: " << hash_table.total_elements() << endl;
    cout << "size_of_table: " << hash_table.table_size() << endl;
    cout << "load_factor: "<< hash_table.total_elements()/hash_table.table_size() << endl;
    cout << "collisions: " << hash_table.total_collisions() << endl;
    cout << "avg_collisions: " << hash_table.total_collisions()/hash_table.total_elements() << endl;
    cout << endl;
    
    table = ""; //reuse table for the next file
    ifstream other_letter_filename;
    other_letter_filename.open(query_filename);
    while (getline(other_letter_filename, table))
    {
        if(hash_table.Contains(table) == false)
        {
            cout << table << " Not_Found " << hash_table.total_copies() << endl;
        }
        else
        {
            cout << table << " Found " << hash_table.total_copies() << endl;
        }
    }
}

int testFunctionWrapper(int argument_count, char **argument_list)
{
    const string words_filename(argument_list[1]);
    const string query_filename(argument_list[2]);
    const string param_flag(argument_list[3]);

    if (param_flag == "linear")
    {
      HashTableLinear<string> linear_probing_table;
      TestFunctionForHashTable(linear_probing_table, words_filename, query_filename);
    }
    
    else if (param_flag == "quadratic")
    {
        HashTable<string> quadratic_probing_table;
        TestFunctionForHashTable(quadratic_probing_table, words_filename, query_filename);
    }
    
    else if (param_flag == "double")
    {
        //to account for the double taking in a foruth argument we need to
        //1) have a condition where the r_value is taken in
        //2) adjust for a non fourth case (that later part was super weird and gave me errors for just having the doubles case be for the sperate function
        //I had to make an if/else statement where a double could have no r_value to make sure that linear and quadratic don't break
        const string R_value(argument_list[4]); //define our fourth arguement
        if (argument_count != 5)//normal argument
        {
            HashTableDouble<string> quadratic_probing_table;
            TestFunctionForHashTable(quadratic_probing_table, words_filename, query_filename);
        }
        else
        {
            //actual doubles arguemnt
            int converted_Rvalue = stoi(R_value); //argv is a char, so we need to conver that into an int
            HashTableDouble<string> double_probing_table; //define a doubles table
            double_probing_table.rvalue(converted_Rvalue); //place that converetd value into a table
            TestFunctionForDoubleHashTable(double_probing_table, words_filename, query_filename,R_value); //pass the parameters as you normally would, but  with r as well
        }
    }
    
    else
    {
      cout << "Unknown tree type " << param_flag << " (User should provide linear, quadratic, or double)" << endl;
    }
    return 0;
}

// Sample main for program create_and_test_hash.
// WE WILL NOT USE YOUR MAIN IN TESTING. DO NOT CODE FUNCTIONALITY INTO THE MAIN.
// WE WILL DIRECTLY CALL testFunctionWrapper. ALL FUNCTIONALITY SHOULD BE THERE.
// This main is only here for your own testing purposes.
int main(int argc, char **argv) {
  if (argc != 4 && argc != 5) {
    cout << "Usage: " << argv[0] << " <wordsfilename> <queryfilename> <flag>" << endl;
    return 0;
  }
    
  testFunctionWrapper(argc, argv);
  return 0;
}
