#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "WordData.h"
#include <algorithm>
#include <list> 

/*********************************************************************************************************
 * Function: processFileWithVectorIndexing
 * -------------------------------------------------------------------------------------------------------
 * Description: Processes the specified file to count occurrences of each unique word found within, using
 * a vector for efficient indexing and access. This method utilizes a vector's direct element access to
 * search for existing words and increment their counts or add new words as needed. It is designed to
 * handle up to a predetermined number of unique words, with the excess being ignored.
 * -------------------------------------------------------------------------------------------------------
 * Parameters:
 * - filename (import) : A string representing the path of the file to be processed. This file will be
 *   opened and each word will be read sequentially to update the word count or add new entries in
 *   the vector.
 * -------------------------------------------------------------------------------------------------------
 * Member Type: Facilitator
 * Returns: Void
 * -------------------------------------------------------------------------------------------------------
 * Pre-conditions: The file specified by 'filename' exists and is accessible for reading.
 * Post-conditions: Outputs the count of each unique word found in the file up to the maximum size limit.
 *                  Each word and its corresponding count are printed to standard output.
 *********************************************************************************************************/
void processFileWithVectorIndexing(const std::string& filename) {
    const int maxSize = 10; // Max number of unique words to track
    std::vector<WordData> wordDataVector;
    std::ifstream inFile(filename);
    
    if (!inFile) {
        std::cerr << "Unable to open file: " << filename << std::endl;
        return;
    }
    
    std::string word;
    while (inFile >> word) {
        bool found = false;
        for (size_t i = 0; i < wordDataVector.size() && i < maxSize; ++i) {
            if (wordDataVector[i].matches(word)) {
                wordDataVector[i].increment();
                found = true;
                break;
            }
        }
        if (!found && wordDataVector.size() < maxSize) {
            wordDataVector.emplace_back(word, 1);
        }
    }
    
    for (const auto& wd : wordDataVector) {
        std::cout << wd << std::endl;
    }
}



void processFileRecursively(const std::string& filename) { //Recursive Method
    const int maxSize = 10;
    WordData* wordArray = new WordData[maxSize];
    int numWords = 0; // Track the number of unique words added

    std::ifstream inFile(filename);
    if (!inFile) {
        std::cerr << "Unable to open file: " << filename << std::endl;
        delete[] wordArray; // Free allocated memory
        return;
    }

    std::string word;
    while (inFile >> word) {
        addOrUpdateWordRecursively(wordArray, word, 0, numWords, maxSize);
    }

    // Print results
    for (int i = 0; i < numWords; ++i) {
        std::cout << wordArray[i] << std::endl;
    }

    delete[] wordArray; // Cleanup
}



void addOrUpdateWordRecursively(WordData* array, const std::string& word, int currentIndex, int& numWords, int maxSize) { // Recursive Helper Function
    // Base case: If we've checked all words or array is full
    if (currentIndex == numWords) {
        if (numWords < maxSize) {
            array[numWords++] = WordData(word, 1);
        }
        return;
    }

    // If the word is found
    if (array[currentIndex].matches(word)) {
        array[currentIndex].increment();
        return;
    }

    // Recursive call
    addOrUpdateWordRecursively(array, word, currentIndex + 1, numWords, maxSize);
}


void processFileWithPointers(const std::string& filename) { //object array pointer (no index)
    const int maxSize = 10;
    WordData* wordArray = new WordData[maxSize]; // Dynamically allocate array of WordData
    int numWords = 0; // Track the number of unique words added

    std::ifstream inFile(filename);
    if (!inFile) {
        std::cerr << "Unable to open file: " << filename << std::endl;
        delete[] wordArray; // Don't forget to free allocated memory
        return;
    }

    std::string word;
    while (inFile >> word && numWords < maxSize) {
        bool found = false;
        for (WordData* ptr = wordArray; ptr != wordArray + numWords; ++ptr) {
            if (ptr->matches(word)) {
                ptr->increment();
                found = true;
                break;
            }
        }
        if (!found && numWords < maxSize) {
            new (wordArray + numWords) WordData(word, 1); // Use placement new for construction
            numWords++;
        }
    }

    // Print results
    for (WordData* ptr = wordArray; ptr != wordArray + numWords; ++ptr) {
        std::cout << *ptr << std::endl; // Assuming WordData has an overloaded << operator
    }

    // Cleanup
    delete[] wordArray; // Matching delete[] for the allocated array
}


