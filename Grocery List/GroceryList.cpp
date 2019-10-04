#include <algorithm>            // find(), move(), move_backward(), equal(), swap(), lexicographical_compare()
#include <cstddef>              // size_t
#include <initializer_list>
#include <iterator>             // distance()
#include <iomanip>              // setw()
#include <stdexcept>            // logic_error
#include <string>
#include <utility>              // move()

#include "GroceryItem.hpp"
#include "GroceryList.hpp"



// As a rule, I strongly recommend avoiding macros, unless there is a compelling reason - this is such a case. This really does need
// to be a macro and not a function due to the way the preprocessor expands the source code location information.  It's important to
// have these expanded where they are used, and not here. But I just can't bring myself to writing this, and getting it correct,
// everywhere it is used.  Note:  C++20 will change this technique with the introduction of the source_location class. Also note the
// usage of having the preprocessor concatenate two string literals separated only by whitespace.
#define exception_location "\n detected in function \"" + std::string(__func__) +  "\""    \
                           "\n at line " + std::to_string( __LINE__ ) +                    \
                           "\n in file \"" __FILE__ "\""






/*******************************************************************************
**  Private implementations, types, and objects
*******************************************************************************/
// Calculate the size of the singly linked list on demand
std::size_t GroceryList::groceries_sl_list_size() const
{
  ///////////////////////// TO-DO //////////////////////////////
    /// Some implementations of a singly linked list maintain the size (number of elements in the list).  std::forward_list does
    /// not. The size of singly linked list must be calculated on demand by walking the list from beginning to end counting the
    /// number of elements visited.  The STL's std::distance() function does that, or you can write your own loop.
    // std::size_t count = 0;

    // for(auto element : _groceries_sl_list) {
    //     count++;
    // }

    // return count;

    return std::distance(_groceries_sl_list.begin(), _groceries_sl_list.end());
    

  /////////////////////// END-TO-DO ////////////////////////////
}



bool GroceryList::containersAreConsistant() const
{
  // Sizes of all containers must be equal to each other
  if(    _groceries_array_size != _groceries_vector.size()
      || _groceries_array_size != _groceries_dl_list.size()
      || _groceries_array_size !=  groceries_sl_list_size() ) return false;

  // Element content and order must be equal to each other
  auto current_array_position   = _groceries_array  .cbegin();
  auto current_vector_position  = _groceries_vector .cbegin();
  auto current_dl_list_position = _groceries_dl_list.cbegin();
  auto current_sl_list_position = _groceries_sl_list.cbegin();

  while( current_vector_position != _groceries_vector.cend() )
  {
    if(    *current_array_position != *current_vector_position
        || *current_array_position != *current_dl_list_position
        || *current_array_position != *current_sl_list_position ) return false;

    // Advance the iterators to the next element in unison
    ++current_array_position;
    ++current_vector_position;
    ++current_dl_list_position;
    ++current_sl_list_position;
  }

  return true;
}












/*******************************************************************************
**  Constructors, destructor, and assignment operators
*******************************************************************************/
GroceryList::GroceryList()                                        = default;

GroceryList::GroceryList( const GroceryList  & )                  = default;
GroceryList::GroceryList(       GroceryList && )                  = default;

GroceryList & GroceryList::operator=( GroceryList    rhs )        { swap( rhs ); return *this; }
GroceryList & GroceryList::operator=( GroceryList &&     )        = default;

GroceryList::~GroceryList()                                       = default;



GroceryList::GroceryList( const std::initializer_list<GroceryItem> & initList )
  : _groceries_vector ( initList.begin(), initList.end() ),
    _groceries_dl_list( initList.begin(), initList.end() ),
    _groceries_sl_list( initList.begin(), initList.end() )
{
  // Unlike the other containers that are expendable, the array has a fixed capacity N.  Copy only the first N elements of the
  // initialization list into the array.
  for( auto p = initList.begin();  _groceries_array_size < _groceries_array.size()  &&  p != initList.end();   ++_groceries_array_size, ++p)
  {
    _groceries_array[_groceries_array_size] = std::move( *p );
  }
}



GroceryList & GroceryList::operator+=( const std::initializer_list<GroceryItem> & rhs )
{
  ///////////////////////// TO-DO //////////////////////////////
    /// Concatenate the right hand side grocery list of grocery items to this list by repeatedly inserting at the bottom of this
    /// grocery list.  The input type is a container of grocery items accessible with iterators like all the other containers.  The
    /// constructor above gives an example.  Use GroceryList::insert() to insert at the bottom.

  /////////////////////// END-TO-DO ////////////////////////////

  // Verify the internal grocery list state is still consistent amongst the four containers
  if( !containersAreConsistant() ) throw GroceryList::InvalidInternalState_Ex( "Container consistency error" exception_location );
  return *this;
}



