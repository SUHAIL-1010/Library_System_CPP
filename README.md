# Sentinel Library Engine 📚

A high-performance, multi-threaded Library Management System built in Modern C++ (C++17).

## 🚀 Key Features
* **In-Memory Cache:** Utilizes `std::unordered_map` for $O(1)$ fast lookups.
* **Thread Safety:** Implements `std::shared_mutex` allowing concurrent reads while protecting exclusive write operations.
* **Data Persistence:** Custom binary serialization and parsing using pipe-delimited text (`|`) to prevent data corruption from commas in book titles.
* **CLI Dashboard:** Interactive console interface with formatted tabular output and dynamic word-wrapping.

## 🛠️ Tech Stack
* Language: C++17
* Concepts: OOPs, STL, Concurrency, File I/O (fstream)

## ⚙️ How to Run
Compile the code using a C++17 compliant compiler:
`g++ -std=c++17 main.cpp Library.cpp -o library_app -pthread`
Run
`.\library_app.exe`

## 🚀 Output:

<img width="901" height="451" alt="image" src="https://github.com/user-attachments/assets/2d3aff91-f4a8-4eff-a9d0-cfe83041de22" />

