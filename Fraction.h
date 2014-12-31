//fraction.cpp


#ifndef FRACTION_H
#define FRACTION_H

#include <iostream>
#include <iomanip>
#include <string>
#include <cctype>
#include <typeinfo>
#include <exception>
#include <stdexcept>
#include <climits>
#include <limits>
#include <sstream>


using namespace std;

class Fraction
{


/*=================================	FRIEND FUNCTIONS (MOSTLY OPERATORS) ================================
 *======================================================================================================

  These are the overloaded operator functions for a Fraction object as the RIGHT HAND operand. See the
  section OPERATORS below for the LEFT HAND operand functions which are used to implement the following*/

//++++++++ Stream operators ++++++++//
	
	// Stream insertion
	friend ostream &operator<< ( ostream &output, const Fraction &frac);
	
	// Stream extraction
	friend istream &operator>> ( istream &input, Fraction &frac );

//++++++++ Left-hand arithmetic operators ++++++++//

	// Addition
	friend Fraction operator+ ( const long long &num, Fraction &frac );
	
	// Subtraction
	friend Fraction operator- ( const long long &num, Fraction &frac );
	
	// Multiplication
	friend Fraction operator* ( const long long &num, Fraction &frac );
	
	// Division
	friend Fraction operator/ ( const long long &num , Fraction &frac );
	
//++++++++ Equality Operators ++++++++//

	// Is equal check: num == fraction
	friend bool operator== ( const long long &num, Fraction &frac );
	
	// Is not equal check: num != fraction
	friend bool operator!= ( const long long &num, Fraction &frac );
	
	// Is larger than: num > fraction
	friend bool operator> ( const long long &num, Fraction &frac );
	
	// Is lesser than: num < fraction
	friend bool operator< ( const long long &num, Fraction &frac );
	
	// Is larger or equal to: num >= fraction
	friend bool operator>= ( const long long &num, Fraction &frac );
	
	// Is smaller or equal to: num <= fraction
	friend bool operator<= ( const long long &num, Fraction &frac );
	
	
public:

/*====================================	CONSTRUCTORS  ==================================================
 *======================================================================================================*/
	
	/* Default constructor: defaults to 1 / 1. Also functions as constructor from an integer,
	 * because the denominator defaults to 1. */
	Fraction ( const long long &n = 1, const long long &d = 1 );
	
	/* Copy constructor: creates a new  from another fraction. */
	Fraction ( const Fraction &frac );
	
	/* Construct using a string */
	Fraction ( const string &str  );
	
	Fraction ( const string &str1, const string &str2 );
	
	/* NOTE: conversion from a floating point is not yet implemented owing to floating point
	 *       representation issues. Future editions of this class will implement big integers
	 *       and arbitrary precision floating point numbers.
	 */
	
	
/*====================================	OPERATORS ======================================================
 *======================================================================================================*/
 
/*These are the operator functions for THIS as the LEFT operand, or as the operad of a unary operator.
 *The RIGHT operand functions are defined as FRIENDS (see above), and are implemented using the following
 *as utilities. 
 */

//++++++++ Simple assignment ++++++++//

	// Assign from another fraction
	void operator= ( const Fraction &frac );
	
	// Assign an int
	void operator= ( const long long & num );
 
//++++++++ Right-hand arithmetic operators ++++++++//

	// Addition: fraction + fraction
	Fraction operator+ ( const Fraction &frac ) const;
	
	// Addition: fraction + integer
	Fraction operator+ ( const long long &num ) const;
	
	// Subtraction: fraction - fraction
	Fraction operator- ( const Fraction &frac ) const;
	
	// Subtraction: fraction - integer
	Fraction operator- ( const long long &num) const;
	
	// Multiplication: fraction * fraction
	Fraction operator* ( const Fraction &frac ) const;
	
	// Multiplication: fraction * integer
	Fraction operator* ( const long long &num) const;
	
	// Division: fraction / fraction
	Fraction operator/ ( const Fraction &frac ) const;
	
	// Division: fraction / integer
	Fraction operator/ ( const long long &num ) const;
	
	// Power: fraction ^ num
	/* NOTE: operator^ has lower precedence than regular arithmetic operators in C++.
	 *       ALWAYS enclose a fraction "A" in parenthesis when putting the the power of
	 *       an integer "c" in an expression containing other operators, as in :
				
	 *			Wrong:  a ^ c + b  will yield a ^ (c + b)
	 *			Right: (a ^ c) + b
	 */
	Fraction operator^ ( const long long &num ) const;
	
	// Power: identical to above, but does not require () in operator precedence. Not so nice looking though...
	Fraction operator~ ( const long long &num ) const;
	
//++++++++ Increment and Decrement operators ++++++++//

	// Prefix increment: ++fraction
	Fraction &operator++ ();
	
	// Postfix increment: fraction++
	Fraction operator++ ( int = 0 );
	
	// Prefix decrement: --fraction
	Fraction &operator-- ();
	
	// Postfix decrement: fraction --
	Fraction operator-- ( int = 0 );
	
	// Unary minus
	Fraction operator- () const // unary minus
	{
		Fraction temp( -getNumerator(), getDenominator() );
		return temp;
	}	// unary minus 
	
//++++++++ Left-hand equality operators ++++++++//

	// Is equal check: Fraction == Fraction
	bool operator== ( const Fraction &frac ) const;

	// Is equal check: Fraction == integer
	bool operator== ( const long long &num ) const;
	
