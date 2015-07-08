#include<array>

class Scalar;

template <typename T>
struct Traits{
   typedef T const& ExprRef;
};

template <>
struct Traits<Scalar>{
   typedef Scalar  ExprRef;
};

class Scalar{
private:
	double  const & val;
public:
	Scalar(double const& v) : val(v) {}
	double operator[](size_t) const { return val; }
	friend std::ostream& operator<<(std::ostream& os, Scalar const& v);
};

std::ostream& operator<<(std::ostream& os, Scalar const& s) {
    return os << "(" << s[0] << ")";

}

template <typename T, size_t dim>
std::ostream& operator<<(std::ostream &os, const std::array<T, dim>&) { return os << "Array<" << dim << ">"; }

template <size_t N, typename Rep = std::array<double,N> >
class Vector{
private:
    Rep expr_rep;  // Implementacijski objekt
public:
	// Konstruktor inicijalizira implementacijski objekt
	Vector(Rep const& r) : expr_rep(r) {}
	// Vektor možemo inicijalizirati konstantom.
	explicit Vector(double val = 0.0) {expr_rep.fill(val);}
    // pridruživanje polja različitog tipa
    template <typename Rep2>
    Vector& operator=(Vector<N,Rep2> const& rhs){
        for(size_t i=0; i < N; ++i) expr_rep[i]= rhs[i];
        return *this;
    }
    // Pomoćne funkcije
    size_t size() const { return N; }
	double operator[](size_t i) const {  return expr_rep[i]; }
	double& operator[](size_t i) { return expr_rep[i]; }
	Rep const& rep() const { return expr_rep; }
	Rep& rep() { return expr_rep; }
};

template <size_t dim, typename Rep>
std::ostream& operator<<(std::ostream &os, const Vector<dim, Rep> &v) { return os << v.rep(); }
template <size_t dim>
std::ostream& operator<<(std::ostream &os, const Vector<dim> &v) {
    os << '(';
    for (size_t i = 0; i < dim - 1; ++i) os << v[i] << ',';
    os << v[dim-1] << ')';
    return os;
}

//reprezentacije
template <typename OP1, typename OP2>
class Add{
private:
    typename Traits<OP1>::ExprRef op1;
	typename Traits<OP2>::ExprRef op2;
public:
	Add(OP1 const& a, OP2 const& b) : op1(a), op2(b) {}
	double operator[](int i) const { return op1[i]+op2[i]; }
	friend std::ostream& operator<<(std::ostream &os, const Add &rep) {
        return os << "Add<" << rep.op1 << ',' << rep.op2 << '>';
    }
};

template <typename OP1, typename OP2>
class Sub{
private:
    typename Traits<OP1>::ExprRef op1;
	typename Traits<OP2>::ExprRef op2;
public:
	Sub(OP1 const& a, OP2 const& b) : op1(a), op2(b) {}
	double operator[](int i) const { return op1[i] - op2[i]; }
	friend std::ostream& operator<<(std::ostream &os, const Sub &rep) {
        return os << "Sub<" << rep.op1 << ',' << rep.op2 << '>';
    }
};

template <typename OP1, typename OP2>
class Mult{
private:
    typename Traits<OP1>::ExprRef op1;
	typename Traits<OP2>::ExprRef op2;
public:
	Mult(OP1 const& a, OP2 const& b) : op1(a), op2(b) {}
	double operator[](int i) const { return op1[i] * op2[i]; }
    friend std::ostream& operator<<(std::ostream &os, const Mult &rep) {
        return os << "Mult<" << rep.op1 << ',' << rep.op2 << '>';
    }
};

//operatori
//zbrajanje vektora
template <size_t N,   typename R1, typename R2>
Vector<N, Add<R1,R2> >
operator+(Vector<N,R1> const& a, Vector<N,R2> const& b){
    return Vector<N, Add<R1,R2> >( Add<R1,R2>( a.rep(),b.rep() ) );
}

//zbrajanje vektora skalarom
template <size_t N, typename R2>
Vector<N, Add<R2, Scalar> >
operator+(Vector<N,R2> const& b, double const& a){
    return Vector<N,Add<R2, Scalar> >(Add<R2, Scalar>(b.rep(), Scalar(a)) );
}

//zbrajanje vektora skalarom
template <size_t N, typename R2>
Vector<N, Add<Scalar, R2> >
operator+(double const& a, Vector<N,R2> const& b){
    return Vector<N,Add<Scalar, R2> >(Add<Scalar, R2>(Scalar(a), b.rep()) );
}

//mnozenje vektora
template <size_t N,   typename R1, typename R2>
Vector<N, Mult<R1,R2> >
operator*(Vector<N,R1> const& a, Vector<N,R2> const& b){
    return Vector<N, Mult<R1,R2> >( Mult<R1,R2>( a.rep(),b.rep() ) );
}

//mnozenje skalara vektorom
template <size_t N, typename R2>
Vector<N, Mult<Scalar,R2> >
operator*(double const& a, Vector<N,R2> const& b){
    return Vector<N,Mult<Scalar,R2> >( Mult<Scalar,R2>( Scalar(a), b.rep() ) );
}

//mnozenje vektora skalarom
template <size_t N, typename R2>
Vector<N, Mult<R2, Scalar> >
operator*(Vector<N,R2> const& b, double const& a){
    return Vector<N,Mult<R2, Scalar> >( Mult<R2, Scalar>(b.rep(), Scalar(a)) );
}

//oduzimanje vektora
template <size_t N,   typename R1, typename R2>
Vector<N, Sub<R1,R2> >
operator-(Vector<N,R1> const& a, Vector<N,R2> const& b){
    return Vector<N, Sub<R1,R2> >( Sub<R1,R2>( a.rep(),b.rep() ) );
}

//oduzimanje vektora od skalara
template <size_t N, typename R2>
Vector<N, Sub<Scalar,R2> >
operator-(double const& a, Vector<N,R2> const& b){
    return Vector<N,Sub<Scalar,R2> >( Sub<Scalar,R2>( Scalar(a), b.rep() ) );
}
