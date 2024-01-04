#include <iostream>
#include <string>
#include <fstream>
#include "AVLSearchTree.h"
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;
struct DocumentItem{
    string documentName;
    int count;
};
struct WordItem{
    string word;
    AVLSearchTree<string, DocumentItem> documentList;
};

bool is_alpha(string str1) //checks if the given string is alphabetical returns true if so
{
    for(int i = 0; i < str1.length(); i++)
    {
        if(!isalpha(str1[i]))
        {
            return false;
        }
    }
    return true;
}

string to_Lower(const string &s1) // returns the lowercase version of the string
{
    string result;
    result = "";
    for(int i = 0; i < s1.length(); i++)
    {
        result += tolower(s1[i]);
    }
    return result;
}

bool doc_has_queries(vector<string> & queries, const string & doc_name, AVLSearchTree<string,WordItem*> & myTree) //checks if the given document has the
{                                                                                                                 // given queries in it returns true if so
    for(const string & query:queries)
    {
        if(myTree.valueOf(query)->documentList.find(doc_name) == "item not found")
        {
            return false;
        }
    }
    return true;
}

bool tree_has_queries(vector<string> & queries, AVLSearchTree<string,WordItem*> & myTree) //checks if the given tree has the
{                                                                                         // given queries in it returns true if so
    for(const string & query:queries)
    {
        if(myTree.find(query) == "item not found")
        {
            return false;
        }
    }
    return true;
}

int main()
{
    int file_count;
    cout << "Enter number of input files: ";
    cin >> file_count;

    vector<string> file_names; //creating a vector to store the document(file) names
    AVLSearchTree<string , WordItem*> Search_Engine; //creating the tree to store the word items

    for(int i = 0; i < file_count; i++)
    {
        string file_name;
        cout << "Enter " << i+1 << ". " << "file name: ";
        cin >> file_name;

        file_names.push_back(file_name); //adding the file name to the vector
        ifstream file1;
        file1.open(file_name);

        string str; //string to read words from the file
        DocumentItem doc1;
        WordItem *word1;

        while(file1 >> str) //reading words from the file
        {
            str = to_Lower(str); //making the string lowercase to be case-insensitive
            if(is_alpha(str)) //checking if the string is a word or not
            {
                if(Search_Engine.find(str) == "item not found") //checking if the word is already in the tree or not
                {
                    word1 = new WordItem;
                    doc1.documentName = file_name; //assigning the file name to the document name
                    doc1.count = 1; //making the count 1 since we are adding it for the first time
                    word1->word = str; //assigning the str to the word of the word item object
                    word1->documentList.insert(file_name, doc1); //inserting the document item object to the document list of word item
                    Search_Engine.insert(str,word1); //inserting the word item object to the tree
                }
                else //if the word is already in the tree
                {
                    if(Search_Engine.valueOf(str)->documentList.find(file_name) != "item not found") //checking if the document of the word that is in the tree is the current one
                    {
                        Search_Engine.valueOf(str)->documentList.valueOf(file_name).count++; //if so incrementing the count of the word for that document
                    }
                    else
                    {
                        Search_Engine.valueOf(str)->documentList.insert(file_name, doc1); //if it is not in the document list adding it as a new document to the document list
                    }
                }
            }
        }
    }

    string queries;
    cout << "Enter queried words in one line: ";

    cin.ignore();
    getline(cin, queries); // getting a line of input
    while(queries != "ENDOFINPUT")
    {
        istringstream iss(queries);
        string word;
        vector<string> query_list;

        while (iss >> word) //getting the separate words from the line of input
        {
            if(word != "REMOVE")
                word = to_Lower(word); //making the word lowercase
            query_list.push_back(word); //adding the word to a vector to further use them
        }
        if(query_list[0] != "REMOVE")
        {
            bool query_not_found = false; //a bool to check if queries are in the files
            if (!tree_has_queries(query_list, Search_Engine)) //checking if the queries are in the tree
            {
                cout << "No document contains the given query" << endl; //if they are not in the tree
            } else //if they are in the tree
            {
                for (const string &file_name: file_names) //iterating over file names
                {
                    if (doc_has_queries(query_list, file_name,
                                        Search_Engine)) //checking if the file contains the queries
                    {
                        cout << "In Document " << file_name << ", ";

                        for (const string &query: query_list) //iterating over words to display their values
                        {
                            cout << query << " found "
                                 << Search_Engine.valueOf(query)->documentList.valueOf(file_name).count << " times";

                            if (query != query_list[query_list.size() - 1]) {
                                cout << ", ";
                            }
                        }
                        cout << "." << endl;
                        query_not_found = true; //if neither of the files contain the queries the variable is false
                    }
                }

                if (!query_not_found) //if neither of the files contain the queries, displaying the info for that
                {
                    cout << "No document contains the given query" << endl;
                }
            }
        }
        else //If the first word in the input words is REMOVE
        {
            Search_Engine.remove(query_list[1]); //removing the given word from the tree
            cout << query_list[1] << " has been REMOVED" << endl;
        }

        cout << "Enter queried words in one line: ";

        getline(cin, queries); // getting a line of input
    }

    return 0;
}
