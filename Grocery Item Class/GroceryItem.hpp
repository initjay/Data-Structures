// Grocery Item Class
// James Talavera
// 9/10

#pragma once

#include <string>

class GroceryItem {
	// comparison operators
	friend bool operator==(const GroceryItem & lhs, const GroceryItem & rhs);
	friend bool operator<(const GroceryItem & lhs, const GroceryItem & rhs);
	
	// insertion and extraction operators
	friend std::istream & operator>>(std::istream & stream, GroceryItem & GI);
	friend std::ostream & operator<<(std::ostream & stream, const GroceryItem & GI);

	public:

		// constructors
		GroceryItem() = default;
		GroceryItem(const std::string productName,
					const std::string brandName = {},
					const std::string UPC = {},
					double price = 0.0);

		// Queries (const since they should not modify attributes)
		std::string UPC() const;
		std::string brandName() const;
		std::string productName() const;
		double price() const;

		// Mutators
		void UPC(const std::string newUPC);
		void brandName(const std::string newBrandName );
		void productName(const std::string newProductName);
		void price(const double newPrice);


		
	private:
    	std::string _UPC, _brandName, _productName;
    	double _price = 0.0;
		
};

// comparison operators
bool operator==(const GroceryItem & lhs, const GroceryItem & rhs);
bool operator<(const GroceryItem & lhs, const GroceryItem & rhs);

bool operator!=(const GroceryItem & lhs, const GroceryItem & rhs);
bool operator<=(const GroceryItem & lhs, const GroceryItem & rhs);
bool operator>(const GroceryItem & lhs, const GroceryItem & rhs);
bool operator>=(const GroceryItem & lhs, const GroceryItem & rhs);
