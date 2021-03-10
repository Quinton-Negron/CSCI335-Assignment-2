//Quinton Negron
#include "quadratic_probing.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <ctype.h>
using namespace std;

template <typename HashTableType>
void SpellChecker(HashTableType &hash_table, const string &document_filename, const string &dictionary_filename)
{
    hash_table.MakeEmpty(); //makes table empty
    string dictionary = "";
    string letter = "";
    string A, B, C;

    ifstream words(dictionary_filename); //gets dictionary
    while(getline(words, dictionary))
    {
        hash_table.Insert(dictionary); //we have our dictionary
    }
    
    ifstream file(document_filename);
    while (file >> letter) //for every word in the document, we comb through it for adjustment (capitalization and  puncuation)
    {
        for(int i = 0; i < letter.size(); i++)
        {
            letter[i] = tolower(letter[i]); //makes the letters lowercase
            letter.erase(std::remove(letter.begin(), letter.end(), '.'), letter.end()); //removes periods
            letter.erase(std::remove(letter.begin(), letter.end(), '?'), letter.end()); //removes question marks
            letter.erase(std::remove(letter.begin(), letter.end(), '!'), letter.end()); // removes exclamation marks
            letter.erase(std::remove(letter.begin(), letter.end(), ','), letter.end()); //removes commas
            letter.erase(std::remove(letter.begin(), letter.end(), ':'), letter.end()); //removes colons
            letter.erase(std::remove(letter.begin(), letter.end(), ';'), letter.end()); //removes semicolons
            //letter.erase(std::remove(letter.begin(), letter.end(), '-'), letter.end()); //removes dashes
        }
        
        if(hash_table.Contains(letter) == false) //compares words with hash table
        {
            cout << letter << " is INCORRECT" << endl;
            
            for(int i = 0; i <= letter.length(); i++) //loops through string using the ascii code for lowercase to fix spelling errors
            {
                for(int j = 97; j <= 122; j++)
                {
                    A = letter; //passes current letter to A for
                    string add = " "; add[0] = j; //add was needed to be able to use insert
                    A.insert(i, add);
                    if(hash_table.Contains(A))
                    {
                        cout << "** "<< letter << " -> " << A << " **" << " case A" << endl;
                    }

                }
            }
            
            for(int i = 0; i < letter.length(); i++)
            {
                B = letter; B.erase(i, 1);
                if(hash_table.Contains(B))
                {
                    cout << "** " << letter << " -> " << B << " **" << " case B" << endl;
                }
            }
            
            for(int i = 0; i < letter.length(); i++)
            {
                C = letter; std::swap(C[i], C[i + 1]);
                if(hash_table.Contains(C))
                {
                    cout << "** " <<  letter << " -> " << C << " **" << " case C" << endl;
                }
            }
        }
        else
        {
            cout << letter << " is CORRECT" << endl;
        }
    }
}
int testSpellingWrapper(int argument_count, char** argument_list)
{
    const string  words_filename(argument_list[1]);
    const string query_filename(argument_list[2]);
    HashTable<string> quadratic_probing_table;
    SpellChecker(quadratic_probing_table, words_filename, query_filename);
    return 0;
}


// Sample main for program spell_check.
// WE WILL NOT USE YOUR MAIN IN TESTING. DO NOT CODE FUNCTIONALITY INTO THE MAIN.
// WE WILL DIRECTLY CALL testSpellingWrapper. ALL FUNCTIONALITY SHOULD BE THERE.
// This main is only here for your own testing purposes.
int main(int argc, char **argv)
{
    if (argc != 3)
    {
        cout << "Usage: " << argv[0] << " <document-file> <dictionary-file>" << endl;
        return 0;
    }
    testSpellingWrapper(argc, argv);
    return 0;
}

