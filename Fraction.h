//full body fraction header


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

/*=====================================	A NOTE ABOUT THIS HEADER =======================================
 *======================================================================================================
  
  FEATURES:
  
  This header implements a class for representing and manipulating rational numbers.
  It features:
	-- Full operator overloading to allow intuitive mathematical expressions, including ^ as a power
	   operator.
	-- Strict denominator checking to ensure that the denominator is never 0
	-- Fraction reduction at every step, except for in two methods scaleUp and scaleDown (should be
	   pretty obvious that if you want to scale, you don't want to simplify...)
	-- Construction from integers, other fractions, and strings
	-- Member functions to check various attributes of the object
	-- Member functions to return as integer, floating point, and string representations
	-- If a fraction is negative, the sign is always stored in the numerator.
	
  ARITHMETIC AND OPERATORS
  
  The class is implemented such that all arithmetic member functions such as .add(...), .sub(...), etc,
  modify the object for which they are called without returning.
  Operators invoked do not modify the object ( except for assignment, compound assignment, and
  increment and decrement, of course).
  Incrementing and decrementing adds a fraction of value of 1. eg: (3 / 4)++ is 7 / 4
  The stream insertion operator MUST read strings in the form "a / b" with the slash included. Omitting
  the slash will result in error. This will be retinkered later.
  The operator ^ is of lower precedence than arithmetic operators in C/C++. Therefore, to achieve PEDMAS
  ordering, you MUST place parentheses around an expression containing a power. The ~ operator, which is
  higher in precedence than the arithmetic operators, has also been overloaded as a power operator 
  and works with PEDMAS. But this is a bit less intuitive and appealing to the eye. Use the one you prefer.
  
  FUTURE CHANGES
  
  The next version of this class header will also come with a interface and body. However, this is not
  possible right now due to problems encountered while linking for testing that setup.
  
  Another change is to allow for more flexible string operations; especially constructing and reading using
  strings.
  
  The main change that will be implemented is to represent the fraction using arbitrary length integers, and
  to construct using arbitrary precision floating points. This will eliminate the need to raise exceptions for
  out of bounds integers, and will allow correct creation of a fraction from floating point numbers.

 */






/*=================================	FRIEND FUNCTIONS (MOSTLY OPERATORS) ================================
 *======================================================================================================

  These are the overloaded operator functions for a Fraction object as the RIGHT HAND operand. See the
  section OPERATORS below for the LEFT HAND operand functions which are used to implement the following*/

//++++++++ Stream operators ++++++++//
	
	// Stream insertion
	friend ostream &operator<< ( ostream &output, const Fraction &frac)
	{
		output << frac.str();
		return output;
	}
	
	// Stream extraction
	friend istream &operator>> ( istream &input, Fraction &frac )
	{
		long long n, d;
		input >> n;
		input.ignore ( std::numeric_limits<streamsize>::max() , '/' );
		input >> d;
		frac.set( n, d );
		return input;
	}

//++++++++ Left-hand arithmetic operators ++++++++//

	// Addition
	friend Fraction operator+ ( const long long &num, Fraction &frac ) 
	{
		return (frac + num);
	}
	
	// Subtraction
	friend Fraction operator- ( const long long &num, Fraction &frac )
	{
		return -( frac - num );
	}
	
	// Multiplication
	friend Fraction operator* ( const long long &num, Fraction &frac )   
	{
		return (frac * num);
	}
	
	// Division
	friend Fraction operator/ ( const long long &num , Fraction &frac )
	{
		Fraction temp = frac / num;
		temp.reciprocal();
		return temp;
	}
	
//++++++++ Equality Operators ++++++++//

	// Is equal check: num == fraction
	friend bool operator== ( const long long &num, Fraction &frac )
	{
		return (frac == num);
	}
	
	// Is not equal check: num != fraction
	friend bool operator!= ( const long long &num, Fraction &frac )
	{
		(frac != num);
	}
	
	// Is larger than: num > fraction
	friend bool operator> ( const long long &num, Fraction &frac )
	{
		return (frac < num);
	}
	
	// Is lesser than: num < fraction
	friend bool operator< ( const long long &num, Fraction &frac )
	{
		return (frac > num);
	}
	
	// Is larger or equal to: num >= fraction
	friend bool operator>= ( const long long &num, Fraction &frac )
	{
		return (frac <= num);
	}
	
	// Is smaller or equal to: num <= fraction
	friend bool operator<= ( const long long &num, Fraction &frac )
	{
		return (frac >= num);
	}
	
	
public:

