#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void f( double*, double );

void update( double*, double, double );

int timeToStop( double, double, double );

int main( int argc, char* argv[] ) {
	if( argc == 4 ) {
		
		/*variables*/
		double prev = 0.0;
		double curr = 0.0;
		double next = 0.0;
		double tol = 0.0;
		double funcVal = 500.0;
		int n = 0;
		int done = 0;

		curr = atof( argv[ 1 ] );
		next = atof( argv[ 2 ] );
		tol = atof( argv[ 3 ] );
		done = 0;
		printf( "%8s %8s %8s\n", "n", "x", "f(x)" );
		printf( "---------" );
		printf( "---------" );
		printf( "--------\n" );
		while( !done ) {
			double f_curr = 0.0;
			double temp = 0.0;
			temp = curr;
			curr = next;
			prev = temp;

			/*update*/
			update( &next, curr, prev );		

			/*is it time to stop?*/
			if( timeToStop( next, curr, tol ) ) {
				done = 1;
			}
			n++;
			f( &f_curr, curr );
			printf( "%8d %8.5lf %8.5lf\n", n, curr, f_curr ); 
		}
		f( &funcVal, next );	
		printf( "---------" );
		printf( "---------" );
		printf( "--------\n" );
		printf( "Total iterations: %d\n", n - 1 );
		printf( "f( %lf ) = %lf\n", next, funcVal ); 
	} else {
		printf( "Usage: %s x0 x1 tol\n", argv[ 0 ] );
	}
	return 0;
}

void f( double* y, double x ) {
	*y = 0.76 * x * sin( ( 3 * x ) / 5.2 ) * tan( x / 4.7 ) +
	2.9 * cos( x + 2.5 ) * sin( 0.39 * ( 1.5 * x ) );
}

void update( double* next, double curr, double prev ) {
	double f_curr;
	double f_prev;

	/*compute function values*/
	f( &f_curr, curr );
	f( &f_prev, prev );
	*next = curr - f_curr * ( ( curr - prev ) / ( f_curr - f_prev ) );
}

int timeToStop( double x0, double x1, double tol ) {
	int retVal = 0;
	if( ( x1 - x0 ) < tol && ( x1 - x0 ) > -tol ) {
		retVal = 1;
	}
	return retVal;
}
