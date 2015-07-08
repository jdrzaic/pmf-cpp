#include"GameOL.h"

/*
pretvara poziciju znaka u vektoru s[tren] u njegovu poziciju (i.j) u "matrici"
iz datoteke
*/
void GameOL::posNizToPosMat(int& i, int& j, int pos) const {
    i = pos / stupaca;
    j = pos % stupaca;
}

void GameOL::init(std::string const & file_name) {
    std::ifstream in;
    std::string ucitan, dodatak;
    int dLinije;
    in.open(file_name.c_str());
    if(in.is_open()) {
        in >> redaka >> stupaca;
        std::getline(in,ucitan);
        while(std::getline(in, ucitan)) {
            //std::cout << ucitan << "a";
            dLinije = ucitan.size();
            if(dLinije < stupaca) {
                //dodatak.resize(stupaca - dLinije, ' ');
                //ucitan.append(dodatak);
                ucitan.resize(stupaca, ' ');
            }
            for(int i = 0; i < stupaca; ++i) {
                s[0].push_back(ucitan[i]);

            }
            ucitan.clear();
        }
    }
    (s[1]).resize(redaka * stupaca);
    /*u s[0] se u ovoj metodi spremaju podatci, pa joj nije potrebno eksplicitno
    zadati velicinu*/
}

void GameOL::print() const {
    for(int i = 0; i < redaka * stupaca; ++i) {
        if(i % stupaca == 0) std::cout << std::endl;
        std::cout << s[tren][i];
    }
    std::cout << std::endl;
}

/*
vraca 1 ako je celija na poziciji (i,j) ziva, 0 inace.
*/
bool GameOL::ziv(int i, int j) const {
    if(s[tren][posMatToPosNiz(i, j)] == '*') return true;
    return false;
}
int GameOL::br_susjeda(int i, int j) const {
    int suma = 0;
    for(int k = -1; k <= 1; ++k) {
        for(int l = -1; l <= 1; ++l) {
            if(k == 0 && l == 0) continue;
            if(i + k >= 0 && i + k <= redaka && j + l >= 0 && j + l <= stupaca)
                suma += ziv(i + k, j + l);
        }
    }
    return suma;
}
void GameOL::update() {
    int i, j, broj;
    for(int pos = 0; pos < redaka * stupaca; ++pos) {
        posNizToPosMat(i, j, pos);
        broj = br_susjeda(i, j);
        if(s[tren][pos] == '*') {
            if(broj < 2 || broj > 3)
                s[(tren + 1) % 2][pos] = ' ';
            else
                s[(tren + 1) % 2][pos] = '*';
        }
        else {
            if(broj == 3)
                s[(tren + 1) % 2][pos] = '*';
            else
                s[(tren + 1) % 2][pos] = ' ';
        }
    }
    tren = (tren + 1) % 2;
}

void GameOL::print(std::string const &  file_name) const {
    std::ofstream out;
    out.open(file_name.c_str());
    if(!out.is_open()) exit(1);
    out << redaka << ' ' << stupaca << std::endl;
    for(int i = 0; i < redaka * stupaca; ++i) {
        if(i % redaka == 0) {
            out << std::endl;
        }
        out << s[tren][i];
    }
}
