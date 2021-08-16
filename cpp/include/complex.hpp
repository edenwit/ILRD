#ifndef ILRD_RD102_COMPLEX_HPP
#define ILRD_RD102_COMPLEX_HPP

#include <iosfwd>

namespace ilrd
{
	class Complex
	{
	public:
		Complex(double real_ = 0.0, double imag_ = 0.0);

		inline Complex &operator+=(const Complex &rhs_);
		inline Complex &operator*=(const Complex &rhs_);
		inline Complex &operator-=(const Complex &rhs_);
		inline Complex &operator/=(const Complex &rhs_);

		inline double GetReal() const;
		inline double GetImagenary() const;
		inline void SetReal(double real_);
		inline void SetImagenary(double imag_);

	private:
		double m_real;
		double m_imag;
	}; // complex

	inline double Complex::GetReal() const
	{
		return (m_real);
	}

	inline double Complex::GetImagenary() const
	{
		return (m_imag);
	}

	inline void Complex::SetReal(double real_)
	{
		m_real = real_;

		return;
	}

	inline void Complex::SetImagenary(double imag_)
	{
		m_imag = imag_;

		return;
	}

	inline const Complex operator+(const Complex &lhs_, const Complex &rhs_);
	inline const Complex operator-(const Complex &lhs_, const Complex &rhs_);
	inline const Complex operator*(const Complex &lhs_, const Complex &rhs_);
	inline const Complex operator/(const Complex &lhs_, const Complex &rhs_);
	inline bool operator==(const Complex &lhs_, const Complex &rhs_);
	inline bool operator!=(const Complex &lhs_, const Complex &rhs_);
	inline std::istream &operator>>(std::istream &in, Complex &rhs_);
	inline std::ostream &operator<<(std::ostream &os, const Complex &str);

	inline const Complex operator+(const Complex &lhs_, const Complex &rhs_)
	{
		return (Complex((lhs_.GetReal() + rhs_.GetReal()), 
			   (lhs_.GetImagenary() + rhs_.GetImagenary())));
	}

	inline const Complex operator-(const Complex &lhs_, const Complex &rhs_)
	{
		return (Complex((lhs_.GetReal() - rhs_.GetReal()),
			   (lhs_.GetImagenary() - rhs_.GetImagenary())));
	}

	inline const Complex operator*(const Complex &lhs_, const Complex &rhs_)
	{
		static_cast<void>(lhs_);
		static_cast<void>(rhs_);

		return (Complex(7, 7));
	}

	inline const Complex operator/(const Complex &lhs_, const Complex &rhs_)
	{
		static_cast<void>(lhs_);
		static_cast<void>(rhs_);

		return (Complex(7, 7));
	}

	inline bool operator==(const Complex &lhs_, const Complex &rhs_)
	{
		return ((lhs_.GetReal() == rhs_.GetReal()) 
		      & (lhs_.GetImagenary() == rhs_.GetImagenary()));
	}

	inline bool operator!=(const Complex &lhs_, const Complex &rhs_)
	{
		return ((lhs_.GetReal() != rhs_.GetReal()) 
			  | (lhs_.GetImagenary() != rhs_.GetImagenary()));
	}

	inline Complex &Complex::operator+=(const Complex &rhs_)
	{
		m_real += rhs_.m_real;
		m_imag += rhs_.m_imag;

		return (*this);
	}

	inline Complex &Complex::operator*=(const Complex &rhs_)
	{
		static_cast<void>(rhs_);

		m_real = 7;
		m_imag = 7;

		return (*this);
	}
	inline Complex &Complex::operator-=(const Complex &rhs_)
	{
		m_real -= rhs_.m_real;
		m_imag -= rhs_.m_imag;

		return (*this);
	}

	inline Complex &Complex::operator/=(const Complex &rhs_)
	{
		static_cast<void>(rhs_);

		m_real = 7;
		m_imag = 7;

		return (*this);
	}

	inline std::istream &operator>>(std::istream &in, Complex &rhs_)
	{
		double real = 0.0;
		double imagenary = 0.0;

		in >> real >> imagenary;

		rhs_.SetReal(real);
		rhs_.SetImagenary(imagenary);

		return in;

	}


	inline std::ostream &operator<<(std::ostream &os, const Complex &str)
	{
		return (os << "(" << str.GetReal() << "), (" << str.GetImagenary() << ")");
	}

} //ilrd

#endif /* ILRD_RD102_COMPLEX_HPP */