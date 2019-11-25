#include <exception>
#include <iomanip>      // setprecision()
#include <iostream>     // cout, cerr, fixed(), showpoint()
#include <stdexcept>    // runtime_error
#include <string>       // string, to_string(), string_literals

#include "GroceryItem.hpp"
#include "GroceryItemDatabase.hpp"
#include "functions.hpp"


namespace // anonymous
{
  struct FailedTest : std::runtime_error {using runtime_error::runtime_error;};

  ShoppingCarts makeShoppingCarts();
  void          test_1();
  void          test_2( const Inventory_DB & inventory );
  void          test_3( const Inventory_DB & inventory );
  void          test_4( const Inventory_DB & inventory );
}





int main()
{
  try
  {
    std::cout << std::fixed << std::setprecision( 2 ) << std::showpoint;
    test_1();


    // Initialize our starting point by creating a bunch of shopping carts, each full of groceries waiting to check out.
    auto shoppingCarts = makeShoppingCarts();

    // Load in the current inventory for this store.  The store doesn't carry everything, especially all at once.  The inventory tells
    // us how many of each item are currently in stock.
    auto inventory = loadInventory();
    test_2( inventory );


    // There are several customers standing in line waiting to pay for the items in their baskets.  Process them all by scanning all
    // the items in the basket, printing a receipt with an amount due, and deducting the items bought from the store's inventory.
    processCustomerShoppingCarts( shoppingCarts, inventory );
    test_3( inventory );

    // All the shoppers have checkout out and it's late in the day.  Let's close the store, take inventory, and if we
    // sold enough items to fall below our re-order threshold, order some more.
    std::cout << "\n\n\n";

    // For all the items sold today, if the quantity on hand has fallen below a re-order threshold, reorder more of those items.
    reorderItems( shoppingCarts, inventory );
    test_4( inventory );

    std::cout << "\n\nTESTS PASSED\n";
  }

  catch( const FailedTest & ex )
  {
    std::cerr << "TEST FAILURE:  " << ex.what() << '\n';
  }

  catch( const std::exception & ex )
  {
    std::cerr << "FAILED - Unhandled exception:\n"  << ex.what() << '\n';
  }

  return 0;
}




















namespace  // anonymous
{
  ShoppingCarts makeShoppingCarts()
  {
    // Our store has many customers, and each (identified by name) is pushing a shopping cart. Shopping carts are structured as
    // trees of trees of grocery items.
    ShoppingCarts carts =
    {
      // first shopping cart
      { "Red Baron",        { {"00075457129000", {"milk"     }}, {"00038000291210", {"rice krispies"}}, {"00025317533003", {"hotdogs"}},
                              {"09073649000493", {"apple pie"}}, {"00835841005255", {"bread"        }}, {"00688267039317", {"eggs"   }}
                            }
      },

      // second shopping cart
      { "Peppermint Patty", { {"00813608012401", {"Cheese"      }}, {"00037466065908", {"Truffles"      }}, {"00631723300704", {"Pepperoncini"}},
                              {"00051500280645", {"Pancake Mix" }}, {"00792851355155", {"Soup"          }}, {"00898425001333", {"Sandwich"    }},
                              {"00021908501871", {"Potato Spuds"}}, {"00856414001092", {"Plantain Chips"}}, {"00036192122930", {"Applesauce"  }},
                              {"00763795931415", {"Paper Plates"}}, {"00070596000647", {"Soap"          }}, {"00079400266200", {"Deodorant"   }}
                            }
      },

      // third shopping cart
      { "Woodstock",        { {"00859013004327", {"Mint Tea"         }}, {"00041331092609", {"Spanish Omelet"}}, {"00217039300005", {"Fillet Steak"   }},
                              {"00636874220338", {"Face Exfoliate"   }}, {"00688267138973", {"Green Tea"     }}, {"00033674100066", {"Forskohlii"     }},
                              {"00891475001421", {"Candy Fruit Chews"}}, {"00688267133442", {"Coffee"        }}, {"00021000778690", {"Cheesy Potatoes"}},
                              {"00071758100823", {"Pepper"           }}, {"00041520010667", {"Mouth Wash"    }}, {"00216079600007", {"Lamb Chops"     }},
                              {"00790555051526", {"Black Beans"      }}, {"00070177862640", {"Tea Sampler"   }}, {"00018000001958", {"Cinnamon Rolls" }}
                            }
      },

      // forth shopping cart
      { "Schroeder",        { {"00072591002251", {"Peanut Butter"}}, {"00219019100001", {"Ground Beef"           }}, {"00890692002020", {"Stretch Cream" }},
                              {"00637876981630", {"Mozzarella"   }}, {"00716237183507", {"Facial Towelettes"     }}, {"00886911000052", {"Pastry Popover"}},
                              {"00084783499008", {"Massage Oil"  }}, {"00016055456747", {"Children's Fruit Drink"}}, {"00021908743325", {"Granola Cereal"}}
                            }
      },

      // fifth shopping cart
      { "Lucy van Pelt",    { {"00070327012116", {"Pineapple"     }}, {"00073377801839", {"Sleep Mask Blue"}}, {"00030768009670", {"Calcium Softgels"}},
                              {"00852697001422", {"Baby Food"     }}, {"00079471102414", {"Manzanillo"     }}, {"00072736013753", {"Dressing"        }},
                              {"00216210900003", {"Cheddar Cheese"}}, {"00780872310185", {"Dog Food"       }}, {"00710069086036", {"Crackers"        }},
                              {"00092657016985", {"Tea",          }}, {"00086449903065", {"Deodorant"      }}, {"00885229000198", {"Drinks"          }}
                            }
      },

      // sixth shopping cart
      { "Charlie Brown",    { {"00611508524006", {"Lump Of Coal"}}
                            }
      }
    };

    return carts;
  }  // makeShoppingCarts






