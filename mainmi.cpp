#include"mi.h"
#include<assert.h>
#include<string>
#include<cstdlib>



bool operator==(const Datum& s, const Datum& d) {
    return s.dan() == d.dan() && s.mjesec() == d.mjesec() && s.godina() == d.godina();
}

Datum::Datum(const std::string& datum) {split(datum);}

int Datum::dan() const {return m_dan;}
int Datum::mjesec() const {return m_mjesec;}
int Datum::godina() const {return m_godina;}

//treba dodati nule
const std::string Datum::toString() const {
    std::stringstream ss;
    ss.width(2);
    ss.fill('0');
    ss << std::right << m_dan << ":";
    ss.width(2);
    ss << std::right << m_mjesec << ":";
    ss << m_godina;
    return ss.str();
}

void Datum::split(std::string s) {
    std::stringstream ss(s);
    char tmp;
    ss >> m_dan >> tmp >> m_mjesec >> tmp >> m_godina;
}

Osoba::Osoba(const std::string& ime, const std::string& prezime) : m_ime(ime), m_prezime(prezime) {
    std::cout << "Osoba\n";
}

bool Osoba::jednak(Osoba const& o) const{
    if(o.ime() == m_ime && o.prezime() == m_prezime) return true;
    return false;
}

const std::string& Osoba::ime() const {return m_ime;}
const std::string&  Osoba::prezime() const {return m_prezime;}

Osoba::Stringifier::Stringifier(const Osoba* o) {
    m_data = o->ime() + "\n" + o->prezime() + "\n";
}

Zaposlenik::Zaposlenik(const std::string ime, const std::string prezime, const int rMjesto, const std::string& poc) :
        Osoba(ime, prezime), m_radnoMjesto(rMjesto), m_pocetakZaposlenja(poc) {
    std::cout << "Zaposlenik\n";
}

bool Zaposlenik::jednak(Osoba const& o) const {
    if((*this).Osoba::jednak(o)) {
        const Zaposlenik& z = dynamic_cast<const Zaposlenik&>(o);
        if(z.radnoMjesto() == m_radnoMjesto && z.pocetakZaposlenja() == m_pocetakZaposlenja) {
            return true;
        }
    }
    return false;
}

int Zaposlenik::radnoMjesto() const {return m_radnoMjesto;}
const Datum Zaposlenik::pocetakZaposlenja() const {return m_pocetakZaposlenja;}

Zaposlenik::Stringifier::Stringifier(const Zaposlenik* o) : Osoba::Stringifier(o) {
    m_data += std::to_string(o->radnoMjesto()) + "\n" + o->pocetakZaposlenja().toString() + "\n";
}

Student::Student(const std::string& ime, const std::string& prezime, const int godina) :
        Osoba(ime, prezime), m_godina(godina){
    std::cout << "Student\n";
}

bool Student::jednak(Osoba const& o) const {
    if((*this).Osoba::jednak(o)) {
        const Student& s = dynamic_cast<const Student&>(o);
        if(s.godina() == m_godina) return true;
    }
    return false;
}

int Student::godina() const {return m_godina;}

Student::Stringifier::Stringifier(const Student* o) : Osoba::Stringifier(o) {
    m_data += std::to_string(o->godina()) + "\n";
}

PrivremeniZaposlenik::PrivremeniZaposlenik(const std::string& ime, const std::string& prezime, const int rMjesto, const std::string& poc,
        const std::string& kraj) : Osoba(ime, prezime), Zaposlenik(ime, prezime, rMjesto, poc), m_krajZaposlenja(kraj) {
    std::cout << "PrivremeniZaposlenik\n";
}

bool PrivremeniZaposlenik::jednak(Osoba const& o) const{
    if((*this).Zaposlenik::jednak(o)) {
        const PrivremeniZaposlenik& p = dynamic_cast<const PrivremeniZaposlenik&>(o);
        if(p.krajZaposlenja() == m_krajZaposlenja) return true;
    }
    return false;
}

PrivremeniZaposlenik::Stringifier::Stringifier(const PrivremeniZaposlenik* o) : Osoba::Stringifier(o), Zaposlenik::Stringifier(o) {
    m_data += o->krajZaposlenja().toString() + '\n';
}

Datum PrivremeniZaposlenik::krajZaposlenja() const {return m_krajZaposlenja;}

AngaziraniStudent::AngaziraniStudent(const std::string& ime, const std::string& prezime, const int rMjesto, const std::string& poc,
    const std::string& kraj, const int godina) : Osoba(ime, prezime),
    PrivremeniZaposlenik(ime, prezime, rMjesto, poc, kraj), Student(ime, prezime, godina){
    std::cout << "AngaziraniStudent\n";
}

bool AngaziraniStudent::jednak(Osoba const& o) const {
    if((*this).PrivremeniZaposlenik::jednak(o) && (*this).Student::jednak(o)) return true;
    return false;
}

AngaziraniStudent::Stringifier::Stringifier(const AngaziraniStudent* o) : Osoba::Stringifier(o),
        Student::Stringifier(o), PrivremeniZaposlenik::Stringifier(o) {}

std::ostream& operator<<(std::ostream& os, const Osoba::Stringifier &s) {
    return os << s.m_data;
}

//pomocne metode za ispis
void Osoba::print(std::ostream& out) const{
    out << Stringifier(this);
}

void Zaposlenik::print(std::ostream& out) const{
    out << Stringifier(this);
}

void Student::print(std::ostream& out) const{
    out << Stringifier(this);
}

void PrivremeniZaposlenik::print(std::ostream& out) const {
    out << Stringifier(this);
}

void AngaziraniStudent::print(std::ostream& out) const {
    out << Stringifier(this);
}


bool operator==(Osoba const & left, Osoba const & right) {
    if(typeid(left) != typeid(right)) return false;
    return left.jednak(right);
}

bool operator!=(Osoba const & left, Osoba const & right) {
    return !(left==right);
}

std::ostream & operator<<(std::ostream& out, Osoba const & o) {
    o.print(out);
    return out;
}

int main()
{
    AngaziraniStudent  as1("Ivo", "Josic", 17, "12:02:2015", "12:03:2015", 2);

    std::cout << "----------------------------------------\n";
    std::cout << as1 << std::endl;
    std::cout << "----------------------------------------\n";

    AngaziraniStudent as2(as1);
    assert(as1 == as2);

    PrivremeniZaposlenik pz1 = as2;
    std::cout << "----------------------------------------\n";
    std::cout << pz1 << std::endl;
    std::cout << "----------------------------------------\n";
    assert(pz1 != as2);

    AngaziraniStudent * pas3 = new  AngaziraniStudent("Nino", "Gusic",  16, "12:02:2015", "12:03:2015",  2);
    Student * ps = pas3;
    std::cout << ps->prezime() << std::endl;
    std::cout << "----------------------------------------\n";
    std::cout << *pas3 << std::endl;
    std::cout << "----------------------------------------\n";

    assert(as2 != *pas3);

    std::cout << "------------------\n";
    delete pas3;
    return EXIT_SUCCESS;

}