	// Is not equal check: fraction != fraction
	bool operator!= ( const Fraction &frac ) const;
	
	// Is not equal check: fraction != integer
	bool operator!= ( const long long &num ) const;
	
	// Is smaller than check: Fraction < fraction
	bool operator< (const Fraction &frac ) const;
	
	// Is smaller than check: fraction < integer
	bool operator< (const long long &num ) const;
	
	// Is larger than check: fraction > fraction
	bool operator> (const Fraction &frac ) const;
	
	// Is larger than check: fraction > integer
	bool operator> (const long long &num ) const;
	
	// Is smaller than or equal to check: fraction <= fraction
	bool operator<= (const Fraction &frac ) const;
	
	// Is smaller than or equal to check: fraction <= integer
	bool operator<= (const long long &num ) const;
	
	// Is larger than or equal to check: fraction >= fraction
	bool operator>= (const Fraction &frac ) const;
	
	// Is larger than or equal to check: fraction >= integer
	bool operator>= (const long long &num ) const;

//++++++++ Compound assignment operators ++++++++//

	// Plus equals fraction
	Fraction operator+= ( const Fraction &frac );
	
	// Plus equals integer
	Fraction operator+= ( const long long &num );
	
	// Minus equals fraction
	Fraction operator-= ( const Fraction &frac );
	
	// Minus equals integer
	Fraction operator-= ( const long long &num );
	
	// Times equals fraction
	Fraction operator*= ( const Fraction &frac );
	
	// Times equals integer
	Fraction operator*= ( const long long &num );
	
	// Divide equals fraction
	Fraction operator/= ( const Fraction &frac );
	
	// Divide equals integer
	Fraction operator/= ( const long long &num );
	
	// Power equals integer
	Fraction operator^= ( const long long &num );


/*====================================	SET AND GET ====================================================
 *======================================================================================================*/

// ++++++++ Set ++++++++/

	// Set numerator and denominator in one go as integers
	void set( const long long &n, const long long &d );
	
	// Set using a fraction
	void set ( const Fraction &frac );
	
	// Set using 1 string
	void set ( const string & str );
	
	//set using more than one string
	void set ( const string & str1, const string & str2 );
	
	// Set numerator
	void setNumerator( const long long &n = 1);
	
	// Set denominator
	void setDenominator( const long long &d = 1);

//++++++++ Get ++++++++//

	// Get returns a fraction
	Fraction get() const;
	
	// getNumerator returns numerator as an integer
	long long getNumerator() const;
	
	// getDenominator returns denominator as an integer
	long long getDenominator() const;
	
	// getNumerAsFrac returns the numerator as fraction 'numerator / 1'
	Fraction getNumerAsFrac() const;
	
	// getDenomAsFrac returns the denominator as fraction '1 / denominator'
	Fraction getDenomAsFrac() const;
	
/*====================================	ARITHMETIC =====================================================
 *======================================================================================================*/

/*NOTE: these arithmetic methods alter the object for which they are called. */

	// Add integer
	void add( const long long &num);
	
	// Add Fraction
	void add( const Fraction &frac );
	
	// Subtract integer
	void sub( const long long &num);
	
	// Subtract fraction
	void sub( const Fraction &frac);
	
	// Multiply by integer
	void mul( const long long &num);
	
	// Multiply by fraction
	void mul( const Fraction &frac);
	
	// Divide by integer
	void div( const long long &num );
	
	// Divide by fraction
	void div( const Fraction &frac );
	
	// Put to the power of an integer
	void pow( const long long &num );
	
	
/*====================================	ARITHMETIC UTILITIES ===========================================
 *======================================================================================================*/
 
	// Simplify (reduce) the fraction
	void simplify();
	
	// Scales the fraction up by an integer factor
	// Throws invalid_argument exception if the factor is smaller than 1
	void scaleUp(const long long &factor);
	
	// Scales the fraction down by an integer factor
	// Throws invalid_argument exception if the factor is smaller than 1
	// Throws invalid_argument exception if the factor does not divide both numerator and denominator
	void scaleDown( const long long &factor );
	
	// Returns the smallest common denominator that the object has with another fraction object
	long long scd(const Fraction &other) const;
	
	// Sets the fraction to its reciprocal (i.e. ( num / denom ) ^ -1 )
	void reciprocal ();
	
	// Increment
	void increment();
	
	//Decrement
	void decrement();
	
/*====================================	MISCELLANEOUS ==================================================
 *======================================================================================================*/
	
	// Checks if the fraction is a whole number
	bool isInteger() const;
	
	// Returns the the integer if it is whole
	long long integer() const;
	
	// Returns the double that it represents
	long double decimal() const;
	
	// Returns the fraction in the form a "a / b" string
	string str() const;
	
private:

	long long numerator;
	long long denominator;

/*====================================	PROTECTED UTILITIES ==============================================
 *======================================================================================================*/

protected:

	// Returns the Greatest Common Divisor of two numbers -- thanks, Euclid!!!
	long long gcd(long long a, long long b)
	{
		long long c = a % b;
		while(c != 0)
		{
			a = b;
			b = c;
			c = a % b;
		}
		return b;
	}
	
	// Integer absolute value implementation
	long long abs_( long long i )
	{
		if( i == 0 ) return 0;
		if( i > 0 ) return i;
		if( i < 0 ) return -i;
	}
	
};

#endif