/*====================================	CONSTRUCTORS  ==================================================
 *======================================================================================================*/
	
	/* Default constructor: defaults to 1 / 1. Also functions as constructor from an integer,
	 * because the denominator defaults to 1. */
	Fraction ( const long long &n = 1, const long long &d = 1 )
	{
		set(n, d);
	}
	
	/* Copy constructor: creates a new  from another fraction. */
	Fraction ( const Fraction &frac )
	{
		set( frac );
	}
	
	/* Construct using a string */
	Fraction ( const string &str  )
	{
		set( str );
	}
	
	Fraction ( const string &str1, const string &str2 )
	{
		set(str1, str2);
	}
	
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
	void operator= ( const Fraction &frac )
	{
		if ( this == &frac )
			throw invalid_argument("Attempted self-assignment.");
		
		set(frac.getNumerator(), frac.getDenominator() );
	}
	
	// Assign an int
	void operator= ( const long long & num )
	{
		set(num, 1);
	}
 
//++++++++ Right-hand arithmetic operators ++++++++//

	// Addition: fraction + fraction
	Fraction operator+ ( const Fraction &frac )
	{
		Fraction temp( getNumerator(), getDenominator() );
		temp.add(frac);
		return temp;
	}
	
	// Addition: fraction + integer
	Fraction operator+ ( const long long &num)
	{
		Fraction temp( getNumerator(), getDenominator() );
		temp.add(num);
		return temp;
	}
	
	// Subtraction: fraction - fraction
	Fraction operator- ( const Fraction &frac )
	{
		Fraction temp( getNumerator(), getDenominator() );
		temp.sub(frac);
		return temp;
	}
	
	// Subtraction: fraction - integer
	Fraction operator- ( const long long &num)                          // Fraction - long long
	{
		Fraction temp( getNumerator(), getDenominator() );
		temp.sub(num);
		return temp;
	}
	
	// Multiplication: fraction * fraction
	Fraction operator* ( const Fraction &frac )                           // Fraction * Fraction
	{
		Fraction temp( getNumerator(), getDenominator() );
		temp.mul(frac);
		return temp;
	}
	
	// Multiplication: fraction * integer
	Fraction operator* ( const long long &num)                           // Fraction * long long
	{
		Fraction temp( getNumerator(), getDenominator() );
		temp.mul(num);
		return temp;
	}
	
	// Division: fraction / fraction
	Fraction operator/ ( const Fraction &frac )       // Fraction / Fraction
	{
		Fraction temp( getNumerator(), getDenominator() );
		temp.div(frac);
		return temp;
	}
	
	// Division: fraction / integer
	Fraction operator/ ( const long long &num ) // Fraction / Fraction
	{
		Fraction temp( getNumerator(), getDenominator() );
		temp.div(num);
		return temp;
	}
	
	// Power: fraction ^ num
	/* NOTE: operator^ has lower precedence than regular arithmetic operators in C++.
	 *       ALWAYS enclose a fraction "A" in parenthesis when putting the the power of
	 *       an integer "c" in an expression containing other operators, as in :
				
	 *			Wrong:  a ^ c + b  will yield a ^ (c + b)
	 *			Right: (a ^ c) + b
	 */
	Fraction operator^ ( const long long &num )
	{
		Fraction temp( getNumerator(), getDenominator() );
		temp.pow( num );
		return temp;
	}
	
	// Power: identical to above, but does not require () in operator precedence. Not so nice looking though...
	Fraction operator~ ( const long long &num )
	{
		Fraction temp( getNumerator(), getDenominator() );
		temp.pow( num );
		return temp;
	}
	
//++++++++ Increment and Decrement operators ++++++++//

	// Prefix increment: ++fraction
	Fraction &operator++ ()
	{
		increment();
		return *this;
	}
	
	// Postfix increment: fraction++
	Fraction operator++ ( int a = 0 ) //postfix increment
	{
		Fraction temp( getNumerator(), getDenominator() );
		increment();
		return temp;
	}
	
	// Prefix decrement: --fraction
	Fraction &operator-- () // prefix decrement
	{
		decrement();
		return *this;
	}
	
	// Postfix decrement: fraction --
	Fraction operator-- ( int a = 0 ) //postfix decrement
	{
		Fraction temp( getNumerator(), getDenominator() );
		decrement();
		return temp;
	}
	
	// Unary minus
	Fraction operator- () const // unary minus
	{
		Fraction temp( -getNumerator(), getDenominator() );
		return temp;
	}	// unary minus 
	
