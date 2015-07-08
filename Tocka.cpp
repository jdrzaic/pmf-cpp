#include<iostream>
#include<cmath>
#include<algorithm>
#include<vector>
#include<bitset>
#include"Tocka.h"

double Tocka::izracunaj_put(std::vector<Tocka> const& tocke) {
    double put = 0.0;
    std::vector<Tocka>::const_iterator it = tocke.begin();
    std::vector<Tocka>::const_iterator tmp;
    while(it != tocke.end()){
        if(it != tocke.begin())
            put += norma(*tmp, *it);
        //std::cout << put << std::endl;
        tmp = it;
        ++it;
    }
    //std::cout << put << std::endl;
    return put;
}
bool operator< (Tocka const& tocka1, Tocka const& tocka2) {
    if(tocka1.x < tocka2.x) return true;
    if(tocka1.x == tocka2.x) {
        if(tocka1.y < tocka2.y) return true;
        return false;
    }
    return false;
}
bool operator== (Tocka const& tocka1, Tocka const& tocka2) {
    return tocka1.x == tocka2.x && tocka1.y == tocka2.y;
}
double Tocka::put_nerek(std::vector<Tocka> tocke) {
    double min_put = -1, tmp_put;
    std::sort(tocke.begin(), tocke.end());
    do {
        if((tmp_put = izracunaj_put(tocke)) < min_put || min_put == -1)
            min_put = tmp_put;
    } while(std::next_permutation(tocke.begin(), tocke.end()));
    //std::cout << nf << std::endl;
    return min_put;
}
void Tocka::put_rek(std::vector<Tocka> const& tocke, std::vector<Tocka>& min_put, double& min_udalj) {
    std::vector<Tocka> tren_put;
    double tren_udalj = 0;
    min_udalj = -1;
    for(int i = 0; i < tocke.size(); ++i) {
        put_rek(tocke, tren_put, min_put,
                    i, min_udalj, tren_udalj);
    }
}
void Tocka::put_rek(std::vector<Tocka> const& tocke, std::vector<Tocka>& tren_put, std::vector<Tocka>& min_put,
                    int i, double& min_udalj, double& tren_udalj) {
    tren_put.push_back(tocke[i]);
    if(tren_put.size() == tocke.size()) {
        if(min_udalj == -1 || tren_udalj < min_udalj) {
            min_put = tren_put;
            min_udalj = tren_udalj;
        }
    }
    else {
        for(int j = 0; j < tocke.size(); ++j) {
            if(std::count(tren_put.begin(), tren_put.end(), tocke[j]) == 0) {
                tren_udalj += norma(tocke[i], tocke[j]);
                put_rek(tocke, tren_put, min_put, j, min_udalj, tren_udalj);
                tren_udalj -= norma(tocke[i], tocke[j]);
            }
        }
    }
    tren_put.pop_back();
}
