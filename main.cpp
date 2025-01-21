#include <array>
#include <fstream>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>

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

class Tusmo {

private:
  string word;
  float score;
  int occurency;

public:
  // Constructor

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

  // To string

  void display() const {
    cout << "Word: " << word << ", Score: " << score
         << ", Occurency: " << occurency << ", First Char: " << getFirstChar()
         << '\n';
  }
};

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

  vector<vector<Tusmo>> tusmoVectors(25);

  for (auto tusmo : tusmos) {
    tusmoVectors[tusmo.getWord().size() - 1].push_back(tusmo);
  }

  for (auto tusmo : tusmoVectors[24]) {
    tusmo.display();
  }

  return EXIT_SUCCESS;
}