//
// Includes
//

#include <array>
#include <fstream>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>
#include <algorithm>



//
// Namespaces
//

using namespace std;



//
// Occurency array and alphabet array
//

constexpr array<tuple<float, int>, 26> frequencyTable =
{
  make_tuple(0.1444f, 'e'), make_tuple(0.0746f, 'a'),
  make_tuple(0.0664f, 'i'), make_tuple(0.0651f, 's'),
  make_tuple(0.0639f, 'n'), make_tuple(0.0607f, 'r'),
  make_tuple(0.0592f, 't'), make_tuple(0.0507f, 'o'),
  make_tuple(0.0496f, 'l'), make_tuple(0.0454f, 'u'),
  make_tuple(0.0367f, 'd'), make_tuple(0.0323f, 'c'),
  make_tuple(0.0262f, 'm'), make_tuple(0.0249f, 'p'),
  make_tuple(0.0123f, 'g'), make_tuple(0.0114f, 'b'),
  make_tuple(0.0111f, 'v'), make_tuple(0.0111f, 'h'),
  make_tuple(0.0111f, 'f'), make_tuple(0.0065f, 'q'),
  make_tuple(0.0046f, 'y'), make_tuple(0.0038f, 'x'),
  make_tuple(0.0034f, 'j'), make_tuple(0.0029f, 'k'),
  make_tuple(0.0017f, 'w'), make_tuple(0.0015f, 'z')
};

constexpr array<char, 26> alphabet =
{
  'a', 'b', 'c', 'd', 'e', 'f',
  'g', 'h', 'i', 'j', 'k',  'l',
  'm', 'n',  'o', 'p', 'q',  'r',
  's', 't', 'u', 'v', 'w', 'x',
  'y', 'z'
};



//
// Class for Tusmo objects
//

class Tusmo {

private:
  // Attributes

  string word;
  float score;
  int occurency;

public:
  // Constructor (default and "word" one)

  Tusmo() : word(""), score(0.0), occurency(0) {}

  Tusmo(const string &word) : word(word), score(0), occurency(0) {
    computeScore();
  }

  // Getters

  const string &getWord() const { return word; }
  float getScore() const { return score; }
  int getOccurency() const { return occurency; }

  // Function to get the first char

  char getFirstChar() const { return word.empty() ? '\0' : word[0]; }

  // Function to compute the score

  void computeScore() {
    // For every characters in the word

    for (auto character : word) {

      // Not computing '-' characters

      if (character != 45)
      {
        // For every letters in the alphabet

        for (int i = 0; i < 26; ++i) {

          // Checking if the current character have
          // a match in the frequencyTable

          if (get<1>(frequencyTable[i]) == character) {

            // If yes, check if is it possible to add the
            // the score of the character score in frequency
            // table by the help of the binary operator &

            if ((occurency & (1 << i)) == 0) {

              // If yes, setting the bit that correspond
              // to the letter in occurency parameter
              // of the object and adding to the score
              // the value of the character in the
              // frenquency table

              occurency |= (1 << i);
              score += get<0>(frequencyTable[i]);
            }

            // If already compute the score for this
            // letter, simply skip the others one

            break;
          }
        }
      }
    }
  }

  // To string

  void display() const {
    cout << "Word: " << word << ", Score: " << score
         << ", Occurency: " << occurency << ", First Char: " << getFirstChar()
         << '\n';
  }
};



//
// Function to comput pertinent words
//

void computePertinentWords(vector<Tusmo> &tusmos)
{

  // Declaration of the vector that  will contain all the words for each
  // words size (ie : tab[0] = 1 letter words, tab[1] = 2 letters
  // words, ... , tab[24] = 25 letters words)

  vector<vector<Tusmo>> tusmoVectors(25);

  // For each words on tusmos vector

  for (auto tusmo : tusmos) {

    // If there are one or more -, those are not include in word's size
    // (ie : abat-jour is 8 letter word and not 9)

    int occur = count(tusmo.getWord().begin(), tusmo.getWord().end(), '-');
    if (occur)
      tusmoVectors[tusmo.getWord().size() - 1 - occur].push_back(tusmo);
    else
      tusmoVectors[tusmo.getWord().size() - 1].push_back(tusmo);
  }

  // Creating a vector for the most pertinent words of the 330k words
  // (ie : those with the highest score)

  array<array<Tusmo, 26>, 25> pertinentTusmos;

  // For every size of words

  for (int i = 0; i < 25; ++i)
  {

    // Resetting the letters we are dealing with

    int j = 0;

    // For every letter in the alphabet

    for (int k = 0; k < 26; ++k)
    {

      // Initializing an temporary object for max
      // score word computation

      Tusmo maxTusmo;

      // For every words at a specified size (ie : tab[0], for
      // every word of 1 letter)

      for (auto tusmo : tusmoVectors[i]) {

        // If the first char of the word is the same as the
        // first char of the alphabet (ie : computing all
        // words beginning with 'a' then 'b' etc.)

        if (tusmo.getFirstChar() == alphabet[k])
        {

          // If the score of the current object is higher than
          // the max, this is the new max object

          if (tusmo.getScore() >= maxTusmo.getScore())
          {
            maxTusmo = tusmo;
          }
        }

        // Here potential performances gain but need to
        // investigate it deeply

      }

      // Saving the max for a given size and given start letter
      // and then incrementing j, to deal with the next letter

      pertinentTusmos[i][j] = maxTusmo;
      j++;
    }
  }

  // Printing every words in the
  // pertinent words list

  for (auto& row : pertinentTusmos) {
    for (auto& tusmo : row) {
      if (tusmo.getWord().size() > 0)
        cout << tusmo.getWord() << endl;
    }
    cout << endl << endl;
  }
}



//
// Main
//

int main() {

  // Creating a vector of tusmos

  vector<Tusmo> tusmos;

  // Setting the file we need to read from

  ifstream file("french_set/lst_mots.txt");

  if (file)
    {

    // Getting the current readed line

    string line;
    while (getline(file, line))
    {

      // Addind this line to the tusmos vector

      Tusmo tusmo(line);
      tusmos.push_back(tusmo);
    }
  }

  // Error handleling

  else
  {
    cout << "ERROR: Unable to open the file in lecture mode." << endl;
    return EXIT_FAILURE;
  }

  // Call to the computePertinentWords function

  computePertinentWords(tusmos);

  return EXIT_SUCCESS;
}