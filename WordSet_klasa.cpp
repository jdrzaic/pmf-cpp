#include<iostream>
#include<algorithm>
#include<string>
#include<set>
#include<stdexcept>
#include<fstream>
#include<math.h>
#include<iterator>

class WordSet {
private:
    std::set<std::string> skup;
public:
//ako se f-ja ne poziva direktno, vec samo kao u main-u u zadatku 4, tada bi ta funkcija bila private.
    void separator(std::string const& text) {
		int textPosO = -1, textPosN, d;
		while(textPosO != (text.size() - 1)) {
			textPosN = text.find_first_of(".,!?:\t- ", textPosO + 1);
			if(textPosN ==  std::string::npos) {
				skup.insert(text.substr(textPosO + 1));
				break;
			}
			d = textPosN - textPosO - 1;
			if(d) {
				skup.insert(text.substr(textPosO + 1 ,d));
			}
			textPosO = textPosN;
		}
    //ispis(skup);
	}
    void ucitavanje(std::string imeDatoteke) {
		std::ifstream in;
		std::string all;
		in.open(imeDatoteke.c_str());
		if(!in) {
			throw std::runtime_error("greska");
		}
		while(getline(in, all)) {
			separator(all);
		}
		in.close();
	}
    void ispis() {
        for_each(skup.begin(), skup.end(), [] (std::string const& element) {std::cout << element << std::endl;}); //lambda
    }
    static double podudaranje(WordSet& A, WordSet& B) {
        double hi;
        std::set<std::string> intersection;
        if(A.skup.size() == 0 || B.skup.size() == 0) {
            return 0;
        }
        std::set<std::string>::iterator it = intersection.begin();
        std::set_intersection(A.skup.begin(), A.skup.end(), B.skup.begin(), B.skup.end(), std::inserter(intersection, it));
        hi = intersection.size() / (sqrt(A.skup.size()) * sqrt(B.skup.size()));
        //std::cout << intersection.size() << std::endl;
        //ispis(intersection);
        return hi;
    }
    //dodane metode
    int kolikoElemenata() {
        return skup.size();
    }
    int postoji(std::string rijec) {
        if(skup.find(rijec) != skup.end())
            return true;
        return false;
    }
};
int main(int argc, char** argv) {
    WordSet A, B;
    if(argc < 2){std::cerr << " Ocekujem dva argumenta\n" << argv[0] << " ime1 ime2\n"
                  << " ime1 = ulazna datoteka s tekstom\n ime2 = datoteka s trazenim rijecima."
                  << std::endl;
        std::exit(1);
    }
    std::string in1(argv[1]);
    std::string in2(argv[2]);
    A.ucitavanje(in1);
    B.ucitavanje(in2);
    std::cout << "prva datoteka" << std::endl;
    A.ispis();
    std::cout << "druga datoteka" << std::endl;
    B.ispis();
    double x = WordSet::podudaranje(A, B);
    std::cout << "Podudaranje iznosi " << x << std::endl;
    return 0;
}

