#include"vect.h"
#include<memory>
#include<cmath>

std::allocator<double> Vect::alloc;
using std::cout;
using std::endl;
// Konstruktor
// Tek ako je zadano n>0 alociramo memoriju
Vect::Vect(size_t n, double v, std::string const & vec_name) :
        ime(vec_name), mdata(nullptr), mfirst_free(nullptr), mend(nullptr) {
    std::cerr << "Ctor"<<std::endl;
    if(n > 0) {
        mdata = alloc.allocate(n);
        for(size_t i=0; i<n; ++i)
            alloc.construct(mdata+i, v);
        mfirst_free = mend = mdata+n;
    }
}

//Kontrola kopiranja
//Copy constructor kopiranjem
Vect::Vect(const Vect& v) : ime(v.ime), mdata(nullptr), mend(nullptr), mfirst_free(nullptr) {
	cout << "CCtor" << endl;
    if(v.size() == 0) return;
    mdata = alloc.allocate(v.size());
    for(size_t i = 0; i < v.size(); ++i) {
        mdata[i] = v.mdata[i];
    }
    mfirst_free = mend = mdata + v.size();
}

//Operator pridruzivanja kopiranjem
Vect& Vect::operator=(const Vect& v) {
    if(mdata == v.mdata) return *this;
    free();
    ime = v.ime;
    mdata = alloc.allocate(v.size());
    for(size_t i = 0; i < v.size(); ++i) {
        mdata[i] = v.mdata[i];
    }
    mfirst_free = mend = mdata + v.size();
    return *this;
}

//Copy constructor premjestanjem
Vect::Vect(Vect&& v) noexcept : ime(std::move(v.ime)), mdata(v.mdata),
        mfirst_free(v.mfirst_free), mend(v.mend) {
        cout << "MCtor" << endl;
    v.mdata = v.mfirst_free = v.mend = nullptr;
}

//Operator pridruzivanja premjestanjem
Vect& Vect::operator=(Vect && v) noexcept  {
    if(mdata != v.mdata) {
        free();
        ime = std::move(v.ime);
        mdata = v.mdata;
        mfirst_free = v.mfirst_free;
        mend = v.mend;
        v.mdata = v.mfirst_free = v.mend = nullptr;
    }
    return *this;
}
//kraj kontrole kopiranja

void Vect::reallocate() {
    double* tmp;
    //prazan
     if(capacity() == 0) {
        mdata = alloc.allocate(1);
        mend = mdata + 1;
        mfirst_free = mdata;
        return;
    }

    tmp = alloc.allocate(2 * capacity());
    size_t novi_cap = 2 * capacity(), nova_velicina = capacity();

    std::uninitialized_copy(mdata, mdata + size(), tmp);
    free();
    mdata = tmp;
    mfirst_free = tmp + nova_velicina;
    mend = tmp + novi_cap;

}

void Vect::free() {
    if(mdata == nullptr) return;
    for(int i = 0; i < capacity(); ++i) {
        alloc.destroy(&mdata[i]);
    }
    alloc.deallocate(mdata, capacity());
}

void Vect::print(std::ostream& out) const {
    out<< ime << ": (" << size() << "," << capacity()<<") ";
    for(size_t i=0; i < size(); ++i) {
        out << mdata[i];
        if(i+1 < size()) out << ",";
    }
}

void Vect::push_back(double x){
    if( !has_space() )
        reallocate();
    alloc.construct(mfirst_free++, x);
}

Vect& Vect::scale(double alpha) {
    for(size_t i = 0; i < size(); ++i) {
        mdata[i] *= alpha;
    }
    return *this;
}

double Vect::norm2() const {
    double norm = 0;
    for(size_t i = 0; i < size(); ++i) {
        norm += mdata[i] * mdata[i];
    }
    return sqrt(norm);
}