// Recursive function to count words using parallel arrays
void countWordsRecursively(const std::string& word, std::string words[], int counts[], int& currentIndex, int maxSize, int& uniqueWords) {
    if (currentIndex >= maxSize) return; // Base case: reached the max size of the arrays

    if (words[currentIndex] == word) { // Word found
        counts[currentIndex]++;
        return;
    } else if (currentIndex == uniqueWords) { // New word
        if (uniqueWords < maxSize) { // Still have space
            words[uniqueWords] = word;
            counts[uniqueWords] = 1;
            uniqueWords++;
        }
        return;
    }

    // Not found, move to the next index
    countWordsRecursively(word, words, counts, ++currentIndex, maxSize, uniqueWords);
}

// Function to process the file using parallel arrays and the recursive counting method
void processFileWithParallelArraysRecursively(const std::string& filename) {
    const int maxSize = 10;
    std::string words[maxSize] = {};
    int counts[maxSize] = {0};
    int uniqueWords = 0;

    std::ifstream inFile(filename);
    if (!inFile) {
        std::cerr << "Unable to open file: " << filename << std::endl;
        return;
    }

    std::string word;
    while (inFile >> word) {
        int currentIndex = 0; // Start from the beginning for each new word
        countWordsRecursively(word, words, counts, currentIndex, maxSize, uniqueWords);
    }

    // Print the words and their counts
    for (int i = 0; i < uniqueWords; ++i) {
        std::cout << words[i] << ": " << counts[i] << std::endl;
    }
}


void processFileWithList(const std::string& filename) {
    std::ifstream inFile(filename);
    if (!inFile) {
        std::cerr << "Unable to open file: " << filename << std::endl;
        return; // Return early if file cannot be opened
    }

    std::list<WordData> wordDataList;
    std::string word;
    while (inFile >> word) {
        auto it = std::find_if(wordDataList.begin(), wordDataList.end(), [&word](const WordData& wd) {
            return wd.matches(word);
        });
        if (it != wordDataList.end()) {
            it->increment();
        } else {
            wordDataList.emplace_back(word, 1);
        }
    }

    // Assuming WordData has an overloaded << operator
    for (const auto& wd : wordDataList) {
        std::cout << wd << std::endl;
    }
}

void processFileWithParallelArrays(const std::string& filename); //should probably put this in a separate header


void displayMenu() {
    std::cout << "Select an option:\n";
    std::cout << "1. Parallel Iterative\n"; 
    std::cout << "2. Parallel Recursive\n"; 
    std::cout << "3. OBJECT ARRAY ITERATIVE\n"; 
    std::cout << "4. Object Array Pointer (No Indexing)\n"; 
    std::cout << "5. Object Array Recursive\n";
    std::cout << "6. STL Seq Object Indexing\n"; 
    std::cout << "7. STL Seq Object Iterator (No Indexing)\n";
    std::cout << "8. Exit\n";
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
        processFile(filename); // This needs to align with one of the specific functionalities.
        return 0; // Exit after processing in batch mode
    }

    // Interactive mode
    int choice = 0;
    do {
        displayMenu();
        std::cin >> choice;

        switch (choice) {
            case 1: // OBJECT ARRAY ITERATIVE
                std::cout << "Enter the filename: ";
                std::cin >> filename;
                processFile(filename); 
                break;
            case 2: // Parallel Iterative
                std::cout << "Enter the filename: ";
                std::cin >> filename;
                processFileWithParallelArrays(filename); 
                break;
            case 3: // Parallel Recursive
                std::cout << "Enter the filename: ";
                std::cin >> filename;
                processFileWithParallelArraysRecursively(filename); 
                break;
            case 4: // Object Array Pointer (No Indexing)
                std::cout << "Enter the filename: ";
                std::cin >> filename;
                processFileWithPointers(filename);
                break;
            case 5: // Object Array Recursive
                std::cout << "Enter the filename: ";
                std::cin >> filename;
                processFileRecursively(filename); 
                break;
            case 6: // STL Seq Object Indexing
                std::cout << "Enter the filename: ";
                std::cin >> filename;
                processFileWithVectorIndexing(filename); 
                break;
            case 7: // STL Seq Object Iterator (No Indexing)
                std::cout << "Enter the filename: ";
                std::cin >> filename;
                processFileWithList(filename); 
                break;
            case 8: // Exiting the program
                std::cout << "Exiting.\n";
                break;
        }
    } while (choice != 8);

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



