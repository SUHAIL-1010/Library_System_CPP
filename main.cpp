#include "Library.h"
#include <iostream>
#include <string>
#include <limits>

int main() {
    std::cout << "--- Sentinel Library Engine Booting ---\n";
    Library myLibrary;

    int choice;
    while (true) {
        std::cout << "\n=== MAIN MENU ===\n";
        std::cout << "1. Add Books / Update Quantity\n";
        std::cout << "2. Remove Books / Delete Record\n";
        std::cout << "3. Search Book\n";
        std::cout << "4. View All Available Books\n";
        std::cout << "5. Exit\n";
        std::cout << "Enter choice: ";
        
        if (!(std::cin >> choice)) {
            std::cout << "[Error] Invalid input. Please enter a number.\n";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }

        if (choice == 1) {
            int id, quantity;
            std::string title, author;
            
            std::cout << "Enter Book ID: ";
            if (!(std::cin >> id)) {
                std::cout << "[Error] ID must be a number.\n";
                std::cin.clear(); std::cin.ignore(10000, '\n'); continue;
            }
            
            std::cout << "Enter Quantity to Add: ";
            if (!(std::cin >> quantity)) {
                std::cout << "[Error] Quantity must be a number.\n";
                std::cin.clear(); std::cin.ignore(10000, '\n'); continue;
            }
            std::cin.ignore(10000, '\n'); 

            std::cout << "Enter Title: ";
            std::getline(std::cin, title);
            std::cout << "Enter Author: ";
            std::getline(std::cin, author);

            myLibrary.addBook(id, title, author, quantity);
        } 
        else if (choice == 2) {
            int id, quantity;
            std::cout << "Enter Book ID to remove: ";
            if (!(std::cin >> id)) { std::cin.clear(); std::cin.ignore(10000, '\n'); continue; }
            
            std::cout << "How many copies to remove? (Enter large number to delete completely): ";
            if (!(std::cin >> quantity)) { std::cin.clear(); std::cin.ignore(10000, '\n'); continue; }
            
            myLibrary.removeBook(id, quantity);
        }
        else if (choice == 3) {
            int id;
            std::cout << "Enter Book ID to search: ";
            if (!(std::cin >> id)) { std::cin.clear(); std::cin.ignore(10000, '\n'); continue; }
            
            myLibrary.searchBookDisk(id);
        } 
        else if (choice == 4) {
            myLibrary.displayAllBooks();
        }
        else if (choice == 5) {
            std::cout << "Shutting down Sentinel. Goodbye.\n";
            break;
        } 
        else {
            std::cout << "Invalid choice. Please select 1-5.\n";
        }
    }

    return 0;
}