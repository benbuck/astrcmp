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


#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "astrcmp.h"
#ifdef STANDALONE
#	include <stdlib.h>
#endif /* STANDALONE */


/* Turn this on to reduce wrong-case penalty in astrcmp() */
/* #define STEP5A */

/* Turn this on to reduce punctuation/whitespace penalty */
#define STEP5B


typedef float dist_t; /* type to store Levenshtein or edit distances */
typedef unsigned int index_t; /* type to store indices into distance matrix */


dist_t astrcmp_min3(dist_t const a, dist_t const b, dist_t const c);
dist_t astrcmp_get_cell(dist_t const * const matrix, index_t const col, index_t const row, size_t const column_count);
void astrcmp_put_cell(dist_t * const matrix, index_t const col, index_t const row, size_t const column_count, dist_t const contents);
#ifdef STANDALONE
	int main(int const argc, char const * const * const argv);
#	ifdef TEST
		void astrcmp_test(const char * const s1, const char * const s2, float const expected_result, float const expected_resulti);
#	endif /* TEST */
#endif /* STANDALONE */


#ifdef STANDALONE

int main(int const argc, char const * const * const argv)
{
#ifdef TEST

	(void)argc;
	(void)argv;

	astrcmp_test("a", "a", 1.0f, 1.0f); /* simple equality */
	astrcmp_test("a", "b", 0.0f, 0.0f); /* simple inequality */
	astrcmp_test("a", "A", 0.0f, 1.0f); /* case sensitivity */
	astrcmp_test("aa", "ab", 0.5f, 0.5f); /* substitution */
	astrcmp_test("aa", "ba", 0.5f, 0.5f); /* substitution */
	astrcmp_test("a", "aa", 0.5f, 0.5f); /* insertion */
	astrcmp_test("aa", "a", 0.5f, 0.5f); /* deletion */
	astrcmp_test("ab", "ba", 0.0f, 0.0f); /* transposition (not for short strings) */
	astrcmp_test("aab", "aba", 0.666667f, 0.666667f); /* transposition */
	astrcmp_test("aaaaaaaaa", "aaaabaaaa", 0.8888889f, 0.8888889f); /* transposition */
	astrcmp_test("Brittany Spears", "britnee_sperez", 0.466667f, 0.5333333f); /* combined tests */

	return EXIT_SUCCESS;

#else /* !TEST */

	float sameness;

	if ((argv == NULL) || (argc != 3))
	{
		printf("Usage is: astrcmp source_text target_text\n");
		return EXIT_FAILURE;
	}

	sameness = astrcmp(argv[1], argv[2]);
	printf("astrcmp : %f\n", sameness);
	sameness = astrcmpi(argv[1], argv[2]);
	printf("astrcmpi: %f\n", sameness);

	return EXIT_SUCCESS;

#endif /* !TEST */
}


#ifdef TEST

void astrcmp_test(const char * const s1, const char * const s2, float const expected_result, float const expected_resulti)
{
	float result;
	int int_result;
	int int_expected;
	
	result = astrcmp(s1, s2);
	printf("astrcmp: \"%s\" \"%s\" = %f, expecting %f\n", s1, s2, result, expected_result);
	int_result = (int)(result * 0xFFFFF);
	int_expected = (int)(expected_result * 0xFFFFF);
	if (int_result != int_expected)
	{
		printf("*** FAILURE *** %d %d\n", int_result, int_expected);
		exit(EXIT_FAILURE);
	}

	result = astrcmpi(s1, s2);
	printf("astrcmpi: \"%s\" \"%s\" = %f, expecting %f\n", s1, s2, result, expected_resulti);
	int_result = (int)(result * 0xFFFFF);
	int_expected = (int)(expected_resulti * 0xFFFFF);
	if (int_result != int_expected)
	{
		printf("*** FAILURE ***\n");
		exit(EXIT_FAILURE);
	}
}

#endif /* TEST */

#endif /* STANDALONE */


/***
 *
 * astrcmp_min3 - returns the minimum of three values
 *
 ***/

dist_t astrcmp_min3(dist_t const a, dist_t const b, dist_t const c)
{
	dist_t mi;

	mi = a;
	if (b < mi)
	{
		mi = b;
	}
	if (c < mi)
	{
		mi = c;
	}
	return mi;

}


/***
 *
 * astrcmp_get_cell - get the contents of the specified cell in the matrix 
 *
 ***/

dist_t astrcmp_get_cell(dist_t const * const matrix, index_t const col, index_t const row, size_t const column_count)
{
	dist_t const * cell;

	if (matrix == NULL)
	{
		return (dist_t)0;
	}

	cell = matrix + col + (row * (index_t)(column_count + 1));
	return *cell;
}


