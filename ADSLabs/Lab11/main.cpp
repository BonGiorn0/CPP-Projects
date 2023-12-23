#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

#define NO_OF_CHARS 256

const int ALPHABET_SIZE = 29;


std::string replaceCharsInMiddleWord(const std::string& text) {
    std::string modifiedText = text;
    int wordCount = 0;
    bool isInMiddle = false;
    int wordStart = 0;

    for (size_t i = 0; i < text.size() / 2; ++i) 
        if (!isalpha(text[i])) 
                wordStart = i;

    int j = wordStart;
    while(isalpha(text[j])){
        if (text[j] == 'a') {
            modifiedText[j] = 'o';
        } else if (text[j] == 'i') {
            modifiedText[j] = 'e';
        }
        j++;
    }
    return modifiedText;
}

void badCharHeuristic( string str, int size, 
                        int badchar[NO_OF_CHARS]) 
{ 
    int i; 
 
    // Initialize all occurrences as -1 
    for (i = 0; i < NO_OF_CHARS; i++) 
        badchar[i] = -1; 
 
    // Fill the actual value of last occurrence 
    // of a character 
    for (i = 0; i < size; i++) 
        badchar[(int) str[i]] = i; 
} 
 

void search( string txt, string pat) 
{ 
    int m = pat.size(); 
    int n = txt.size(); 
 
    int badchar[NO_OF_CHARS]; 
 
    /* Fill the bad character array by calling 
    the preprocessing function badCharHeuristic() 
    for given pattern */
    badCharHeuristic(pat, m, badchar); 
    for(int i = 0; i < 256; i++)
        cout << badchar[i] << ' ';
    cout << endl;
 
    int s = 0; // s is shift of the pattern with 
                // respect to text 
    while(s <= (n - m)) 
    { 
        int j = m - 1; 
 
        /* Keep reducing index j of pattern while 
        characters of pattern and text are 
        matching at this shift s */
        while(j >= 0 && pat[j] == txt[s + j]){ 
            j--; 
            cout << "j: " << j << " pattern[j]: " << pat[j] << " text[shift + j]: " << txt[s + j];
            cout << endl;
        }
 
        /* If the pattern is present at current 
        shift, then index j will become -1 after 
        the above loop */
        if (j < 0) 
        { 
            cout << "pattern occurs at shift = " <<  s << endl; 
 
            /* Shift the pattern so that the next 
            character in text aligns with the last 
            occurrence of it in pattern. 
            The condition s+m < n is necessary for 
            the case when pattern occurs at the end 
            of text */
            s += (s + m < n)? m-badchar[txt[s + m]] : 1; 
 
        } 
 
        else
            /* Shift the pattern so that the bad character 
            in text aligns with the last occurrence of 
            it in pattern. The max function is used to 
            make sure that we get a positive shift. 
            We may get a negative shift if the last 
            occurrence of bad character in pattern 
            is on the right side of the current 
            character. */
            s += max(1, j - badchar[txt[s + j]]); 
    } 
} 

int main() {
    
    std::string text1 = "brown fox jumps over the lazy dog";
    std::string text2 = "The quick brown fox jumps over the lazy dog and the quick brown fox jumps over the lazy dog with a quiet sound";
    

    // Replace 'a' with 'o' and 'i' with 'e' in the middle word of text1
    std::string modifiedText1 = replaceCharsInMiddleWord(text1);

    std::cout << modifiedText1 << '\n';

    // Find occurrences of modified text1 in text2 using Boyer-Moore
    std::vector<int> positions;
    //boyerMoore(text2, modifiedText1, positions);
    search(text2, modifiedText1);

    // Display occurrences
    
    return 0;
}
