#pragma once    // include guard

#include <array>
#include <cstddef>                                                                            // size_t
#include <forward_list>
#include <iostream>
#include <list>
#include <stdexcept>                                                                          // domain_error, length_error
#include <string>
#include <vector>
#include <initializer_list>

#include "GroceryItem.hpp"


class GroceryList
{
  // Insertion and Extraction Operators
  friend std::ostream & operator<<( std::ostream & stream, const GroceryList & groceryList );
  friend std::istream & operator>>( std::istream & stream,       GroceryList & groceryList );

  // Logical Operators
  friend bool operator==( const GroceryList & lhs, const GroceryList & rhs );
  friend bool operator< ( const GroceryList & lhs, const GroceryList & rhs );

  public:
    // Types and Exceptions
    enum class Position {TOP, BOTTOM};

    struct InvalidInternalState_Ex : std::domain_error { using domain_error::domain_error; }; // Thrown if internal data structures become inconsistent with each other
    struct CapacityExceeded_ex     : std::length_error { using length_error::length_error; }; // Thrown if more items are inserted than will fit


    // Constructors, destructor, and assignment operators
    GroceryList();                                                                            // construct an empty grocery list

    GroceryList( const GroceryList  & other );                                                // construct a grocery list as a copy of another grocery list
    GroceryList(       GroceryList && other );                                                // construct a grocery list by taking the contents of another grocery list

    GroceryList & operator=( GroceryList    rhs );                                            // intentionally passed by value and not const ref
    GroceryList & operator=( GroceryList && rhs );

    GroceryList             ( const std::initializer_list<GroceryItem> & initList );          // constructs a grocery list from  a braced list of grocery items
    GroceryList & operator+=( const std::initializer_list<GroceryItem> & rhs      );          // concatenates a braced list of grocery items to this list
    GroceryList & operator+=( const GroceryList                        & rhs      );          // concatenates the rhs list to the end of this list

   ~GroceryList();


    // Queries
    std::size_t size()                           const;
    std::size_t find( const GroceryItem & item ) const;                                       // returns the (zero-based) offset from top of list
                                                                                              // returns the (zero-based) position of the item, size() if item not found


    // Mutators
    void insert( const GroceryItem & item, Position    position = Position::TOP );            // add the grocery item to the top (beginning) of the grocery list
    void insert( const GroceryItem & item, std::size_t offsetFromTop            );            // inserts before the existing item currently at that offset

    void remove( const GroceryItem & item          );                                         // no change occurs if item not found
    void remove( std::size_t         offsetFromTop );                                         // no change occurs if (zero-based) offsetFromTop >= size()

    void moveToTop( const GroceryItem & item );

    void swap( GroceryList & rhs ) noexcept;                                                  // exchange one grocery list with another

  private:
    // Helper functions
    bool        containersAreConsistant() const;
    std::size_t groceries_sl_list_size()  const;                                              // std::forward_list doesn't maintain size, so calculate it on demand

    // Instance Attributes
    std::size_t _groceries_array_size   = 0;                                                  // std::array's size is constant so manage that attributes ourself

    std::array       <GroceryItem, 11>  _groceries_array;
    std::vector      <GroceryItem    >  _groceries_vector;
    std::list        <GroceryItem    >  _groceries_dl_list;
    std::forward_list<GroceryItem    >  _groceries_sl_list;
};

// Logical Operators
bool operator==( const GroceryList & lhs, const GroceryList & rhs );
bool operator!=( const GroceryList & lhs, const GroceryList & rhs );

bool operator< ( const GroceryList & lhs, const GroceryList & rhs );
bool operator<=( const GroceryList & lhs, const GroceryList & rhs );
bool operator> ( const GroceryList & lhs, const GroceryList & rhs );
bool operator>=( const GroceryList & lhs, const GroceryList & rhs );