//++++++++ Left-hand equality operators ++++++++//

	// Is equal check: Fraction == Fraction
	bool operator== ( const Fraction &frac ) const
	{
		Fraction temp1 = frac; //create temp vars so that in the case that either fraction is scaled intentionally,
		temp1.simplify();      //can be simplified without modifying
		
		Fraction temp2( getNumerator(), getDenominator() );
		temp2.simplify();
		
		if ( temp1.getNumerator() == temp2.getNumerator() && temp1.getDenominator() == temp2.getDenominator() )
			return true;
		else return false;
	}

	// Is equal check: Fraction == integer
	bool operator== ( const long long &num ) const
	{
		if ( isInteger() )
		{
			if ( integer() == num ) return true;
			else return false;
		}
		
		else return false;
	}
	
	// Is not equal check: fraction != fraction
	bool operator!= ( const Fraction &frac ) const
	{
		Fraction temp1 = frac; //create temp vars so that in the case that either fraction is scaled intentionally,
		temp1.simplify();      //can be simplified without modifying
		
		Fraction temp2( getNumerator(), getDenominator() );
		temp2.simplify();
		
		if ( temp1.getNumerator() == temp2.getNumerator() && temp1.getDenominator() == temp2.getDenominator() )
			return false;
		else return true;
	}
	
	// Is not equal check: fraction != integer
	bool operator!= ( const long long &num ) const 
	{
		if ( isInteger() )
		{
			if ( integer() != num ) return true;
			else return false;
		}
		
		else return true;
	}
	
	// Is smaller than check: Fraction < fraction
	bool operator< (const Fraction &frac ) const
	{
		Fraction temp = frac;
		Fraction tempThis(getNumerator(), getDenominator() );
		tempThis.scaleUp(temp.getDenominator() );
		temp.scaleUp( getDenominator() );
		
		if( tempThis.getNumerator() < temp.getNumerator() ) return true;
		else return false;
	}
	
	// Is smaller than check: fraction < integer
	bool operator< (const long long &num ) const
	{
		Fraction temp(num);
		temp.scaleUp( getDenominator() );
		
		if( getNumerator() < temp.getNumerator() ) return true;
		else return false;
	}
	
	// Is larger than check: fraction > fraction
	bool operator> (const Fraction &frac ) const
	{
		Fraction temp = frac;
		Fraction tempThis(getNumerator(), getDenominator() );
		tempThis.scaleUp(temp.getDenominator() );
		temp.scaleUp( getDenominator() );
		
		if( tempThis.getNumerator() > temp.getNumerator() ) return true;
		else return false;
	}
	
	// Is larger than check: fraction > integer
	bool operator> (const long long &num ) const
	{
		Fraction temp(num);
		temp.scaleUp( getDenominator() );
		
		if( getNumerator() > temp.getNumerator() ) return true;
		else return false;
	}
	
	// Is smaller than or equal to check: fraction <= fraction
	bool operator<= (const Fraction &frac ) const
	{
		Fraction temp = frac;
		Fraction tempThis(getNumerator(), getDenominator() );
		tempThis.scaleUp(temp.getDenominator() );
		temp.scaleUp( getDenominator() );
		
		if( tempThis.getNumerator() <= temp.getNumerator() ) return true;
		else return false;
	}
	
	// Is smaller than or equal to check: fraction <= integer
	bool operator<= (const long long &num ) const
	{
		Fraction temp(num);
		temp.scaleUp( getDenominator() );
		
		if( getNumerator() <= temp.getNumerator() ) return true;
		else return false;
	}
	
	// Is larger than or equal to check: fraction >= fraction
	bool operator>= (const Fraction &frac ) const
	{
		Fraction temp = frac;
		Fraction tempThis(getNumerator(), getDenominator() );
		tempThis.scaleUp(temp.getDenominator() );
		temp.scaleUp( getDenominator() );
		
		if( tempThis.getNumerator() >= temp.getNumerator() ) return true;
		else return false;
	}
	
	// Is larger than or equal to check: fraction >= integer
	bool operator>= (const long long &num ) const
	{
		Fraction temp(num);
		temp.scaleUp( getDenominator() );
		
		if( getNumerator() >= temp.getNumerator() ) return true;
		else return false;
	}

//++++++++ Compound assignment operators ++++++++//

	// Plus equals fraction
	Fraction operator+= ( const Fraction &frac )
	{
		add(frac); 
	}
	
	// Plus equals integer
	Fraction operator+= ( const long long &num )
	{
		add(num);
	}
	
	// Minus equals fraction
	Fraction operator-= ( const Fraction &frac )
	{
		sub(frac);
	}
	
	// Minus equals integer
	Fraction operator-= ( const long long &num )
	{
		sub(num);
	}
	
	// Times equals fraction
	Fraction operator*= ( const Fraction &frac )
	{
		mul(frac);
	}
	
	// Times equals integer
	Fraction operator*= ( const long long &num )
	{
		mul(num);
	}
	
	// Divide equals fraction
	Fraction operator/= ( const Fraction &frac )
	{
		div(frac);
	}
	
	// Divicde equals integer
	Fraction operator/= ( const long long &num )
	{
		div(num);
	}
	
	// Power equals integer
	Fraction operator^= ( const long long &num )
	{
		pow( num );
	}


