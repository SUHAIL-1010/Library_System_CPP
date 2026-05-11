#include "Library.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip> // Required for table formatting (setw, left)

Library::Library() {
    loadFromDisk();
}

void Library::loadFromDisk() {
    std::ifstream inFile(dbFile);
    if (!inFile.is_open()) {
        std::cout << "No existing database found. Starting fresh.\n";
        return;
    }

    std::string line;
    while (std::getline(inFile, line)) {
        std::stringstream ss(line);
        std::string idStr, title, author, qtyStr;

        if (std::getline(ss, idStr, '|') &&
            std::getline(ss, title, '|') &&
            std::getline(ss, author, '|') &&
            std::getline(ss, qtyStr)) {
            
            int id = std::stoi(idStr);
            int qty = std::stoi(qtyStr);
            cache[id] = Book(id, title, author, qty);
        }
    }
    inFile.close();
    std::cout << "Successfully loaded " << cache.size() << " books from disk.\n";
}

void Library::saveAllToDisk() {
    std::ofstream outFile(dbFile, std::ios::trunc); 
    if (outFile.is_open()) {
        for (const auto& pair : cache) {
            const Book& b = pair.second;
            outFile << b.id << "|" << b.title << "|" << b.author << "|" << b.quantity << "\n";
        }
        outFile.close();
    }
}

void Library::addBook(int id, const std::string& title, const std::string& author, int quantity) {
    std::unique_lock<std::shared_mutex> lock(rw_mutex);

    if (cache.find(id) != cache.end()) {
        cache[id].quantity += quantity;
        std::cout << "[Success] Added " << quantity << " more copies. Total: " << cache[id].quantity << "\n";
    } else {
        cache[id] = Book(id, title, author, quantity);
        std::cout << "[Success] New book added to the library.\n";
    }
    saveAllToDisk(); 
}

void Library::removeBook(int id, int amountToRemove) {
    std::unique_lock<std::shared_mutex> lock(rw_mutex);

    auto it = cache.find(id);
    if (it != cache.end()) {
        if (it->second.quantity > amountToRemove) {
            it->second.quantity -= amountToRemove;
            std::cout << "[Success] Removed " << amountToRemove << " copies. Remaining: " << it->second.quantity << "\n";
        } else {
            cache.erase(it);
            std::cout << "[Success] All copies removed. Book completely deleted from system.\n";
        }
        saveAllToDisk(); 
    } else {
        std::cout << "[Error] Book ID " << id << " not found in the library.\n";
    }
}

void Library::searchBookDisk(int id) {
    std::shared_lock<std::shared_mutex> lock(rw_mutex);

    auto it = cache.find(id);
    if (it != cache.end()) {
        std::cout << "\n[Success] Book Found:\n";
        std::cout << "-----------------------\n";
        it->second.display();
        std::cout << "-----------------------\n";
    } else {
        std::cout << "\n[Error] Book ID " << id << " not found.\n";
    }
}

// Helper Function: safely splits strings at spaces so words aren't cut in half
std::string Library::getWrapChunk(std::string& text, int maxWidth) {
    if (text.length() <= maxWidth) {
        std::string chunk = text;
        text = ""; // Empty the original string
        return chunk;
    }
    
    // Find the last space within the allowed width
    size_t spacePos = text.rfind(' ', maxWidth);
    if (spacePos != std::string::npos && spacePos > 0) {
        std::string chunk = text.substr(0, spacePos);
        text.erase(0, spacePos + 1); // +1 removes the space itself
        return chunk;
    }
    
    // If there is a massive word with no spaces, just hard cut it
    std::string chunk = text.substr(0, maxWidth);
    text.erase(0, maxWidth);
    return chunk;
}

void Library::displayAllBooks() {
    std::shared_lock<std::shared_mutex> lock(rw_mutex);

    if (cache.empty()) {
        std::cout << "\n[Info] The library is currently empty. No books to display.\n";
        return;
    }

    std::cout << "\n================================================================================\n";
    // Header Row Formatting
    std::cout << std::left 
              << std::setw(6)  << "S.No" 
              << std::setw(8)  << "ID" 
              << std::setw(35) << "Title" 
              << std::setw(20) << "Author" 
              << std::setw(8)  << "Qty" << "\n";
    std::cout << "--------------------------------------------------------------------------------\n";
    
    int sno = 1;
    for (const auto& pair : cache) {
        std::string titleStr = pair.second.title;
        std::string authorStr = pair.second.author;
        
        bool isFirstLineOfRow = true;

        // Loop runs until both title and author have been fully printed
        while (!titleStr.empty() || !authorStr.empty()) {
            
            // Extract chunks that fit in the columns (33 chars for title, 18 for author)
            std::string titleChunk = getWrapChunk(titleStr, 33);
            std::string authorChunk = getWrapChunk(authorStr, 18);

            if (isFirstLineOfRow) {
                // Print the main row with ID and Quantity
                std::cout << std::left 
                          << std::setw(6)  << (std::to_string(sno) + ".")
                          << std::setw(8)  << pair.second.id
                          << std::setw(35) << titleChunk
                          << std::setw(20) << authorChunk
                          << std::setw(8)  << pair.second.quantity << "\n";
                isFirstLineOfRow = false;
            } else {
                // Print the extra wrapped lines, leaving S.No, ID, and Qty blank
                std::cout << std::left 
                          << std::setw(6)  << ""
                          << std::setw(8)  << ""
                          << std::setw(35) << titleChunk
                          << std::setw(20) << authorChunk
                          << std::setw(8)  << "" << "\n";
            }
        }
        std::cout << "................................................................................\n";
        sno++;
    }
    
    std::cout << "================================================================================\n";
    std::cout << "Total unique titles: " << cache.size() << "\n";
}