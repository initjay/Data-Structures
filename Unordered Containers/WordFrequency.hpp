#pragma once
#include <cstddef>    // size_t
#include <string>
#include <fstream>
#include <iostream>

///////////////////////// TO-DO //////////////////////////////
  /// Add any additional include files here
  #include <unordered_map>
/////////////////////// END-TO-DO ////////////////////////////

class WordFrequency
{
  public:
    WordFrequency( std::istream & iStream = std::cin);                 // (default) constructor, add words from file to hash table

    std::size_t numberOfWords   ()                           const;    // return the number of unique words
    std::size_t wordCount       ( const std::string & word ) const;    // return the number of occurrences of the given word
    std::string mostFrequentWord()                           const;    // return the most frequent word
    std::size_t maxBucketSize   ()                           const;    // return the size of the largest bucket in the hash table


  private:
    ///////////////////////// TO-DO //////////////////////////////
      /// The class should have a single member variable, of class std::unordered_map which is the C++ Standard Library�s
      /// implementation of a hash table, to store the association of words (key) to the number of times a word occurs (value).
      std::unordered_map<std::string, int> wordBank;
    /////////////////////// END-TO-DO ////////////////////////////
};
