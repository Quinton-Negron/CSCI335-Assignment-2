//Hannan Abid

#include "double_hashing.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <iomanip>
using namespace std;

//@param query: string that needs to be adjusted
//Makes all upper-case characters lowercase, removes punctuation, return carraige, and newline characters
void AdjustString(string &query)
{
  for(unsigned long int i = 0; i < query.length(); i++) //Change all letters to lowercase
  {
    if(query[i] >= 65 && query[i] <= 90)
    {
      query[i] += 32;
    }
   if(ispunct(query[i])) //remove punctuation marks
    {
      query.erase(i,1);
      i--;
    }
    if(query[i] == 13) //remove carriage return character
    {
      query.erase(i, 1);
      i--;
    }
    if(query[i] == 10) //remove newline character
    {
      query.erase(i, 1);
      i--;
    }
  }
}

//@param qeury: string to be used for search
//@param hash_table: hash table to be searched
//Outputs possible corrections to query after adding a character
template <typename HashTableType>
void AddChar(const string &query, HashTableType &hash_table)
{
  string teststring;
  for(unsigned long int i = 0; i <= query.length(); i++) //loop through string
  {

    for(unsigned long int j = 97; j <= 122; j++) //loop through all lowercase letters
    {

      teststring = query;
      static string add = " ";
      add[0] = j;
      teststring.insert(i, add); //insert lower case letters
      if(hash_table.Contains(teststring)) //check if new string is found in hash table

      {
        cout << "---> " <<teststring << setw(9)  << "case(a)" << endl;
      }

    }

  }

}


//@param qeury: string to be used for search
//@param hash_table: hash table to be searched
//Outputs possible corrections to query after removing a charcter
template <typename HashTableType>
void RemoveChar(const string &query, const HashTableType &hash_table)
{
  string teststring;
  for(unsigned long int i = 0; i < query.length(); i ++) //loop through query
  {

    teststring = query;
    teststring.erase(i, 1);
    if(teststring.length() != 0) //Do not check for empty string
    {

    if(hash_table.Contains(teststring)) //check if teststring is found in hash table
      {
        cout << "---> " <<teststring << setw(11)  << "case(b)" << endl;
      }

    }

  }

}


//@param qeury: string to be used for search
//@param hash_table: hash table to be searched
//Outputs possible corrections to query after swapping adjacent characters
template <typename HashTableType>
void SwapChar(const string &query, const HashTableType &hash_table)
{
  string teststring;
  for(unsigned long int i = 0; i < query.length() - 1; i++) //loop through query
  {
    teststring = query;
    std::swap(teststring[i], teststring[i + 1]);
    if(hash_table.Contains(teststring)) //check if teststring is found in hash table
      {
        cout << "---> " <<teststring << setw(10)  << "case(c)" << endl;
      }
  }
}


//@param hash_table: hash table to be populated
//@param dictionary: dictionary used for hash table population
template <typename HashTableType>
void PopulateDictTable(HashTableType &hash_table, fstream &dictionary)
{
  hash_table.MakeEmpty();
  string word;
  while(getline(dictionary, word)) //iterate through dictionary
  {
    if(word != "")
    {
      hash_table.Insert(word); //Insert words into hashtable
    }
  }
}

// Sample main for program spell_check
int main(int argc, char **argv) {
  if (argc != 3) {
    cout << "Usage: " << argv[0] << " <document-file> <dictionary-file>" << endl;
    return 0;
  }

  const string document_filename(argv[1]);
  const string dictionary_filename(argv[2]);

  cout << "Input document filename is " << document_filename << endl;
  cout << "Input dictionary filename is " << dictionary_filename << endl <<endl;

  fstream document;
  document.open(document_filename); //Open document file
  if(document.fail())
  {
    cout << "Could not open " << document_filename << endl << endl;
    return 1;
  }
  fstream dictionary_file;
  dictionary_file.open(dictionary_filename); //open dictionary file
  if(dictionary_file.fail())
  {
    cout << "Could not open " << dictionary_filename << endl << endl;
    return 1;
  }

  HashTableDouble<string> dictionary_table;
  PopulateDictTable(dictionary_table, dictionary_file); //Populate Hash table

  string testword;
  while(getline(document, testword, ' '))
  {

    while(testword == "" || testword == "/n" || testword[0] == 13) //Skip over invalid strings
    {
      getline(document, testword, ' ');
    }

    AdjustString(testword); //Modify string

    if(!dictionary_table.Contains(testword)) //If word is not found in hash table
      {

        cout << "Misspelled: " << testword << endl << endl;
        cout << "****************"<< "Possible Candidates" << "*************" << endl << endl;

        AddChar(testword, dictionary_table);
        RemoveChar(testword, dictionary_table);
        SwapChar(testword, dictionary_table);

        cout << endl <<"************************************************" << endl <<endl;
      }

  }

  return 0;

}
