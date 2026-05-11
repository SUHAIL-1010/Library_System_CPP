#pragma once
#include <iostream>
#include <string>

struct Book {
    int id;
    std::string title;
    std::string author;
    int quantity;

    Book(int id = 0, std::string t = "", std::string a = "", int q = 1) 
        : id(id), title(t), author(a), quantity(q) {}

    // Used for single-book search displays
    void display() const {
        std::cout << "ID: " << id << "\n"
                  << "Title: " << title << "\n"
                  << "Author: " << author << "\n"
                  << "Quantity: " << quantity << "\n";
    }
};