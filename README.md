Fraction
========

A class that implements rational numbers in C++

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
