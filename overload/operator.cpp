#include <iostream>
using namespace std;

class Complex {

private: double r, i;

public:
	Complex(double R=0, double I=0) : r{ R }, i{ I }{};
	Complex operator+(Complex &b);
	Complex operator+(int val);

	Complex operator-(Complex &b);
	Complex operator*(Complex &b);
	Complex operator/(Complex &b);
	
	// normal function, not a member function.
	friend Complex operator+(int val, Complex& b);     
	//friend Complex operator+(Complex& b, int val);


	void display();
};

// member function hide a *this, so only need a parameter 
Complex Complex::operator+(Complex &b) { return Complex(r + b.r, i + b.i); }
Complex Complex::operator+(int val) { return Complex(r + val, i); }
Complex Complex::operator-(Complex &b) { return Complex(r - b.r, i - b.i); }
Complex Complex::operator*(Complex &b) { 
	Complex t;
	t.r = r * b.r - i * b.i;
	t.i = r * b.i - i * b.r;
	return t;
}
Complex Complex::operator/(Complex &b) {
	Complex t;
	double x;
	x = 1 / (b.r * b.r + b.i * b.i);
	t.r = x * (r * b.r + i * b.i);
	t.i = x * (i * b.r - r * b.i);
	return t;
}

// note: this function is not a member function!
Complex operator+(int val, Complex& b) {
	// we can access m_cents directly because this is a friend function
	return Complex(val + b.r, b.i);
}
//Complex operator+(Complex& b, int val) {
//	// we can access m_cents directly because this is a friend function
//	return Complex(val + b.r, b.i);
//}

void Complex::display() {
	cout << r;
	if (i > 0) {
		cout << "+";
	}
	if (i != 0) {
		cout << i << "i" << '\n';
	}
}


class Cents
{
private:
	int m_cents{};

public:
	Cents(int cents): m_cents{ cents } {}

	// add Cents + Cents using a friend function
	friend Cents operator+(const Cents& c1, const Cents& c2);

	void display() const { cout << "m_cents is " << m_cents<<'\n'; }
};

// note: this function is not a member function!
Cents operator+(const Cents& c1, const Cents& c2)
{
	// use the Cents constructor and operator+(int, int)
	// we can access m_cents directly because this is a friend function
	return { c1.m_cents + c2.m_cents };
}


int main() {

	Complex c1(1, 2), c2(3, 4), c3, c4, c5, c6;
	Complex a, b(4, 3);
	Cents cents1{ 6 };
	Cents cents2{ 8 };

	a = b + 2;
	a.display();

	a = 2 + b;
	a.display();


	c3 = c1 + c2;
	c3.display();

	c4 = c1 - c2;
	c4.display();

	c5 = c1 * c2;
	c5.display();

	c6 = c1 / c2;
	c6.display();

	Cents centsSum{ cents1 + cents2 };
	centsSum.display();
	
	return 0;
}