/***
 *
 * astrcmp_put_cell - fill the specified cell in the matrix with the given contents
 *
 ***/

void astrcmp_put_cell(dist_t * const matrix, index_t const col, index_t const row, size_t const column_count, dist_t const contents)
{
	if (matrix == NULL)
	{
		return;
	}

	matrix[col + (row * (index_t)(column_count + 1))] = contents;
}


/***
 *
 * astrcmp - approximate string comparison (case-sensitive)
 * 
 * Takes two strings and returns a value between zero (no similarity) and one
 * (exactly the same).
 *
 ***/

float astrcmp(char const * const s1, char const * const s2)
{
	dist_t * matrix; /* pointer to matrix */
	size_t len1; /* length of s1 */
	size_t len2; /* length of s2 */
	size_t maxlen; /* length of larger string */
	index_t index1; /* iterates through s1 */
	index_t index2; /* iterates through s2 */
	char s1_current; /* current character of s1 */
	char s2_current; /* current character of s2 */
	dist_t cost; /* cost */
	dist_t result; /* result */
	dist_t cell; /* contents of s2 cell */
	dist_t above; /* contents of cell immediately above */
	dist_t left; /* contents of cell immediately to left */
	dist_t diagonal; /* contents of cell immediately above and to left */
	dist_t trans; /* cost of transposition */

	/* Step 1 */
	/* Check string lengths */

	if ((s1 == NULL) || (s2 == NULL))
	{
		return (float)0;
	}

	len1 = strlen(s1);
	len2 = strlen(s2);
	if (len1 == 0)
	{
		return (float)len2;
	}
	if (len2 == 0)
	{
		return (float)len1;
	}
	maxlen = (len2 > len1) ? len2 : len1;

	/* Step 2 */
	/* Allocate matrix for algorithm and fill it with default values */

	matrix = (dist_t *)malloc((len1 + 1) * (len2 + 1) * sizeof(dist_t));

	for (index1 = 0; index1 <= len1; index1++)
	{
		cost = (dist_t)index1;
		astrcmp_put_cell(matrix, index1, 0, len1, cost);
	}

	for (index2 = 0; index2 <= len2; index2++)
	{
		cost = (dist_t)index2;
		astrcmp_put_cell(matrix, 0, index2, len1, cost);
	}

	/* Step 3 */
	/* Loop through first string */

	for (index1 = 1; index1 <= len1; index1++)
	{
		s1_current = s1[index1 - 1];

		/* Step 4 */
		/* Loop through second string */

		for (index2 = 1; index2 <= len2; index2++)
		{
			s2_current = s2[index2 - 1];

			/* Step 5 */
			/* Calculate cost of this iteration (handles deletion, insertion, 
			and substitution) */

			if (s1_current == s2_current)
			{
				cost = 0.0f;
			}
#ifdef STEP5A
			else if (toupper(s1_current) == toupper(s2_current))
			{
				/* Step 5a */
				/* Handle upper/lower case mismatch at reduced penalty.
				This modification done by Benbuck Nason */
				cost = 0.5f;
			}
#endif
#ifdef STEP5B
			else if (isspace(s1_current) && isspace(s2_current))
			{
				cost = 0.75f;
			}
			else if (ispunct(s1_current) && ispunct(s2_current))
			{
				cost = 0.25f;
			}
			else if ((isspace(s1_current) || ispunct(s1_current)) && (isspace(s2_current) || ispunct(s2_current)))
			{
				cost = 0.5f;
			}
#endif
			else
			{
				cost = 1.0f;
			}

			/* Step 6 */
			/* Calculate the total cost up to this point */

			above = astrcmp_get_cell(matrix, index1 - 1, index2, len1);
			left = astrcmp_get_cell(matrix, index1, index2 -1 , len1);
			diagonal = astrcmp_get_cell(matrix, index1 - 1, index2 - 1, len1);
			cell = astrcmp_min3(above + 1, left + 1, diagonal + cost);

			/* Step 6a */
			/* Also cover transposition. This step is taken from Berghel & Roach: 
			"An Extension of Ukkonen's Enhanced Dynamic Programming ASM Algorithm"
			http://www.acm.org/~hlb/publications/asm/asm.html */
			
			if ((index1 > 2) && (index2 > 2))
			{
				trans = astrcmp_get_cell(matrix, index1 - 2, index2 - 2, len1) + 1.0f;
				if (s1[index1 - 2] != s2_current)
				{
					trans++;
				}
				if (s1_current != s2[index2 - 2])
				{
					trans++;
				}
				if (cell > trans)
				{
					cell = trans;
				}
			}

			astrcmp_put_cell(matrix, index1, index2, len1, cell);
		}
	}

	/* Step 7 */
	/* Clean up and get result */

	result = astrcmp_get_cell(matrix, len1, len2, len1);
	free(matrix);
#	ifdef DEBUG
		printf("Levenshtein Distance: %f of %d\n", result, maxlen);
#	endif

	/* Step 7a */
	/* Convert the Levenshtein distance into a floating point value
	between 0 and 1 by scaling the distance by the longer string
	length. This step added by Benbuck Nason */

	return (float)1 - ((float)result / (float)maxlen);
}


