#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "WordData.h"
#include <algorithm>


void processFileWithParallelArrays(const std::string& filename); //should probably put this in a separate header


void displayMenu() {
    std::cout << "Select an option:\n";
    std::cout << "1. Count words using WordData array (current implementation)\n";
    std::cout << "2. Count words using parallel arrays\n";
    std::cout << "3. Count words using a std::list\n";
    std::cout << "4. Exit\n";
    std::cout << "> ";
}


void processFile(const std::string& filename) {
    std::ifstream inFile(filename);
    if (!inFile) {
        std::cerr << "Unable to open file: " << filename << std::endl;
        return; // Return early if file cannot be opened
    }

    std::vector<WordData> wordDataList;
    std::string word;
    while (inFile >> word) {
        auto it = std::find_if(wordDataList.begin(), wordDataList.end(), [&word](const WordData& wd) {
            return wd.matches(word);
        });
        if (it != wordDataList.end()) {
            // Word found, increment count
            it->increment();
        } else {
            // New word, add to the list
            wordDataList.emplace_back(word, 1);
        }
    }

    // Print the words and their counts to verify
    for (const auto& wd : wordDataList) {
        std::cout << wd << std::endl; // Assuming WordData has an overloaded << operator
    }
}

int main(int argc, char* argv[]) {
    std::string filename;

    // Batch mode check
    if (argc > 1) {
        filename = argv[1];
        processFile(filename);
        return 0; // Exit after processing in batch mode
    }

    // Interactive mode
    int choice = 0;
    do {
        displayMenu();
        std::cin >> choice;

        switch (choice) {
    case 1: // word data
        std::cout << "Enter the filename: ";
        std::cin >> filename;
        processFile(filename); 
        break;
     case 2: //parallel array
        std::cout << "Enter the filename: ";
        std::cin >> filename;
        processFileWithParallelArrays(filename);
        break;
    case 3:
        std::cout << "Option under development.\n";
        break;
    case 4:
        std::cout << "Exiting.\n";
        break;
    default:
        std::cout << "Invalid option. Please try again.\n";
}

    } while (choice != 4);

    return 0;
}

void processFileWithParallelArrays(const std::string& filename) { //parallel array implementation
    std::ifstream inFile(filename);
    if (!inFile) {
        std::cerr << "Unable to open file: " << filename << std::endl;
        return; // Return early if the file cannot be opened
    }

    std::vector<std::string> words;
    std::vector<int> counts;
    std::string word;
    while (inFile >> word) {
        auto it = std::find(words.begin(), words.end(), word); //Used std::find, not ideal due to O(n) complexity (Linear)
        if (it != words.end()) {
            // Word found, increment its count
            ++counts[std::distance(words.begin(), it)];
        } else {
            // New word, add to vectors
            words.push_back(word);
            counts.push_back(1);
        }
    }

    // Print the words and their counts
    for (size_t i = 0; i < words.size(); ++i) {
        std::cout << words[i] << ": " << counts[i] << std::endl;
    }
}

