#pragma once
#include <string>
#include <vector>

#include "GroceryItem.hpp"


// Singleton
class GroceryItemDatabase
{
  public:
    // Get a reference to the one and only instance of the database
    static GroceryItemDatabase & instance( const std::string & filename = "Grocery_UPC_Database_Sample.dat");

   // Locate and return a reference to a particular record
    GroceryItem * find( const std::string & upc );                              // Returns a pointer to the item in the database if found, nullptr otherwise

  private:
    GroceryItemDatabase            ( const std::string & filename );

    GroceryItemDatabase            ( const GroceryItemDatabase & ) = delete;    // intentionally prohibit making copies
    GroceryItemDatabase & operator=( const GroceryItemDatabase & ) = delete;    // intentionally prohibit copy assignments

    // We'll look at alternatives to std::vector later
    std::vector<GroceryItem> data;
};