/*====================================	SET AND GET ====================================================
 *======================================================================================================*/

// ++++++++ Set ++++++++/

	// Set numerator and denominator in one go as integers
	void set( const long long &n, const long long &d )
	{
		setNumerator( n );
		setDenominator( d );
	
		simplify();
	}
	
	// Set using a fraction
	void set ( const Fraction &frac )
	{
		set( frac.getNumerator(), frac.getDenominator() );
		simplify();
	}
	
	// Set using 1 string
	void set ( const string & str )
	{
		if ( str[0] == '/' or str[str.length() - 1] == '/' )
			throw invalid_argument( 
				"Cannot create fraction from string that begins or ends with a slash.");
				
		stringstream numstream;
		int slash = 0;
		long long num, denom;
		
		
		for ( int k = 0; k < str.length() ; k++ ) if ( str[k] == '/' ) slash++;
		if ( slash > 1 ) throw invalid_argument( 
			"Cannot create a fraction from a string containing more than 1 slash.");
		if ( slash == 1 )
		{
			numstream << str;
			numstream >> num;
			numstream.ignore( numeric_limits<streamsize>::max() , '/');
			if ((numstream >> denom) == NULL ) denom = 1;
			set(num , denom);
		}
		if ( slash == 0 )
		{
			numstream <<str;
			numstream >> num;
			if ( (numstream >> denom) == NULL ) denom = 1;
			set(num , denom);
		}
		
		simplify();
	}
	
	//set using more than one string
	void set ( const string & str1, const string & str2 )
	{
		stringstream numstream;
		string result = str1 + " " + str2;
		set( result ); // uses with 1 string defined above
	}
	
	
	// Set numerator
	void setNumerator( const long long &n = 1)
	{
		if( n > LLONG_MAX || n < LLONG_MIN ) 
			throw overflow_error("Numerator provided exceeds long long type limits");
		else numerator = n;
	}
	
	// Set denominator
	void setDenominator( const long long &d = 1)
	{
		if(d == 0) throw invalid_argument("Denominator assigned as 0.");
		if( d > LLONG_MAX || d < LLONG_MIN ) 
			throw overflow_error("Denominator provided exceeds long long type limits");
		else denominator = d;
	}

//++++++++ Get ++++++++//

	// Get returns a fraction
	Fraction get() const
	{
		Fraction c(numerator, denominator);
		return c;
	}
	
	// getNumerator returns numerator as an integer
	long long getNumerator() const
	{
		return numerator;
	}
	
	// getDenominator returns denominator as an integer
	long long getDenominator() const
	{
		return denominator;
	}
	
	// getNumerAsFrac returns the numerator as fraction 'numerator / 1'
	Fraction getNumerAsFrac() const
	{
		Fraction numer( getNumerator(), getDenominator() );
		numer.simplify();
		numer.setDenominator( 1 );
		return numer;
	}
	
	// getDenomAsFrac returns the denominator as fraction '1 / denominator'
	Fraction getDenomAsFrac() const
	{
		Fraction denom( getNumerator() , getDenominator() );
		denom.simplify();
		denom.setNumerator( 1 );
		return denom;
	}
	
/*====================================	ARITHMETIC =====================================================
 *======================================================================================================*/