  void test_1()
  {
    GroceryItemDatabase & storeDataBase = GroceryItemDatabase::instance();

    // verify an item known to be in the database can be found
    if( auto item = storeDataBase.find( "00312843555419" );
             item == nullptr  ||  *item != GroceryItem( "Bayer Asprin Plus Extra Strength 500mg - 50 Ct",
                                                        "Bayer",
                                                        "00312843555419",
                                                        19.41 ) )
    {  throw FailedTest( "Grocery Database item \"00312843555419\" lookup failure" ); }


    // verify an item known to not be in the database isn't found
    if( auto item = storeDataBase.find( "--------------" );
             item != nullptr )
    { throw FailedTest( "Nonexistent Grocery Item lookup failure" ); }
  }






  void validate( const Inventory_DB & inventory, const Inventory_DB & pairs )
  {
    std::string message;
    for( const auto & [upc, expected] : pairs ) if( inventory.at( upc ) != expected )
    {
        message += "\nInventory item \"" + upc + "\" quantity failure"
                   + "\n   Expected: " + std::to_string( expected )
                   + "\n   Actual:   " + std::to_string( inventory.at( upc ) );
    }

    if( ! message.empty() ) throw FailedTest(message);
  }






  using namespace std::string_literals;

  void test_2( const Inventory_DB & inventory )
  {
    if( auto expected = 104'361ULL; inventory.size() != expected )
    {
      throw FailedTest(   "Opening inventory database quantity failure"s
                        + "\nExpected: "s + std::to_string( expected )
                        + "\nActual:   "s + std::to_string( inventory.size() ) );
    }

    validate( inventory,
              { // "Red Baron"
                {"00075457129000", 10}, {"00038000291210", 23}, {"00025317533003",  9}, //{"09073649000493",  5},
                {"00835841005255", 27}, {"00688267039317", 33},

                // Peppermint Patty
                {"00813608012401", 36}, {"00037466065908", 23}, {"00631723300704", 31}, {"00051500280645", 19},
                {"00792851355155", 31}, {"00898425001333", 52}, {"00021908501871", 21}, {"00856414001092", 40},
                {"00036192122930", 39}, {"00763795931415", 12}, {"00070596000647", 13}, {"00079400266200", 16},

                // Woodstock
                {"00859013004327", 49}, {"00041331092609",  9}, {"00217039300005", 27}, {"00636874220338", 27},
                {"00688267138973", 11}, {"00033674100066", 20}, {"00891475001421", 21}, {"00688267133442",  9},
                {"00021000778690", 30}, {"00071758100823", 26}, {"00041520010667", 24}, {"00216079600007", 49},
                {"00790555051526", 38}, {"00070177862640", 35}, {"00018000001958", 21},

                // Schroeder
                {"00072591002251", 12}, {"00219019100001", 14}, {"00890692002020", 42}, {"00637876981630", 47},
                {"00716237183507", 50}, {"00886911000052", 53}, {"00084783499008", 49}, {"00016055456747", 44},
                {"00021908743325", 39},

                // Lucy van Pelt
                {"00070327012116", 45}, {"00073377801839", 13}, {"00030768009670", 17}, {"00852697001422", 51},
                {"00079471102414", 31}, {"00072736013753", 38}, {"00216210900003", 50}, {"00780872310185", 27},
                {"00710069086036", 46}, {"00092657016985", 46}, {"00086449903065", 45}, {"00885229000198", 17},

                // Charlie Brown
               {"00611508524006", 28}
              } );
  }






  void test_3( const Inventory_DB & inventory )
  {
    if( auto expected = 104'361ULL; inventory.size() != expected )
    {
      throw FailedTest(   "Closing inventory database quantity failure"s
                        + "\nExpected: "s + std::to_string( expected )
                        + "\nActual:   "s + std::to_string( inventory.size() ) );
    }

    validate( inventory,
              { // "Red Baron"
                {"00075457129000",  9}, {"00038000291210", 22}, {"00025317533003",  8}, //{"09073649000493",  5},
                {"00835841005255", 26}, {"00688267039317", 32},

                // Peppermint Patty
                {"00813608012401", 35}, {"00037466065908", 22}, {"00631723300704", 30}, {"00051500280645", 18},
                {"00792851355155", 30}, {"00898425001333", 51}, {"00021908501871", 20}, {"00856414001092", 39},
                {"00036192122930", 38}, {"00763795931415", 11}, {"00070596000647", 12}, {"00079400266200", 15},

                // Woodstock
                {"00859013004327", 48}, {"00041331092609",  8}, {"00217039300005", 26}, {"00636874220338", 26},
                {"00688267138973", 10}, {"00033674100066", 19}, {"00891475001421", 20}, {"00688267133442",  8},
                {"00021000778690", 29}, {"00071758100823", 25}, {"00041520010667", 23}, {"00216079600007", 48},
                {"00790555051526", 37}, {"00070177862640", 34}, {"00018000001958", 20},

                // Schroeder
                {"00072591002251", 11}, {"00219019100001", 13}, {"00890692002020", 41}, {"00637876981630", 46},
                {"00716237183507", 49}, {"00886911000052", 52}, {"00084783499008", 48}, {"00016055456747", 43},
                {"00021908743325", 38},

                // Lucy van Pelt
                {"00070327012116", 44}, {"00073377801839", 12}, {"00030768009670", 16}, {"00852697001422", 50},
                {"00079471102414", 30}, {"00072736013753", 37}, {"00216210900003", 49}, {"00780872310185", 26},
                {"00710069086036", 45}, {"00092657016985", 45}, {"00086449903065", 44}, {"00885229000198", 16},

                // Charlie Brown
               {"00611508524006", 27}
              } );
  }






  void test_4( const Inventory_DB & inventory )
  {
    if( auto expected = 104'361ULL; inventory.size() != expected )
    {
      throw FailedTest(   "Reorder inventory database quantity failure"s
                        + "\nExpected: "s + std::to_string( expected )
                        + "\nActual:   "s + std::to_string( inventory.size() ) );
    }

    validate( inventory,
              { // "Red Baron"
                {"00075457129000", 29}, {"00038000291210", 22}, {"00025317533003", 28}, //{"09073649000493",  5},
                {"00835841005255", 26}, {"00688267039317", 32},

                // Peppermint Patty
                {"00813608012401", 35}, {"00037466065908", 22}, {"00631723300704", 30}, {"00051500280645", 18},
                {"00792851355155", 30}, {"00898425001333", 51}, {"00021908501871", 20}, {"00856414001092", 39},
                {"00036192122930", 38}, {"00763795931415", 31}, {"00070596000647", 32}, {"00079400266200", 15},

                // Woodstock
                {"00859013004327", 48}, {"00041331092609", 28}, {"00217039300005", 26}, {"00636874220338", 26},
                {"00688267138973", 30}, {"00033674100066", 19}, {"00891475001421", 20}, {"00688267133442", 28},
                {"00021000778690", 29}, {"00071758100823", 25}, {"00041520010667", 23}, {"00216079600007", 48},
                {"00790555051526", 37}, {"00070177862640", 34}, {"00018000001958", 20},

                // Schroeder
                {"00072591002251", 31}, {"00219019100001", 33}, {"00890692002020", 41}, {"00637876981630", 46},
                {"00716237183507", 49}, {"00886911000052", 52}, {"00084783499008", 48}, {"00016055456747", 43},
                {"00021908743325", 38},

                // Lucy van Pelt
                {"00070327012116", 44}, {"00073377801839", 32}, {"00030768009670", 16}, {"00852697001422", 50},
                {"00079471102414", 30}, {"00072736013753", 37}, {"00216210900003", 49}, {"00780872310185", 26},
                {"00710069086036", 45}, {"00092657016985", 45}, {"00086449903065", 44}, {"00885229000198", 16},

                // Charlie Brown
               {"00611508524006", 27}
              } );
  }
} // anonymous
