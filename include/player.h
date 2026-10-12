#pragma once
#include <string>

using namespace std;

class Player {
  public:
    Player();
    ~Player();
    void setFirstName(string fName);
    void setLastName(string lName);
    void setPiece(char p);
    string getFirstName();
    string getLastName();
    string getFullName();
    string getPiece();
  protected:
    string firstName;
    string lastName;
    char piece;
};
