// Grocery Item Class
// James Talavera
// September 2019

#pragma once

#include <string>

class GroceryItem {

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