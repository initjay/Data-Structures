#include <algorithm>    // find()
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>


#include "GroceryItemDatabase.hpp"

namespace
{
  // User defined manipulator with arguments that allows std::istream::ignore to be called "in-line" (chained)
  // Usage example:
  //    stream >> first >> ignore(',') second >> ignore('\n') ;
  struct ignore
  {
    char _seperator;
    ignore( char delimiter = '\n' ) : _seperator( delimiter ) {}
  };

  std::istream & operator>>( std::istream & s, ignore && delimiter )
  {
    s.ignore( 100'000'000ULL, delimiter._seperator );
    return s;
  }
}



// Return a reference to the one and only instance of the database
GroceryItemDatabase & GroceryItemDatabase::instance( const std::string & filename )
{
  static GroceryItemDatabase theInstance( filename );
  return theInstance;
}



// Construction
GroceryItemDatabase::GroceryItemDatabase( const std::string & filename )
{
  std::ifstream fin;
  try
  {
    fin.exceptions( std::ios::badbit | std::ios::failbit | std::ios::eofbit );

    fin.open( filename, std::ios::binary );

    ///////////////////////// TO-DO //////////////////////////////
      /// At this point the store's persistent data file has been opened successfully and is ready for you to read the contents.
      ///
      /// Hint:  Do not check to see if the file is open, you already know it is.  If it didn't open correctly an exception would
      ///        have been thrown and you wouldn't have gotten to this point in the code.
      ///
      /// The file contains one record of data on each line of text.  See Grocery_UPC_Database_Sample.dat.  A record has 4 pieces of
      /// data delimited with a comma.
      ///
      ///       Field            Type            Notes
      ///  1.   UPC Code         String          Unique identifier (primary key), always enclosed in double quotes
      ///  2.   Brand Name       String          May contain spaces, always enclosed in double quotes
      ///  3.   Product Name     String          May contain spaces, always enclosed in double quotes
      ///  4.   Price            Floating Point  In dollars
      ///
      ///  Example:
      ///    "00024600017008",   "Morton",         "Morton Kosher Salt Coarse",                                    15.17
      ///    "00033674100066",   "Nature's Way",   "Nature's Way Forskohlii - 60 Ct",                              6.11
      ///    "00041520893307",   "Smart Living",   "Smart Living 10.5\" X 8\" 3 Subject Notebook College Ruled",   18.98
      ///
      ///  Note: double quotes within the string are escaped with the backslash character
      ///
      ///  Hint: Use the std::quoted() manipulator to read the fields of data.  This manipulator knows how to read quoted strings.
      ///        You've used this in previous assignments.
      ///
      ///  Hint: Consume and ignore the delimiter between the fields using the ignore manipulator above.
      ///
      ///  Example:
      ///     fin >> std::quoted( upc ) >> ignore(',') >> std::quoted( brand );
      ///
      ///
      ///  After reading the 4 fields of a record, use those to create a GroceryItem and then add that GroceryItem to the memory
      ///  resident container called data, an instance attribute of this GroceryItemDatabase class.

      /// Note:  The file is intentionally not explicitly closed.  The file is closed when fin goes out of scope - for whatever
      ///        reason.  See RAII

      std::string upc, brandName, productName;
      double price;

      while (fin >> std::quoted(upc) >> ignore(',') >> std::quoted(brandName) >> ignore(',') >>
              std::quoted(productName) >> ignore(',') >> price) {

        GroceryItem tempItem(productName, brandName, upc, price);
        data.insert(std::pair<std::string, GroceryItem>(tempItem.UPC(),tempItem));
      }

    /////////////////////// END-TO-DO ////////////////////////////
  }

  catch( const std::ios::failure & ex )
  {
    // end of file is expected at the start of a new Grocery Item, but could appear anywhere (missing a delimiter, partial data
    // provided, misreading elements with spaces, and so on).  When that happens, reject the partial data such that only valid,
    // complete grocery items are entered into the memory resident data store.
    if( !fin.eof() )
    {
      data.clear();
      std::cerr << "ERROR opening or reading from " << filename << ", using an empty database\n"
                << "  Error code:  " << ex.code() << '\n'
                << "  Meaning:     " << ex.what() << '\n';
    }
  }
}



GroceryItem * GroceryItemDatabase::find( const std::string & upc )
{
  ///////////////////////// TO-DO //////////////////////////////
    /// Walk the memory resident container called data looking for a grocery item with a matching upc code.  If found, return a
    /// pointer to that grocery item.  Otherwise return a null pointer.

    // for(auto &item: data) {
    //   if(item.UPC().compare(upc) == 0) {
    //     return &item;
    //   }
    // }

    //return nullptr;

    auto itItem = data.find(upc);

    if(itItem != data.end()) {
      return &itItem->second;
    } else {
      return nullptr;
    }


  /////////////////////// END-TO-DO ////////////////////////////
}
