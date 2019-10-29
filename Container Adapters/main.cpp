#include <cmath>       // abs()
#include <cstddef>     // size_t
#include <exception>
#include <iomanip>     // setprecision()
#include <iostream>    // cerr
#include <queue>
#include <stack>
#include <string>

#include "GroceryItem.hpp"
#include "GroceryItemDatabase.hpp"


namespace
{
  /*********************************************************************************************************************************
  ** A recursive algorithm to carefully move grocery items from the broken cart to a working cart is given as follows:
  ** START
  ** Procedure carefully_move_grocery_items (number_of_items_to_be_moved, broken_cart, working_cart, spare_cart)
  **
  **    IF number_of_items_to_be_moved == 1, THEN
  **       move top item from broken_cart to working_cart
  **
  **    ELSE
  **       carefully_move_grocery_items (number_of_items_to_be_moved-1, broken_cart, spare_cart, working_cart)
  **       move top item from broken_cart to working_cart
  **       carefully_move_grocery_items (number_of_items_to_be_moved-1, spare_cart, working_cart, broken_cart)
  **
  **    END IF
  **
  ** END Procedure
  ** STOP
  *********************************************************************************************************************************/
  void carefully_move_grocery_items( std::size_t quantity, std::stack<GroceryItem> & sourceCart, std::stack<GroceryItem> & destinationCart, std::stack<GroceryItem> & spareCart )
  {
    ///////////////////////// TO-DO //////////////////////////////
      /// Implement the algorithm above.
      if (quantity == 1) {
        destinationCart.push(sourceCart.top());
        sourceCart.pop();
        return;
      }

      carefully_move_grocery_items(quantity - 1, sourceCart, spareCart, destinationCart);
      destinationCart.push(sourceCart.top());
      sourceCart.pop();
      carefully_move_grocery_items(quantity - 1, spareCart, destinationCart, sourceCart);
    /////////////////////// END-TO-DO ////////////////////////////
  }




  void carefully_move_grocery_items( std::stack<GroceryItem> & brokenCart, std::stack<GroceryItem> & workingCart )
  {
    ///////////////////////// TO-DO //////////////////////////////
      /// Implement the starter function for the above algorithm.  If the broken cart contains grocery items, move those grocery items
      /// to the working cart while ensuring the breakable items are always on top of the nonbreakable items, just like they already
      /// are in the broken cart.  That is, call the above carefully_move_grocery_items function to start moving items recursively.

    /////////////////////// END-TO-DO ////////////////////////////
  }




  struct testItemLookup
  {
    testItemLookup()
    {
      try
      {
        GroceryItemDatabase & storeDataBase = GroceryItemDatabase::instance();

        if( auto item1 = storeDataBase.find( "00312843555419" ),  item2 = storeDataBase.find( "--------------" );
            item1 == nullptr  ||  *item1 != GroceryItem( "Bayer Asprin Plus Extra Strength 500mg - 50 Ct",
                                                         "Bayer",
                                                         "00312843555419",
                                                         19.41 )
            ||
            item2 != nullptr
        )
        {
          std::cerr << "Fail = Grocery Item lookup failure\n";
        }
      }

      catch (std::exception & ex)
      {
        std::cerr << "Fail = Grocery Item lookup failure\n"
                  << "       Unhandled exception " << ex.what();
      }
    }
  } runItemLookupTest;

}    // namespace






int main()
{
  // Snag an empty cart as I enter the grocery store
  ///////////////////////// TO-DO //////////////////////////////
    /// Create an empty shopping cart as a stack of grocery items and call it myCart.

  /////////////////////// END-TO-DO ////////////////////////////




  // Shop for awhile placing grocery items into my shopping cart
  ///////////////////////// TO-DO //////////////////////////////
    /// Put the following grocery items into your cart with the heaviest item on the bottom and the lightest item on the top
    /// according to the ordering given in the table below
    ///
    ///      UPC Code         Name             Brand
    ///      --------------   -------------    ---------------
    ///      00688267039317   eggs             any                     <=== lightest item, put this on the top so heavy items wont break them
    ///      00835841005255   bread            any
    ///      09073649000493   apple pie        any
    ///      00025317533003   hotdogs          Applegate Farms
    ///      00038000291210   rice krispies    Kellogg's
    ///      00075457129000   milk             any                     <===  heaviest item, put this on the bottom

  /////////////////////// END-TO-DO ////////////////////////////

  //auto testData = myCart; *******************remember to uncomment****************************




  // A wheel on my cart has just broken and I need to move items to a new cart that works
  ///////////////////////// TO-DO //////////////////////////////
    /// Create an empty shopping cart as a stack of grocery items and call it workingCart.  Then carefully move the items in your
    /// broken cart to this working cart by calling the above carefully_move_grocery_items function with two arguments.

  /////////////////////// END-TO-DO ////////////////////////////




  // Time to checkout and pay for all this stuff.  Find a checkout line and start placing items on the counter's conveyor belt
  ///////////////////////// TO-DO //////////////////////////////
    /// Create an empty checkout counter as a queue of grocery items and call it checkoutCounter.  Then remove the grocery items
    /// from your working cart and place them on the checkout counter, i.e., put them in this checkoutCounter queue.

  /////////////////////// END-TO-DO ////////////////////////////




  // Now add it all up and print a receipt
  double amountDue = 0.0;
  GroceryItemDatabase & storeDataBase = GroceryItemDatabase::instance();  // Get a reference to the store's grocery item database.
                                                                          // The database will contains a full description of the
                                                                          // item and the item's price.
  ///////////////////////// TO-DO //////////////////////////////
    /// For each item in the checkout counter queue, find the item by UPC code in the store's database.  If the item on the counter
    /// is found in the database then accumulate the amount due and print the item's full description and price (i.e. write the
    /// item's full description and price to standard output)

  /////////////////////// END-TO-DO ////////////////////////////




  std::cout << std::fixed << std::setprecision( 2 ) << std::showpoint
          << std::string( 25, '-' )  << '\n'
          << "Total  $" << amountDue << '\n';



  if( std::abs(amountDue - 68.32) < 1E-4 ) std::cerr << "PASS - Amount due matches expected\n";
  else                                     std::cerr << "FAIL - You're not paying the amount you should be paying\n";

  return 0;
}