/*NOTE: these arithmetic methods alter the object for which they are called. */

	// Add integer
	void add( const long long &num)
	{
		setNumerator( getNumerator() + (num * getDenominator()) );
		simplify();
	} 
	
	// Add Fraction
	void add( const Fraction &frac )
	{
		simplify();
		setNumerator( (getNumerator() * frac.getDenominator()) + (getDenominator() * frac.getNumerator()) );
		setDenominator( getDenominator() * frac.getDenominator() );
		simplify();
	}
	
	// Subtract integer
	void sub( const long long &num)
	{
		setNumerator( getNumerator() - (num * getDenominator()) );
		simplify();
	}
	
	// Subtract fraction
	void sub( const Fraction &frac)
	{
		simplify();
		setNumerator( (getNumerator() * frac.getDenominator()) - (getDenominator() * frac.getNumerator()) );
		setDenominator( getDenominator() * frac.getDenominator() );
		simplify();
	}
	
	// Multiply by integer
	void mul( const long long &num)
	{
		setNumerator( getNumerator() * num );
		simplify();
	}
	
	// Multiply by fraction
	void mul( const Fraction &frac)
	{
		setNumerator( getNumerator() * frac.getNumerator() );
		setDenominator( getDenominator() * frac.getDenominator() );
		simplify();
	}
	
	// Divide by integer
	void div( const long long &num )
	{
		setDenominator( getDenominator() * num );
		simplify();
	}
	
	// Divide by fraction
	void div( const Fraction &frac )
	{
		setNumerator( getNumerator() * frac.getDenominator() );
		setDenominator( getDenominator() * frac.getNumerator() );
		simplify();
	}
	
	// Put to the power of an integer
	void pow( const long long &num )
	{
		if ( num == 0 )
		{
			set( 1 , 1 );
		}
		
		else 
		{
			long long pn = getNumerator();
			long long pd = getDenominator();
		
			for( int k = 2; k <= abs_( num ); k++ ){
				setNumerator( getNumerator() * pn );
				setDenominator( getDenominator() * pd );
			}
			
			if ( num < 0 )
			{
				reciprocal();
			}
		}
		
	}
	
	
/*====================================	ARITHMETIC UTILITIES ===========================================
 *======================================================================================================*/
 
	// Simplify (reduce) the fraction
	void simplify()
	{
		long long gCD = gcd( abs_(getNumerator()), abs_(getDenominator()) );
		
		setNumerator( getNumerator() / gCD );
		setDenominator( getDenominator() / gCD );
		
		if ( getDenominator() < 0 )
		{
			set( -getNumerator(), - getDenominator() );	
		}
		
	}
	
	// Scales the fraction up by an integer factor
	// Throws invalid_argument exception if the factor is smaller than 1
	void scaleUp(const long long &factor)
	{
		if ( factor < 1 ) throw invalid_argument("Factor less than 1 is forbidden in function scaleUp.");
		set( factor * getNumerator(), factor * getDenominator() );
	}
	
	// Scales the fraction down by an integer factor
	// Throws invalid_argument exception if the factor is smaller than 1
	// Throws invalid_argument exception if the factor does not divide both numerator and denominator
	void scaleDown( const long long &factor )
	{
		if ( factor < 1 ) throw invalid_argument("Factor less than 1 is forbidden in function scaleDown.");
		if ( getNumerator() % factor == 0 && getDenominator() % factor == 0 )
			set( getNumerator() / factor , getDenominator() / factor );
		else throw invalid_argument("Scaling factor argument does not divide both numerator and denominator.");
	}
	
	// Returns the smallest common denominator that the object has with another fraction object
	long long scd(const Fraction &other) const
	{	
		Fraction tempT( getNumerator() , getDenominator() );
		Fraction tempO = other;
		tempT.simplify();
		tempO.simplify();
		
		long long thisD = tempT.getDenominator();
		long long otherD = tempO.getDenominator();
		
		if( thisD == otherD) return thisD;
		
		else if( thisD % otherD == 0 ) return thisD;
		else if( otherD % thisD == 0 ) return otherD;
		else return thisD * otherD;
	}
	
	// Sets the fraction to its reciprocal (i.e. ( num / denom ) ^ -1 )
	void reciprocal ()
	{
		long long temp = getNumerator();
		setNumerator( getDenominator() );
		setDenominator( temp );
	}

	void increment()
	{
		setNumerator( getNumerator() + getDenominator() );
	}
	void decrement()
	{
		setNumerator( getNumerator() - getDenominator() );
	}
	
/*====================================	MISCELLANEOUS ==================================================
 *======================================================================================================*/
	
	bool isInteger() const
	{
		if( getNumerator() % getDenominator() == 0 ) return true;
		else return false;
	}
	long long integer() const
	{
		if( isInteger() ){
			return getNumerator() / getDenominator();
		}
		else throw runtime_error("Fraction does NOT reduce to a whole number. Conversion would result in truncation");
	}
	long double decimal() const
	{
		return ( long double)getNumerator() / (long double)getDenominator();
	}
	string str() const
	{
		ostringstream out;
		
		if ( isInteger() )
		{
			out << getNumerator();
		}
		else {
			out << getNumerator() << " / " << getDenominator();
		}
		return out.str();
	}
	
private:

	long long numerator;
	long long denominator;

/*====================================	PROTECTED UTILITIES ==============================================
 *======================================================================================================*/

protected:

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
	
	long long abs_( long long i )
	{
		if( i == 0 ) return 0;
		if( i > 0 ) return i;
		if( i < 0 ) return -i;
	}
	
};

#endif
