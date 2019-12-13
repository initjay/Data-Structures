#include "WordFrequency.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <locale>     // tolower()


namespace
{
  std::string sanitize( const std::string & word )
  {
    constexpr char bad_char[] = " \t\n\b\v_-\"'(){}+/*,=.!?:;";            // leading and trailing characters to be removed
    static std::locale locality;

    auto startIndex = word.find_first_not_of( bad_char );                  // start with the first non-bad character
    if( startIndex == std::string::npos ) startIndex = word.size();        // if the word contains only bad characters ...

    std::size_t count    = 0;                                              // assume the word contains only bad characters ...
    auto        endIndex = word.find_last_not_of( bad_char );              // end with the first non-bad character

    if( endIndex != std::string::npos ) count = endIndex - startIndex + 1; // number of characters to use in results

    auto result = word.substr( startIndex, count );                        // strip the leading and trailing bad characters
    for( auto & c : result ) c = std::tolower( c, locality );              // convert to lower case

    return result;
  }
}    // namespace




///////////////////////// TO-DO //////////////////////////////
  /// Implement WordFrequency � This (default) constructor takes a reference to a standard input stream as a parameter defaulted to
  /// console input (e.g. std::cin).  This function is to
  ///  i.  read from standard input (std::cin) a single word at a time (delimited by whitespace as defined in standard C++) until
  ///      end of file, and
  /// ii.  increment the number of times this word has appeared in the text if it has been seen before, otherwise add it to the hash
  ///      table and initialize the frequency.
  /// Constraint: Only the �sanitized� word should be added to the hashtable.  For example, end punctuation (. ? !), opening &
  /// closing parentheses and brackets should be removed, but intra-word punctuation (' -) should remain.
  WordFrequency::WordFrequency(std::istream & iStream) {
    std::string word;

    while(iStream >> word) {
      word = sanitize(word);

      if(wordBank.find(word) == wordBank.end()) {
        wordBank[word] = 0;
      }

      wordBank[word] += 1;
    }

  }
/////////////////////// END-TO-DO ////////////////////////////



///////////////////////// TO-DO //////////////////////////////
  /// Implement numberOfWords � This function takes no arguments and returns the number of unique words.
std::size_t WordFrequency::numberOfWords() const {

  return wordBank.size();
}
/////////////////////// END-TO-DO ////////////////////////////



///////////////////////// TO-DO //////////////////////////////
  /// Implement wordCount � This function takes a constant reference to a standard string as a parameter and returns the frequency
  /// of occurrence of the that sanitized word.
  std::size_t WordFrequency::wordCount(const std::string & word) const {

      std::size_t count = wordBank.at(sanitize(word));

      return count;
  }
/////////////////////// END-TO-DO ////////////////////////////



///////////////////////// TO-DO //////////////////////////////
  /// Implement mostFrequentWord � This function takes no arguments and returns the most frequent word.
  std::string WordFrequency::mostFrequentWord() const {

    int largestValue = 0;
    std::string largestKey;

    for(auto i = wordBank.begin(); i != wordBank.end(); ++i) {
      if (i->second > largestValue) {
        largestValue = i->second;
        largestKey = i->first;
      }
    }

    return largestKey;
  }
/////////////////////// END-TO-DO ////////////////////////////




///////////////////////// TO-DO //////////////////////////////
  /// Implement maxBucketSize � This function takes no arguments and returns the size of the largest bucket in the hash table
  ///
  /// Hint: see the unordered_map's bucket interface at https://en.cppreference.com/w/cpp/container/unordered_map
  std::size_t WordFrequency::maxBucketSize() const {

    auto buckets = wordBank.bucket_count();
    std::size_t largestBucket= 0;


    for (unsigned long i = 0; i < buckets; ++i) {
      if(wordBank.bucket_size(i) > largestBucket) {
        largestBucket = wordBank.bucket_size(i);
      }
    }

    return largestBucket;
  }
/////////////////////// END-TO-DO ////////////////////////////
