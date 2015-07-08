#ifndef __MI_H_IS_INCLUDDED__
#define __MI_H_IS_INCLUDDED__
#include<typeinfo>
#include<string>
#include<sstream>
#include<iostream>


class Datum {
public:
    Datum(const std::string& datum);
    int dan() const;
    int mjesec() const;
    int godina() const;
    const std::string toString() const;
protected:
private:
    int m_dan;
    int m_mjesec;
    int m_godina;
    void split(std::string s);
};

class Osoba {
protected:
    class Stringifier {
        friend std::ostream & operator<<(std::ostream& out, Osoba::Stringifier const & o);
    public:
        Stringifier(const Osoba* o);
    protected:
        std::string m_data;
    };
public:
    Osoba(const std::string& ime, const std::string& prezime);
    const std::string& ime() const;
    const std::string& prezime() const;
    friend bool operator==(Osoba const & left, Osoba const & right);
    friend std::ostream & operator<<(std::ostream& out, Osoba const & o);
    friend std::ostream & operator<<(std::ostream& out, Osoba::Stringifier const & o);

    virtual ~Osoba() {}
protected:
    virtual bool jednak(Osoba const& o) const;
    virtual void print(std::ostream& out) const;

private:
    std::string m_ime;
    std::string m_prezime;
};

//u klasama Zaposlenik i Student kompajler zanemaruje pozive konstruktora klase Osoba
class Zaposlenik : public virtual Osoba {
public:
    Zaposlenik(const std::string ime, const std::string prezime, const int rMjesto, const std::string& poc);
    int radnoMjesto() const;
    const Datum pocetakZaposlenja() const;
    virtual ~Zaposlenik() {}
protected:
    bool jednak(Osoba const& o) const;
    void print(std::ostream& out) const;

    class Stringifier : public virtual Osoba::Stringifier{
    public:
        Stringifier(const Zaposlenik* o);
    };
private:

    int m_radnoMjesto;
    Datum m_pocetakZaposlenja;
};

class Student : public virtual Osoba {
public:
    Student(const std::string& ime, const std::string& prezime, const int godina);
    int godina() const;
    virtual ~Student() {}
protected:
    void print(std::ostream& o) const;
    bool jednak(Osoba const& o) const;

    class Stringifier : public virtual Osoba::Stringifier{
    public:
        Stringifier(const Student* o);
    };
private:
    int m_godina;
};

class PrivremeniZaposlenik : public Zaposlenik {
public:
    PrivremeniZaposlenik(const std::string& ime, const std::string& prezime, const int rMjesto, const std::string& poc,
        const std::string& kraj);
    Datum krajZaposlenja() const;
    virtual ~PrivremeniZaposlenik() {}
protected:
    bool jednak(Osoba const& o) const;
    void print(std::ostream& out) const;

    class Stringifier : public Zaposlenik::Stringifier{
    public:
        Stringifier(const PrivremeniZaposlenik* o);
    };
private:
    Datum m_krajZaposlenja;
};

class AngaziraniStudent : public PrivremeniZaposlenik, public Student {
public:
    AngaziraniStudent(const std::string& ime, const std::string& prezime, const int rMjesto, const std::string& poc,
        const std::string& kraj, const int godina);
protected:
    bool jednak(Osoba const& o) const;
    void print(std::ostream& out) const;

    class Stringifier : public PrivremeniZaposlenik::Stringifier, public Student::Stringifier{
    public:
        Stringifier(const AngaziraniStudent* o);
    };
private:

};
#endif