GroceryList & GroceryList::operator+=( const GroceryList & rhs )
{
  ///////////////////////// TO-DO //////////////////////////////
    /// Concatenate the right hand side grocery list of grocery items to this list by repeatedly inserting at the bottom of this
    /// grocery list.  All the rhs containers (array, vector, list, and forward_list) contain the same information, so pick just one
    /// to traverse.  Walk the container you picked inserting its grocery items to the bottom of this grocery list. Use
    /// GroceryList::insert() to insert at the bottom.

  /////////////////////// END-TO-DO ////////////////////////////

  // Verify the internal grocery list state is still consistent amongst the four containers
  if( !containersAreConsistant() ) throw GroceryList::InvalidInternalState_Ex( "Container consistency error" exception_location );
  return *this;
}







/*******************************************************************************
**  Queries
*******************************************************************************/
std::size_t GroceryList::size() const
{
  // Verify the internal grocery list state is still consistent amongst the four containers
  if( !containersAreConsistant() ) throw GroceryList::InvalidInternalState_Ex( "Container consistency error" exception_location );

  // All the containers are the same size, so pick one and return the size of that.  Since the forward_list has to calculate the size
  // on demand, stay away from using that one.
  return _groceries_vector.size();
}



std::size_t GroceryList::find( const GroceryItem & item ) const
{
  // Verify the internal grocery list state is still consistent amongst the four containers
  if( !containersAreConsistant() ) throw GroceryList::InvalidInternalState_Ex( "Container consistency error" exception_location );

  ///////////////////////// TO-DO //////////////////////////////
    /// Locate the grocery item in this grocery list and return the zero-based position of that item.  If the item does not exist,
    /// return the size of this grocery list as an indicator the grocery item does not exist.  The grocery item will be in the same
    /// position in all the containers (array, vector, list, and forward_list) so pick just one of those to search.  The STL
    /// provides the find() function that is a perfect fit here, but you may also write your own loop.

  /////////////////////// END-TO-DO ////////////////////////////
}












/*******************************************************************************
**  Mutators
*******************************************************************************/
void GroceryList::insert( const GroceryItem & item, Position position )
{
  // Convert the TOP and BOTTOM enumerations to an offset and delegate the work
  if     ( position == Position::TOP    )  insert( item, 0      );
  else if( position == Position::BOTTOM )  insert( item, size() );
  else throw std::logic_error( "Unexpected insertion position" exception_location );  // Programmer error.  Should never hit this!
}



void GroceryList::insert( const GroceryItem & item, std::size_t offsetFromTop )       // insert new item at offsetFromTop, which places it before the current item at offsetFromTop
{
  // Inserting into the grocery list means you insert the grocery item into each of the containers (array, vector, list, and
  // forward_list).  Because the data structure concept is different for each container, the way an item gets inserted is a little
  // different for each.  You are to insert the grocery item into each container such that the ordering of all the containers is the
  // same.  A check is made at the end of this function to verify the contents of all four containers are indeed the same.


  /**********  Insert into array  ***********************/
  {
    ///////////////////////// TO-DO //////////////////////////////
      /// Unlike the other containers, std::array has no insert() function, so you have to write it yourself. Insert into the array
      /// by shifting all the items at and after the insertion point (offestFromTop) to the right opening a gap in the array that
      /// can be populated with the given grocery item.  Remember that arrays have fixed capacity and cannot grow, so make sure
      /// there is room in the array for another item before you start by verifying _groceries_array_size is less than
      /// _groceries_array.size().  If not, throw CapacityExceeded_ex.  Also remember that you must keep track of the number of
      /// valid grocery items in your array, so don't forget to adjust _groceries_array_size.
      ///
      /// open a hole to insert new item by shifting to the right everything at and after the insertion point.
      /// For example:  a[8] = a[7];  a[7] = a[6];  a[6] = a[5];  and so on.
      /// std::move_backward will be helpful, or write your own loop.
      ///
      /// See function FixedVector::insert() in FixedVector.hpp in our Sequence Container Implementation Examples, and
      /// RationalArray::insert() in RationalArray.cpp in our Rational Number Case Study examples.

    /////////////////////// END-TO-DO ////////////////////////////
  }



  /**********  Insert into vector  **********************/
  {
    ///////////////////////// TO-DO //////////////////////////////
      /// The vector STL container std::vector has an insert function, which can be directly used here.  But that function takes a
      /// pointer (or more accurately, an iterator) that points to the item to insert before.  You need to convert the zero-based
      /// offset from the top to an iterator by advancing _groceries_vector.begin() offsetFromTop times.  The STL has a function
      /// called std::next() that does that, or you can use simple pointer arithmetic to calculate it.
      ///
      /// Behind the scenes, std::vector::insert() shifts to the right everything at and after the insertion point, just like you
      /// did for the array above.

    /////////////////////// END-TO-DO ////////////////////////////
  }



  /**********  Insert into doubly linked list  **********/
  {
    ///////////////////////// TO-DO //////////////////////////////
      /// The doubly linked list STL container std::list has an insert function, which can be directly used here.  But that function
      /// takes a pointer (or more accurately, an iterator) that points to the item to insert before.  You need to convert the
      /// zero-based offset from the top to an iterator by advancing _groceries_dl_list.begin() offsetFromTop times.  The STL has a
      /// function called std::next() that does that, or you can write your own loop.

    /////////////////////// END-TO-DO ////////////////////////////
  }



  /**********  Insert into singly linked list  **********/
  {
    ///////////////////////// TO-DO //////////////////////////////
      /// The singly linked list STL container std::forward_list has an insert function, which can be directly used here.  But that
      /// function inserts AFTER the item pointed to, not before like the other containers.  A singly linked list cannot look
      /// backwards, only forward.  You need to convert the zero-based offset from the top to an iterator by advancing
      /// _groceries_sl_list.before_begin() offsetFromTop times.  The STL has a function called std::next() that does that, or you
      /// can write your own loop.

    /////////////////////// END-TO-DO ////////////////////////////
  }

  // Verify the internal grocery list state is still consistent amongst the four containers
  if( !containersAreConsistant() ) throw GroceryList::InvalidInternalState_Ex( "Container consistency error" exception_location );
}



