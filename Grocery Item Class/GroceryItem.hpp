// Grocery Item Class
// James Talavera
// 9/10

#pragma once

#include <string>

class GroceryItem {
	// comparison operators
	friend bool operator==(const GroceryItem & lhs, const GroceryItem & rhs);
	friend bool operator<(const GroceryItem & lhs, const GroceryItem & rhs);
	friend bool operator!=(const GroceryItem & lhs, const GroceryItem & rhs);
	friend bool operator<=(const GroceryItem & lhs, const GroceryItem & rhs);
	friend bool operator>(const GroceryItem & lhs, const GroceryItem & rhs);
	friend bool operator>=(const GroceryItem & lhs, const GroceryItem & rhs);
	
	// insertion and extraction operators
	friend std::istream & operator>>(std::istream & stream, GroceryItem & GI);
	friend std::ostream & operator<<(std::ostream & stream, const GroceryItem & GI);

	public:
		std::string UPC();

		void UPC(const std::string newUPC);

		std::string brandName();

		void brandName(const std::string newBrandName );

		std::string productName();

		void productName(const std::string newProductName);

		double price();

		void price(const double newPrice);

		GroceryItem(std::string UPC = "", 
					std::string brandName = {},
					std::string productName = {},
					double price = 0.0)
					: _UPC(UPC),
					_brandName(brandName),
					_productName(productName),
					_price(price) {}
		
	private:
    	std::string _UPC, _brandName, _productName;

    	double _price;
		
};