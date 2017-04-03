#ifndef __PROGTEST__

#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <climits>
#include <cmath>
#include <cfloat>
#include <cassert>
#include <unistd.h>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <complex>
#include <string>
#include <vector>
#include <algorithm>
#include <memory>

#endif /* __PROGTEST__ */

std::ios_base& dummy_polynomial_manipulator (std::ios_base& x) {
    return x;
}

std::ios_base& ( * ( polynomial_variable (const std::string& varName))) (std::ios_base& x) {
    return dummy_polynomial_manipulator;
}

class CPolynomial {
public:
    CPolynomial ();
    ~CPolynomial ();
    CPolynomial operator + (const CPolynomial& polynomial);
    CPolynomial operator - (const CPolynomial& polynomial);
    CPolynomial operator * (const CPolynomial& polynomial);
    CPolynomial operator * (const double& number);
    bool operator == (const CPolynomial& polynomial) const;
    bool operator != (const CPolynomial& polynomial) const;
    double& operator [] (const unsigned int& number);
    const double& operator [] (const unsigned int& number) const;
    double operator () (const double& number);
    friend std::ostream& operator << (std::ostream& os, const CPolynomial& polynomial);
    friend bool dumpMatch (const CPolynomial& x, const std::vector<double>& ref);
    unsigned int Degree ();
private:
    std::vector<double> levelList = {0};
};

CPolynomial::CPolynomial () {

}

CPolynomial::~CPolynomial () {

}

CPolynomial CPolynomial::operator + (const CPolynomial& polynomial) {
    CPolynomial result;

    const std::vector<double>& bigger = ((levelList.size() < polynomial.levelList.size()) ? polynomial.levelList : levelList);
    const std::vector<double>& smaller = ((levelList.size() < polynomial.levelList.size()) ? levelList : polynomial.levelList);

    result.levelList.resize(bigger.size());

    for (unsigned int i = 0; i < smaller.size(); ++i) {
        result.levelList[i] = levelList[i] + polynomial.levelList[i];
    }

    for (unsigned int i = (unsigned int) smaller.size(); i < bigger.size(); ++i) {
        result.levelList[i] = bigger[i];
    }

    return result;
}

CPolynomial CPolynomial::operator - (const CPolynomial& polynomial) {
    CPolynomial result;

    const std::vector<double>& bigger = ((levelList.size() < polynomial.levelList.size()) ? polynomial.levelList : levelList);
    const std::vector<double>& smaller = ((levelList.size() < polynomial.levelList.size()) ? levelList : polynomial.levelList);

    result.levelList.resize(bigger.size());

    for (unsigned int i = 0; i < smaller.size(); ++i) {
        result.levelList[i] = levelList[i] - polynomial.levelList[i];
    }

    for (unsigned int i = (unsigned int) smaller.size(); i < bigger.size(); ++i) {
        if (bigger == levelList) {
            result.levelList[i] = levelList[i];
        } else {
            result.levelList[i] = - polynomial.levelList[i];
        }
    }

    return result;
}

CPolynomial CPolynomial::operator * (const CPolynomial& polynomial) {
    return *this;
}

CPolynomial CPolynomial::operator * (const double& number) {
    for (unsigned int i = 0; i < levelList.size(); ++i) {
        levelList[i] *= number;
    }

    return *this;
}

bool CPolynomial::operator == (const CPolynomial& polynomial) const {
    return false;
}

bool CPolynomial::operator != (const CPolynomial& polynomial) const {
    return false;
}

double& CPolynomial::operator [] (const unsigned int& index) {
    if (levelList.size() <= index) {
        levelList.resize(index + 1);
    }

    return levelList[index];
}

const double& CPolynomial::operator [] (const unsigned int& index) const {
    return levelList[index];
}

double CPolynomial::operator () (const double& value) {
    double result = 0;

    for (unsigned int i = 0; i < levelList.size(); ++i) {
        result += levelList[i] * (std::pow(value, i));
    }

    return result;
}

std::ostream& operator << (std::ostream& os, const CPolynomial& polynomial) {
    if (polynomial.levelList.size() == 1) {
        os << "0";
    }

    for (long int i = polynomial.levelList.size() - 1; i >= 0; i--) {
        if (polynomial.levelList[i] == 0) {
            continue;
        }

        bool isFirst = (i == (long int) (polynomial.levelList.size() - 1));

        if (i == 0) {
            if (polynomial.levelList[i] < 0) {
                os << ((isFirst) ? "- " : " - ") << -polynomial.levelList[i];
            } else {
                os << ((isFirst) ? "" : " + ") << polynomial.levelList[i];
            }

            continue;
        }

        if (polynomial.levelList[i] == 1) {
            os << ((isFirst) ? "x^" : " + x^") << i;
        } else if (polynomial.levelList[i] == -1) {
            os << ((isFirst) ? "- x^" : " - x^") << i;
        } else if (polynomial.levelList[i] < 0) {
            os << ((isFirst) ? "- " : " - ") << -polynomial.levelList[i] << "*x^" << i;
        } else {
            os << ((isFirst) ? "" : " + ") << polynomial.levelList[i] << "*x^" << i;
        }
    }

    return os;
}

