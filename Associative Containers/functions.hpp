#pragma once

#include <map>
#include <string>

#include "GroceryItem.hpp"

//-----------------+--------------------------------+-------------------------------------------
//                 |  Key                           |   Value
//-----------------+--------------------------------+-------------------------------------------
using Inventory_DB  = std::map<std::string /*UPC*/,     unsigned int /*quantity*/>;          // Maintains of the quantity of items identified by UPC
using ShoppingCart  = std::map<std::string /*UPC*/,     GroceryItem>;                        // An individual shopping cart is filled with groceries
using ShoppingCarts = std::map<std::string /*name*/,    ShoppingCart>;                       // Many customers, identified by name, each pushing a shopping cart
                                                                                             // Food for thought (pun intended): Could this/should this be a
                                                                                             // multi_map instead?  Why, or why not?



Inventory_DB loadInventory();
void         processCustomerShoppingCarts( ShoppingCarts const & shoppingCarts, Inventory_DB & inventory );
void         reorderItems                ( ShoppingCarts const & shoppingCarts, Inventory_DB & inventory );
