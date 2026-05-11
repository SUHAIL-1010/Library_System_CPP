#pragma once
#include "Book.h"
#include <unordered_map>
#include <shared_mutex>
#include <mutex>
#include <string>

class Library {
private:
    std::unordered_map<int, Book> cache;
    mutable std::shared_mutex rw_mutex;
    const std::string dbFile = "library_db.dat"; 

    void loadFromDisk();
    void saveAllToDisk();
    
    // Helper function to word-wrap long strings for the table
    std::string getWrapChunk(std::string& text, int maxWidth);

public:
    Library();
    void addBook(int id, const std::string& title, const std::string& author, int quantity);
    void removeBook(int id, int amountToRemove);
    void searchBookDisk(int id);
    void displayAllBooks();
};