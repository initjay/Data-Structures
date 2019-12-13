#include <cmath>          // abs()
#include <fstream>
#include <iostream>       // boolalpha()
#include <string>
#include <type_traits>    // is_floating_point

#include "WordFrequency.hpp"



namespace  // unnamed, anonymous namespace
{
  struct AssertEquals
  {
    public:
      template<typename T, typename U>
      bool operator()( const std::string & nameOfTest, const T & expected, const U & actual );

      unsigned testCount   = 0;
      unsigned testsPassed = 0;

    private:
      static constexpr auto GREEN = "\033[32m";
      static constexpr auto RED   = "\033[31m";
      static constexpr auto RESET = "\033[0m";
  };
}    // namespace








int main()
{
  AssertEquals  assertEquals;

  // Test set 1 - Frankenstein
  {
    std::ifstream fin( "Frankenstein or The Modern Prometheus by Mary Shelley.txt" );

    WordFrequency Frankenstein( fin );
    assertEquals( "numberOfWords: Frankenstein   ",    7195U, Frankenstein.numberOfWords()             );
    assertEquals( "wordCount: Frankenstein       ",      24U, Frankenstein.wordCount( "Frankenstein" ) );
    assertEquals( "wordCount: life               ",     114U, Frankenstein.wordCount( "life" )         );
    assertEquals( "wordCount: feared             ",      13U, Frankenstein.wordCount( "feared" )       );
    assertEquals( "wordCount: the                ",    4187U, Frankenstein.wordCount( "the" )          );
    assertEquals( "mostFrequentWord: Frankenstein",    "the", Frankenstein.mostFrequentWord()          );

    std::size_t size = Frankenstein.maxBucketSize();    
    assertEquals( "maxBucketSize: Frankenstein   ", (size - 5 <= 2 ? size : 6U ), size);  // expecting 5, 6, or 7 to allow a little wiggle room for different library implementations
                                                                                          // Programming note: intentionally using unsigned subtraction allowing genitive number to wrap
                                                                                          // around to become very large positive numbers
  }

  std::cout << "\n\n";

  // Test set 2 - Sleepy Hollow
  {
    WordFrequency sleepyHollow;
    assertEquals( "numberOfWords: Sleepy Hollow   ",   3231U, sleepyHollow.numberOfWords()        );
    assertEquals( "wordCount: Ichabod             ",     45U, sleepyHollow.wordCount( "Ichabod" ) );
    assertEquals( "wordCount: the                 ",    917U, sleepyHollow.wordCount( "the" )     );
    assertEquals( "mostFrequentWord: Sleepy Hollow",   "the", sleepyHollow.mostFrequentWord()     );

    std::size_t size = sleepyHollow.maxBucketSize();
    assertEquals( "maxBucketSize: Sleepy Hollow   ", ( size - 4 <= 2 ? size : 5U ), size );    // expecting 4, 5, or 6 to allow a little wiggle room for different library implementations
                                                                                               // Programming note: intentionally using unsigned subtraction allowing genitive number to wrap
                                                                                               // around to become very large positive numbers
  }

  std::cout << "\n\nSummary: " << assertEquals.testsPassed << " of " << assertEquals.testCount
                               << " (" << assertEquals.testsPassed * 100.0 / assertEquals.testCount << "%) tests passed\n";

  return 0;
}









namespace // unnamed, anonymous namespace
{
  template<typename T, typename U>
  bool AssertEquals::operator()( const std::string & nameOfTest, const T & expected, const U & actual )
  {
    ++testCount;

    bool pass = false;
    if      constexpr( std::is_floating_point<T>::value && std::is_floating_point<U>::value ) pass = std::abs( expected - actual ) < 0.005;
    else                                                                                      pass = expected == actual;

    if( pass )
    {
      ++testsPassed;
      // Green colored text
      std::cout << std::boolalpha
                << GREEN << "PASSED "
                << RESET << nameOfTest << ": expected and actual '" << actual << "'\n";
    }
    else
    {
      // Red colored text
      std::cout << std::boolalpha
                << RED << "FAILED "
                << RESET << nameOfTest << ": expected '" << expected << "' but found '" << actual << "'\n";
    }

    return pass;
  }
}    // namespace
