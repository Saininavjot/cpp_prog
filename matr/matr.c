/*
 * matr.c
 *
 *  Created on: Oct. 21, 2019
 *      Author: user
 */

#include <stdio.h>
	#include <stdlib.h>
#include "embt_print_vector.h"

/*
 *  includes for GSL components
 *  	- use double precision
 */
	#include <gsl/gsl_vector_double.h>
	#include <gsl/gsl_matrix_double.h>
	#include <gsl/gsl_rng.h>
	#include <gsl/gsl_randist.h>

/*
 * FUNCTIONS
 */

/*
 * simple Fibonacci sequence generator function, using recursion
 * */
size_t fib(size_t k)
{
	if (k==0)
	{
		return 0;
	}
	else if (k==1)
	{
		return 1;
	}
	else /* k >= 2 */
	{
		return fib(k-1) + fib(k-2);
	}
}
int main()
{
	/*
	 * INITIALIZE PARAMETERS
	 */
		/* vectors parameters */
		size_t		N=10; /* index type, vector sizes */
		gsl_vector *a = gsl_vector_alloc(N); /* allocate vector from heap of size N */
		gsl_vector *b = gsl_vector_alloc(N); /* allocate vector from heap of size N */
		gsl_vector *c = gsl_vector_calloc(N); /* allocate vector of size N but initialize entries to zero */

		/* random number generator parameters */
		const gsl_rng_type *T;
		gsl_rng *r; /* handle for our random number generator */

		/* matrix parameters */
		gsl_matrix *A = gsl_matrix_alloc(N,N);
		gsl_matrix *B = gsl_matrix_alloc(N,N);
		gsl_matrix *C = gsl_matrix_calloc(N,N);

	/*
	 * SET UP RANDOM NUMBER GENERATION
	 */
		gsl_rng_env_setup();
		T = gsl_rng_default;
		r = gsl_rng_alloc(T);

	/*
	 *  VECTOR OPERATIONS
	 */
		/* set the vector elements */
		for (size_t i = 0; i != N; ++i)
		{
			gsl_vector_set(a, i, fib(i)); /* set element i of vector a to Fibonacci number i */
			gsl_vector_set(b, i, gsl_ran_flat(r,-1.0,+1.0)); /* set element of vector b to random number */
		}

		/* c = a + b */
		gsl_vector_add(c, a); /* c += a */
		gsl_vector_add(c, b); /* c += b */



	/*
	 *	MATRIX OPERATIONS - your homework!! :)
	 */
		/* fill A with first N*N Fibonacci numbers, starting with row 1 (cols 1-10), then row 2, etc. */
		for (size_t i=0; i != N; ++i)
		{
			for (size_t j = 0; j != N; ++j)
			{
				gsl_matrix_set(A, i, j, (double) fib(j+i*N));
			}
		}

		/* fill B with N*N random numbers, uniformly distributed over the interval (-100, 100) */
		for (size_t i=0; i != N; ++i)
		{
			for (size_t j = 0; j != N; ++j)
			{
				gsl_matrix_set(B, i, j, gsl_ran_flat(r,-100.0,+100.0));
			}
		}

		/* make C the product of A and B */
		C = embt_mm(A,B,N);


		/* print the results */
		embt_print_vector(a);
		embt_print_vector(b);
		embt_print_vector(c);
		embt_print_matrix(A);
	embt_print_matrix(B);
		embt_print_matrix(C);



	/* de-allocate memory */
	gsl_vector_free(a);
	gsl_vector_free(b);
	gsl_vector_free(c);
	gsl_matrix_free(A);
	gsl_matrix_free(B);
	gsl_matrix_free(C);
	return EXIT_SUCCESS;
}
