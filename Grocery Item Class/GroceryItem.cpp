// GroceryItem class implementation
// James Talavera
// September 2019

#include "GroceryItem.hpp"
#include <string>
#include <iostream>

// setter functions
void GroceryItem::UPC(const std::string newUPC) { _UPC = newUPC; }
void GroceryItem::brandName(const std::string newBrandName ) { _brandName = newBrandName; }
void GroceryItem::productName(const std::string newProductName) { _productName = newProductName; }
void GroceryItem::price(const double newPrice) { _price = newPrice; }

// getter functions
std::string GroceryItem::UPC() { return _UPC; }
std::string GroceryItem::brandName() { return _brandName; }
std::string GroceryItem::productName() { return _productName; }
double GroceryItem::price() { return _price; }




