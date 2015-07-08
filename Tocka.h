#ifndef  _TOCKA_H_IS_INCLUDED_
#define  _TOCKA_H_IS_INCLUDED_

#include<cmath>
#include<vector>

class Tocka {
public:
    double x, y;
    Tocka() : x(0), y(0) {}
    Tocka(double _x, double _y) : x(_x), y(_y) {}
    void ispis() {
        std::cout << "(" << x << "," << y << ")" << std::endl;
    }
    static double put_nerek(std::vector<Tocka> skup);
    static void put_rek(std::vector<Tocka> const& tocke, std::vector<Tocka>& min_put, double& min_udalj);
private:
    static double norma(Tocka const& tocka1, Tocka const& tocka2) {
        return sqrt((tocka1.x - tocka2.x) * (tocka1.x - tocka2.x) + (tocka1.y - tocka2.y) * (tocka1.y - tocka2.y));
    }
    static double izracunaj_put(std::vector<Tocka> const& tocke);
    static void put_rek(std::vector<Tocka> const& tocke, std::vector<Tocka>& tren_put, std::vector<Tocka>& min_put,
                        int i, double& min_udalj, double& tren_udalj);
};
#endif