void GroceryList::remove( const GroceryItem & item )
{
  remove( find( item ) );
}



void GroceryList::remove( std::size_t offsetFromTop )
{
  // Removing from the grocery list means you remove the grocery item from each of the containers (array, vector, list, and
  // forward_list).  Because the data structure concept is different for each container, the way an item gets removed is a little
  // different for each.  You are to remove the grocery item from each container such that the ordering of all the containers is the
  // same.  A check is made at the end of this function to verify the contents of all four containers are indeed the same.

  if( offsetFromTop >= size() ) return;                                               // no change occurs if (zero-based) offsetFromTop >= size()

  /**********  Remove from array  ***********************/
  {
    ///////////////////////// TO-DO //////////////////////////////
      /// Close the hole created by shifting to the left everything at and after the remove point.
      /// For example:  a[5] = a[6];  a[6] = a[7];  a[7] = a[8];  and so on
      ///
      /// std::move() will be helpful, or write your own loop.  Also remember that you must keep track of the number of valid
      /// grocery items in your array, so don't forget to adjust _groceries_array_size.
      ///
      /// See function FixedVector<T>::erase() in FixedVector.hpp in our Sequence Container Implementation Examples, and
      /// RationalArray::remove() in RationalArray.cpp in our Rational Number Case Study examples.

    std::move(_groceries_array.begin() + offsetFromTop + 1, _groceries_array.begin() + _groceries_array_size, _groceries_array.begin() + offsetFromTop);

    --_groceries_array_size;

    /////////////////////// END-TO-DO ////////////////////////////
  }



  /**********  Remove from vector  **********************/
  {
    ///////////////////////// TO-DO //////////////////////////////
      /// The vector STL container std::vector has an erase function, which can be directly used here.  But that function takes a
      /// pointer (or more accurately, an iterator) that points to the item to be removed.  You need to convert the zero-based
      /// offset from the top to an iterator by advancing _groceries_vector.begin() offsetFromTop times.  The STL has a function
      /// called std::next() that does that, or you can use simple pointer arithmetic to calculate it.
      ///
      /// Behind the scenes, std::vector::erase() shifts to the left everything after the insertion point, just like you
      /// did for the array above.

    _groceries_vector.erase(_groceries_vector.begin() + offsetFromTop);

    /////////////////////// END-TO-DO ////////////////////////////
  }



  /**********  Remove from doubly linked list  **********/
  {
    ///////////////////////// TO-DO //////////////////////////////
      /// The doubly linked list STL container std::list has an erase function, which can be directly used here.  But that function
      /// takes a pointer (or more accurately, an iterator) that points to the item to remove.  You need to convert the zero-based
      /// offset from the top to an iterator by advancing _groceries_dl_list.begin() offsetFromTop times.  The STL has a function
      /// called std::next() that does that, or you can write your own loop.

      _groceries_dl_list.erase(std::next(_groceries_dl_list.begin(), offsetFromTop));

    /////////////////////// END-TO-DO ////////////////////////////
  }



  /**********  Remove from singly linked list  **********/
  {
    ///////////////////////// TO-DO //////////////////////////////
      /// The singly linked list STL container std::forward_list has an erase function, which can be directly used here.  But that
      /// function erases AFTER the item pointed to, not the one pointed to like the other containers.  A singly linked list cannot
      /// look backwards, only forward.  You need to convert the zero-based offset from the top to an iterator by advancing
      /// _groceries_sl_list.before_begin() offsetFromTop times.  The STL has a function called std::next() that does that, or you
      /// can write your own loop.

      _groceries_sl_list.erase_after(std::next(_groceries_sl_list.begin(), offsetFromTop - 1));

    /////////////////////// END-TO-DO ////////////////////////////
  }

  // Verify the internal grocery list state is still consistent amongst the four containers
  if( !containersAreConsistant() ) throw GroceryList::InvalidInternalState_Ex( "Container consistency error" exception_location );
}



