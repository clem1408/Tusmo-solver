#include <array>
#include <fstream>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>
#include <algorithm>

using namespace std;

// Occurency array with ascii

constexpr array<tuple<float, int>, 26> frequencyTable = {
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
    make_tuple(0.0017f, 'w'), make_tuple(0.0015f, 'z')};

constexpr array<tuple<char, int>, 26> alphabet = {
  make_tuple('a', 0), make_tuple('b', 1), make_tuple('c', 2),
  make_tuple('d', 3), make_tuple('e', 4), make_tuple('f', 5),
  make_tuple('g', 6), make_tuple('h', 7), make_tuple('i', 8),
  make_tuple('j', 9), make_tuple('k', 10), make_tuple('l', 11),
  make_tuple('m', 12), make_tuple('n', 13), make_tuple('o', 14),
  make_tuple('p', 15), make_tuple('q', 16), make_tuple('r', 17),
  make_tuple('s', 18), make_tuple('t', 19), make_tuple('u', 20),
  make_tuple('v', 21), make_tuple('w', 22), make_tuple('x', 23),
  make_tuple('y', 24), make_tuple('z', 25)
};

class Tusmo {

private:
  string word;
  float score;
  int occurency;

public:
  // Constructor

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
    for (auto character : word) {

      // We do note compute '-'

      if (character != 45)
      {
        for (int i = 0; i < 26; ++i) {
          if (get<1>(frequencyTable[i]) == character) {
            if ((occurency & (1 << i)) == 0) {
              occurency |= (1 << i);
              score += get<0>(frequencyTable[i]);
            }
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
  vector<vector<Tusmo>> tusmoVectors(25);

  for (auto tusmo : tusmos) {
    int occur = count(tusmo.getWord().begin(), tusmo.getWord().end(), '-');
    if (occur)
      tusmoVectors[tusmo.getWord().size() - 1 - occur].push_back(tusmo);
    else
      tusmoVectors[tusmo.getWord().size() - 1].push_back(tusmo);
  }

  array<array<Tusmo, 26>, 25> pertinentTusmos;

  for (int i = 0; i < 25; ++i)
  {
    int j = 0;
    for (int k = 0; k < 26; ++k)
    {
      Tusmo maxTusmo;
      for (auto tusmo : tusmoVectors[i]) {
        if (tusmo.getFirstChar() == get<0>(alphabet[k]))
        {
          if (tusmo.getScore() >= maxTusmo.getScore())
          {
            maxTusmo = tusmo;
          }
        }// Here performances
      }
      pertinentTusmos[i][j] = maxTusmo;
      j++;
    }
  }

  for (auto& row : pertinentTusmos) {
    for (auto& tusmo : row) {
      if (tusmo.getWord().size() > 0)
        cout << tusmo.getWord() << endl;
    }
    cout << endl << endl;
  }
}



int main() {
  vector<Tusmo> tusmos;

  ifstream file("french_set/lst_mots.txt");

  if (file) {
    string line;
    while (getline(file, line)) {
      Tusmo tusmo(line);
      tusmos.push_back(tusmo);
    }
  } else {
    cout << "ERROR: Unable to open the file in lecture mode." << endl;
  }

  computePertinentWords(tusmos);

  return EXIT_SUCCESS;
}