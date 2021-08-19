#ifndef ILRD_RD102_COMPLEX_HPP
#define ILRD_RD102_COMPLEX_HPP

#include <iosfwd>
#include <cmath>
#include <iostream>

namespace ilrd
{
class Complex
{
public:
	Complex(double real_ = 0.0, double imag_ = 0.0);

    inline Complex &operator+=(const Complex &rhs_);
    inline Complex &operator-=(const Complex &rhs_);
    inline Complex &operator*=(const Complex &rhs_);
    inline Complex &operator/=(const Complex &rhs_);

    inline double GetReal() const
    {
        return (m_real);
    }

    inline double GetImagenary() const
    {
        return (m_imag);
    }

    inline void SetReal(double real_)
    {
        m_real = real_;

        return;
    }

    inline void SetImagenary(double imag_)
    {
        m_imag = imag_;

        return;
    }

private:
    double m_real;
    double m_imag;
}; // complex

inline const Complex operator+(const Complex &lhs_, const Complex &rhs_)
{
    Complex return_complex;

    return_complex.SetReal(lhs_.GetReal() + rhs_.GetReal());
    return_complex.SetImagenary(lhs_.GetImagenary() + rhs_.GetImagenary());

    return (return_complex);
}

inline const Complex operator-(const Complex &lhs_, const Complex &rhs_)
{
    Complex return_complex;

    return_complex.SetReal(lhs_.GetReal() - rhs_.GetReal());
    return_complex.SetImagenary(lhs_.GetImagenary() - rhs_.GetImagenary());

    return (return_complex);
}

inline const Complex operator*(const Complex &lhs_, const Complex &rhs_)
{
    Complex return_complex;

    return_complex.SetReal(lhs_.GetReal() * rhs_.GetReal() - (lhs_.GetImagenary() * rhs_.GetImagenary()));
    return_complex.SetImagenary(lhs_.GetReal() * rhs_.GetImagenary() + (lhs_.GetImagenary() * rhs_.GetReal()));

    return (return_complex);
}

inline const Complex operator/(const Complex &lhs_, const Complex &rhs_)
{
    Complex return_complex;

    return_complex.SetReal((lhs_.GetReal() * rhs_.GetReal() + (lhs_.GetImagenary() * rhs_.GetImagenary())) / (pow(rhs_.GetReal(), 2) + pow(rhs_.GetImagenary(), 2)));
    return_complex.SetImagenary((lhs_.GetImagenary() * rhs_.GetReal() - (lhs_.GetReal() * rhs_.GetImagenary())) / (pow(rhs_.GetReal(), 2) + pow(rhs_.GetImagenary(), 2)));

    return (return_complex);
}

inline bool operator==(const Complex &lhs_, const Complex &rhs_)
{
    return (lhs_.GetReal() == rhs_.GetReal() && lhs_.GetImagenary() == rhs_.GetImagenary());
}

inline bool operator!=(const Complex &lhs_, const Complex &rhs_)
{
    return (lhs_.GetReal() != rhs_.GetReal() || lhs_.GetImagenary() != rhs_.GetImagenary());
}

inline std::istream &operator>>(std::istream &in, ilrd::Complex &c)
{
    double real = 0;
    double imag = 0;

    std::cout << "Enter Real Part ";
    in >> real;

    std::cout << "Enter Imaginary Part ";
    in >> imag;

    c.SetReal(real);
    c.SetImagenary(imag);

    return (in);
}

inline std::ostream &operator<<(std::ostream &out, const ilrd::Complex &c)
{
    if (c.GetReal() == 0 && c.GetImagenary() == 0)
    {
        out << '0' << std::endl;
    }

    else if (c.GetReal() == 0)
    {
        out << c.GetImagenary() << 'i' << std::endl;
    }

    else if (c.GetImagenary() > 0)
    {
        out << c.GetReal() << '+' << c.GetImagenary() << 'i' << std::endl;
    }

    else if (c.GetImagenary() < 0)
    {
        out << c.GetReal() << c.GetImagenary() << 'i' << std::endl;
    }

    else
    {
        out << c.GetReal() << std::endl;
    }

    return (out);
}

inline Complex &Complex::operator+=(const Complex &rhs_)
{
    *this = *this + rhs_;
    
    return (*this);
}

inline Complex &Complex::operator-=(const Complex &rhs_)
{
    *this = *this - rhs_;

    return (*this);
}

inline Complex &Complex::operator*=(const Complex &rhs_)
{
    *this = *this * rhs_;

    return (*this);
}

inline Complex &Complex::operator/=(const Complex &rhs_)
{
    *this = *this / rhs_;
    
    return (*this);
}
} // ilrd

#endif // ILRD_RD103_COMPLEX_HPP
