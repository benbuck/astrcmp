/***
 *
 * Approximate string comparison
 *
 * This work is based on the Levenshtein Metric or "edit distance", which is 
 * well known, simple, and seems to be unencumbered by any usage restrictions. 
 * For more information on the Levenshtein Distance you can refer to the web, 
 * e.g. http://www.merriampark.com/ld.htm.
 *
 * Accuracy and speed enhancements could probably be made to this algorithm by 
 * implementing the improvements suggested by such people as Esko Ukkonen, Hal 
 * Berghel & David Roach, and Sun Wu and Udi Manber.
 *
 * This code has been succesfully tested under Microsoft Windows with:
 *	Microsoft Visual C++ 6 SP 5
 *	GNU gcc 3.2 & Cygwin
 *	GNU gcc 3.2 & MinGW
 *	Gimpel PC-Lint 8.0 at extremely high levels.
 * I am fairly certain there should be few, if any, portability issues.
 *
 * This code was derived with permission and without restriction from the 
 * example on Michael Gilleland's site (http://www.merriampark.com/ld.htm) and 
 * the corresponding contribution from Anders Sewerin Johansen. Therefore this 
 * code is also without restriction. Out of courtesy, if you use this code as 
 * is, please leave this message intact, and if you modify the code for your 
 * own purposes please give credit where credit is due.
 *
 * Benbuck Nason
 * February 28th, 2003
 *
 ***/


#ifndef ASTRCMP_H
#define ASTRCMP_H


/***
 *
 * astrcmp - approximate string comparison (case-sensitive)
 * 
 * Takes two strings and returns a value between zero (no similarity) and one
 * (exactly the same).
 *
 ***/

float astrcmp(char const * const s1, char const * const s2);


/***
 *
 * astrcmpi - approximate string comparison (case-insensitive)
 * 
 * Takes two strings and returns a value between zero (no similarity) and one
 * (exactly the same) where the case of each letter is not significant.
 *
 ***/

float astrcmpi(char const * const s1, char const * const s2);


#endif /* ASTRCMP_H */
