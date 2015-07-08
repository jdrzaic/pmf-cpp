#ifndef __GAME_OF_LIFE_H_INCLUDED__
#define __GAME_OF_LIFE_H_INCLUDED__

#include<vector>
#include<string>
#include<fstream>
#include<iostream>

class GameOL{
  public:
    GameOL() : tren(0), redaka(0), stupaca(0) {}
    ~GameOL() {};
    void init(std::string const & file_name);
    void print() const;
    void print(std::string const &  file_name) const;
    void update();
  private:
    // broj živih susjeda danog elementa (i,j)
    int redaka, stupaca, tren; //tren - u kojem vektoru trenutno stanje
    std::vector<char> s[2];
    /*
    pretvara indekse i,j koji odgovaraju poziciji znaka u "matrici" u datoteci
    u poziciju tog znaka u vektoru s[tren].
    */
    int posMatToPosNiz(int i, int j) const {return stupaca * i + j;};
    void posNizToPosMat(int& i, int& j, int pos) const;
    int br_susjeda(int i, int j) const;
    bool ziv(int i, int j) const;
};
#endif