/***
 *
 * astrcmpi - approximate string comparison (case-insensitive)
 * 
 * Takes two strings and returns a value between zero (no similarity) and one
 * (exactly the same) where the case of each letter is not significant.
 *
 ***/

float astrcmpi(char const * const s1, char const * const s2)
{
	dist_t * matrix; /* pointer to matrix */
	size_t len1; /* length of s1 */
	size_t len2; /* length of s2 */
	size_t maxlen; /* length of larger string */
	index_t index1; /* iterates through s1 */
	index_t index2; /* iterates through s2 */
	char s1_current; /* current character of s1 */
	char s2_current; /* current character of s2 */
	int s1_upper; /* upper case current character of s1 */
	int s2_upper; /* upper case current character of s2 */
	dist_t cost; /* cost */
	dist_t result; /* result */
	dist_t cell; /* contents of s2 cell */
	dist_t above; /* contents of cell immediately above */
	dist_t left; /* contents of cell immediately to left */
	dist_t diagonal; /* contents of cell immediately above and to left */
	dist_t trans; /* cost of transposition */

	/* Step 1 */
	/* Check string lengths */

	if ((s1 == NULL) || (s2 == NULL))
	{
		return (float)0;
	}

	len1 = strlen(s1);
	len2 = strlen(s2);
	if (len1 == 0)
	{
		return (float)len2;
	}
	if (len2 == 0)
	{
		return (float)len1;
	}
	maxlen = (len2 > len1) ? len2 : len1;

	/* Step 2 */
	/* Allocate matrix for algorithm and fill it with default values */

	matrix = (dist_t *)malloc((len1 + 1) * (len2 + 1) * sizeof(dist_t));

	for (index1 = 0; index1 <= len1; index1++)
	{
		cost = (dist_t)index1;
		astrcmp_put_cell(matrix, index1, 0, len1, cost);
	}

	for (index2 = 0; index2 <= len2; index2++)
	{
		cost = (dist_t)index2;
		astrcmp_put_cell(matrix, 0, index2, len1, cost);
	}

	/* Step 3 */
	/* Loop through first string */

	for (index1 = 1; index1 <= len1; index1++)
	{
		s1_current = s1[index1 - 1];

		/* Step 4 */
		/* Loop through second string */

		for (index2 = 1; index2 <= len2; index2++)
		{
			s2_current = s2[index2 - 1];

			/* Step 5 */
			/* Calculate cost of this iteration (handles deletion, insertion, 
			and substitution) */

			s1_upper = toupper(s1_current);
			s2_upper = toupper(s2_current);
			if ((s1_current == s2_current) || (s1_upper == s2_upper))
			{
				cost = 0.0f;
			}
			else
			{
				cost = 1.0f;
			}

			/* Step 6 */
			/* Calculate the total cost up to this point */

			above = astrcmp_get_cell(matrix, index1 - 1, index2, len1);
			left = astrcmp_get_cell(matrix, index1, index2 -1 , len1);
			diagonal = astrcmp_get_cell(matrix, index1 - 1, index2 - 1, len1);
			cell = astrcmp_min3(above + 1, left + 1, diagonal + cost);

			/* Step 6a */
			/* Also cover transposition. This step is taken from Berghel & Roach: 
			"An Extension of Ukkonen's Enhanced Dynamic Programming ASM Algorithm"
			http://www.acm.org/~hlb/publications/asm/asm.html */
			
			if ((index1 > 2) && (index2 > 2))
			{
				trans = astrcmp_get_cell(matrix, index1 - 2, index2 - 2, len1) + 1.0f;
				if (s1[index1 - 2] != s2_current)
				{
					trans++;
				}
				if (s1_current != s2[index2 - 2])
				{
					trans++;
				}
				if (cell > trans)
				{
					cell = trans;
				}
			}

			astrcmp_put_cell(matrix, index1, index2, len1, cell);
		}
	}

	/* Step 7 */
	/* Clean up and get result */

	result = astrcmp_get_cell(matrix, len1, len2, len1);
	free(matrix);
#	ifdef DEBUG
		printf("Levenshtein Distance: %f of %d\n", result, maxlen);
#	endif

	/* Step 7a */
	/* Convert the Levenshtein distance into a floating point value
	between 0 and 1 by scaling the distance by the longer string
	length. This step added by Benbuck Nason */

	return (float)1 - ((float)result / (float)maxlen);
}