void GroceryList::moveToTop( const GroceryItem & item )
{
  ///////////////////////// TO-DO //////////////////////////////
    /// If the item exists, then remove and reinsert it.  Else do nothing.  Use GroceryList::find() to determine if the grocery item
    /// exists in this grocery list.

    // if the item does not exist, find will return the current size of GroceryList
    if (GroceryList::find(item) == GroceryList::size())
      return;
    
    // remove item from the list
    GroceryList::remove(item);

    // append item to beginning of the list
    GroceryList::insert(item, 1);

  /////////////////////// END-TO-DO ////////////////////////////
}



void GroceryList::swap( GroceryList & rhs ) noexcept
{
  _groceries_array  .swap( rhs._groceries_array   );
  _groceries_vector .swap( rhs._groceries_vector  );
  _groceries_dl_list.swap( rhs._groceries_dl_list );
  _groceries_sl_list.swap( rhs._groceries_sl_list );

  std::swap( _groceries_array_size, rhs._groceries_array_size );
}












/*******************************************************************************
**  Insertion and Extraction Operators
*******************************************************************************/
std::ostream & operator<<( std::ostream & stream, const GroceryList & groceryList )
{
  if( !groceryList.containersAreConsistant() ) throw GroceryList::InvalidInternalState_Ex( "Container consistency error" exception_location );

  unsigned count = 0;
  for( const auto & item : groceryList._groceries_sl_list )   stream << std::setw(5) << count++ << ":  " << item;

  return stream;
}



std::istream & operator>>( std::istream & stream, GroceryList & groceryList )
{
  if( !groceryList.containersAreConsistant() ) throw GroceryList::InvalidInternalState_Ex( "Container consistency error" exception_location );

  for( GroceryItem item; stream >> item; );

  return stream;
}












/*******************************************************************************
**  Logical Operators
*******************************************************************************/
bool operator==( const GroceryList & lhs, const GroceryList & rhs )
{
  return !( lhs < rhs )  &&  !( rhs < lhs );
}



bool operator<( const GroceryList & lhs, const GroceryList & rhs )
{
  if( !lhs.containersAreConsistant() || !rhs.containersAreConsistant() ) throw GroceryList::InvalidInternalState_Ex( "Container consistency error" exception_location );

  // comparing arrays using std::array::operator==() will compare every element in the array (which is usually what you want).  But
  // in this case, only the first N elements are valid, so compare only those elements.  This is implicitly handled in the other
  // containers because size() and end() are already adjusted for only the valid elements.
  auto begin_lhs = lhs._groceries_array.cbegin();
  auto begin_rhs = rhs._groceries_array.cbegin();

  auto end_lhs   = begin_lhs + lhs._groceries_array_size;
  auto end_rhs   = begin_rhs + rhs._groceries_array_size;

  // C++20's spaceship operator should optimize this algorithm, but for now ...
  if     ( !std::equal( begin_lhs, end_lhs, begin_rhs, end_rhs ) )  return std::lexicographical_compare ( begin_lhs, end_lhs, begin_rhs, end_rhs );
  else if( lhs._groceries_vector  != rhs._groceries_vector       )  return lhs._groceries_vector  < rhs._groceries_vector;
  else if( lhs._groceries_dl_list != rhs._groceries_dl_list      )  return lhs._groceries_dl_list < rhs._groceries_dl_list;
  else if( lhs._groceries_sl_list != rhs._groceries_sl_list      )  return lhs._groceries_sl_list < rhs._groceries_sl_list;

  // At this point, all attributes are equal to each other, so the lhs cannot be less than the rhs
  return false;
}

bool operator!=( const GroceryList & lhs, const GroceryList & rhs ) { return !( lhs == rhs ); }
bool operator<=( const GroceryList & lhs, const GroceryList & rhs ) { return !( rhs  < lhs ); }
bool operator> ( const GroceryList & lhs, const GroceryList & rhs ) { return  ( rhs  < lhs ); }
bool operator>=( const GroceryList & lhs, const GroceryList & rhs ) { return !( lhs  < rhs ); }
