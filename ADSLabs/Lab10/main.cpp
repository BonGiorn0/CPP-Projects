#include <iostream>
#include <fstream>
#include <vector>
#include <string>

std::vector<int> computeLPS(const std::string& pattern) {
    int patternLength = pattern.length();
    std::vector<int> lps(patternLength, 0);
    int j = 0; // Length of the previous longest prefix suffix

    for (int i = 1; i < patternLength; ++i) {
        while (j > 0 && pattern[i] != pattern[j]) {
            j = lps[j - 1];
        }

        if (pattern[i] == pattern[j]) {
            lps[i] = ++j;
        }
    }
    return lps;
}

int findFirstOccurrence(const std::string& text, const std::string& pattern) {
    int textLength = text.length();
    int patternLength = pattern.length();
    std::vector<int> lps = computeLPS(pattern);
    for(int i : lps)
        std::cout << i << ' ';
    std::cout << std::endl;
    int j = 0; // Index for pattern[]

    for (int i = 0; i < textLength; ++i) {
        while (j > 0 && text[i] != pattern[j]) {
            j = lps[j - 1];
        }

        if (text[i] == pattern[j]) {
            if (j == patternLength - 1) {
                return i - j; // Return the start index of the first occurrence
            } else {
                j++;
            }
        }
        std::cout << "i: " << i << ' ' << "j: " << j << std::endl;
    }
    return -1; // Pattern not found in text
}

int main() {
    std::ifstream file("input.txt"); // Replace "input.txt" with your file name
    if (!file.is_open()) {
        std::cout << "Unable to open file!" << std::endl;
        return 1;
    }

    std::string S, P;
    if (std::getline(file, S) && std::getline(file, P)) {
        int index = findFirstOccurrence(S, P);
        if (index != -1) {
            std::cout << "Pattern P found at index: " << index << std::endl;
        } else {
            std::cout << "Pattern P not found in string S" << std::endl;
        }
    } else {
        std::cout << "File does not contain both strings!" << std::endl;
    }

    file.close();
    return 0;
}
