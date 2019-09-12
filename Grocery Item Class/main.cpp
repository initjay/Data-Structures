// main file
// James Talavera
// 9/10

#include<iostream>
#include<iomanip>
#include"GroceryItem.hpp"
#include<vector>

int main() {
    std::cout << std::showpoint << std::fixed << std::setprecision(2)
              << "Welcome to Fresh&Breazy! Place grovery items into."; 
              // FINISH THIS^^

    std::vector<GroceryItem*> myGroceries;

    std::cout << "\nEnter a UPC, Brand Name, Product Name, and Price "
            << "separated by spaces.\n If an entry has a space surround it with quotes. "
            << "When you are done adding items, quit "
            << "with CTL-D.\n";

    while(true){

        GroceryItem *tempGrocery = new GroceryItem;

        std::cin >> *tempGrocery;

        if(std::cin.eof()) {
            delete tempGrocery;
            break;
        }
        
        myGroceries.push_back(tempGrocery);

    } 

    std::cout << "\nYou entered:\n";

    for(auto item : myGroceries) {
        std::cout << *item;
    }

    std::cout << "\n\nItems:\n";

    //print contents of vector in reverse
    for(auto item = myGroceries.crbegin(); item != myGroceries.crend(); item++) {
        std::cout << **item;
    }
    
    //release memory
    while(!myGroceries.empty()){
        delete myGroceries.back();
        myGroceries.pop_back();
    }


    return 0;
}