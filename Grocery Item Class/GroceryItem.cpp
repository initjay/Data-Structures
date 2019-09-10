// GroceryItem class implementation
// James Talavera
// September 2019

#include "GroceryItem.hpp"
#include <string>
#include <iostream>
#include <cmath>
#include <iomanip>

const double EPSILON = 0.001;

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

// comparison functions
bool operator==(const GroceryItem & lhs, const GroceryItem& rhs) {
    
    return lhs._UPC == rhs._UPC
    && lhs._brandName == rhs._brandName
    && lhs._productName == rhs._productName
    && abs(lhs._price - rhs._price) < EPSILON;
}

bool operator!=(const GroceryItem & lhs, const GroceryItem& rhs) {
    return !(lhs == rhs);
}

bool operator<(const GroceryItem & lhs, const GroceryItem & rhs) {
    if(lhs._UPC != rhs._UPC) 
        return lhs._UPC < rhs._UPC;
    else if (lhs._brandName != rhs._brandName) 
        return lhs._brandName < rhs._brandName;
    else if (lhs._productName != rhs._productName)
        return lhs._productName < rhs._productName;
    else if (!(abs(lhs._price - rhs._price) < EPSILON))
        return lhs._price < rhs._price;
    else 
        return false;
}

bool operator<=(const GroceryItem & lhs, const GroceryItem& rhs) {
    return lhs == rhs || lhs < rhs;
}

bool operator>(const GroceryItem & lhs, const GroceryItem& rhs) {
    return !(lhs == rhs) && !(lhs < rhs);
}

bool operator>=(const GroceryItem & lhs, const GroceryItem& rhs) {
    return lhs == rhs || rhs < lhs;
}

// extraction function
std::istream & operator>>(std::istream & stream, GroceryItem & GI) {
    
    stream >> std::quoted(GI._UPC) >> std::quoted(GI._brandName) 
    >> std::quoted(GI._productName) >> GI._price;

    return stream;

}

// insertion function
std::ostream & operator<<(std::ostream & stream, const GroceryItem & GI) {
    stream << "\"" << GI._UPC << "\" " << "\"" << GI._brandName << "\" " 
            << "\"" << GI._productName << "\" " << "$" << GI._price << "\n";
    
    return stream;
}