unsigned int CPolynomial::Degree () {
    return (unsigned int) levelList.size() - 1;
}

#ifndef __PROGTEST__

bool smallDiff (double a, double b) {
    return std::abs(a - b) < 0.000001;
}

bool dumpMatch (const CPolynomial& x, const std::vector<double>& ref) {
    return std::equal(x.levelList.begin(), x.levelList.end(), ref.begin());
}

int main (void) {
    CPolynomial a, b, c, d;
    std::ostringstream out;

    a[0] = -10;
    a[1] = 3.5;
    a[3] = 1;
    assert (smallDiff(a(2), 5));
    out.str("");
    out << a;
    assert (out.str() == "x^3 + 3.5*x^1 - 10");
    a = a * -2;
    assert (a.Degree() == 3 && dumpMatch(a, std::vector<double>{20.0, -7.0, -0.0, -2.0}));

    out.str("");
    out << a;
    assert (out.str() == "- 2*x^3 - 7*x^1 + 20");
    out.str("");
    out << b;
    assert (out.str() == "0");
    b[5] = -1;
    out.str("");
    out << b;
    assert (out.str() == "- x^5");
    c = a + b;
    assert (c.Degree() == 5 && dumpMatch(c, std::vector<double>{20.0, -7.0, 0.0, -2.0, 0.0, -1.0}));

    out . str ("");
    out << c;
    assert ( out . str () == "- x^5 - 2*x^3 - 7*x^1 + 20" );
    c = a - b;
    assert ( c . Degree () == 5 && dumpMatch ( c, std::vector<double>{ 20.0, -7.0, -0.0, -2.0, -0.0, 1.0 } ) );
    d = b - a;
    assert ( d . Degree () == 5 && dumpMatch ( d, std::vector<double>{ -20.0, +7.0, +0.0, +2.0, +0.0, -1.0 } ) );

    out . str ("");
    out << c;
    assert ( out . str () == "x^5 - 2*x^3 - 7*x^1 + 20" );
    c = a * b;
    assert ( c . Degree () == 8 && dumpMatch ( c, std::vector<double>{ 0.0, -0.0, 0.0, -0.0, -0.0, -20.0, 7.0, 0.0, 2.0 } ) );

    /*
    CPolynomial a, b, c;
    ostringstream out;

    a[0] = -10;
    a[1] = 3.5;
    a[3] = 1;
    assert ( smallDiff ( a ( 2 ), 5 ) );
    out . str ("");
    out << a;
    assert ( out . str () == "x^3 + 3.5*x^1 - 10" );
    a = a * -2;
    assert ( a . Degree () == 3 && dumpMatch ( a, std::vector<double>{ 20.0, -7.0, -0.0, -2.0 } ) );

    out . str ("");
    out << a;
    assert ( out . str () == "- 2*x^3 - 7*x^1 + 20" );
    out . str ("");
    out << b;
    assert ( out . str () == "0" );
    b[5] = -1;
    out . str ("");
    out << b;
    assert ( out . str () == "- x^5" );
    c = a + b;
    assert ( c . Degree () == 5 && dumpMatch ( c, std::vector<double>{ 20.0, -7.0, 0.0, -2.0, 0.0, -1.0 } ) );

    out . str ("");
    out << c;
    assert ( out . str () == "- x^5 - 2*x^3 - 7*x^1 + 20" );
    c = a - b;
    assert ( c . Degree () == 5 && dumpMatch ( c, std::vector<double>{ 20.0, -7.0, -0.0, -2.0, -0.0, 1.0 } ) );

    out . str ("");
    out << c;
    assert ( out . str () == "x^5 - 2*x^3 - 7*x^1 + 20" );
    c = a * b;
    assert ( c . Degree () == 8 && dumpMatch ( c, std::vector<double>{ 0.0, -0.0, 0.0, -0.0, -0.0, -20.0, 7.0, 0.0, 2.0 } ) );

    out . str ("");
    out << c;
    assert ( out . str () == "2*x^8 + 7*x^6 - 20*x^5" );
    assert ( a != b );
    b[5] = 0;
    assert ( !(a == b) );
    a = a * 0;
    assert ( a . Degree () == 0 && dumpMatch ( a, std::vector<double>{ 0.0 } ) );

    assert ( a == b );

    // bonus
    a[2] = 4;
    a[1] = -3;
    b[3] = 7;
    out . str ("");
    out << polynomial_variable ( "y" ) << "a=" << a << ", b=" << b;
    assert ( out . str () == "a=4*y^2 - 3*y^1, b=7*y^3" );

    out . str ("");
    out << polynomial_variable ( "test" ) << c;
    assert ( out . str () == "2*test^8 + 7*test^6 - 20*test^5" );
    */
    return 0;
}

#endif /* __PROGTEST__ */