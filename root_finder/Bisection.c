#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void f( double*, const double );

void signum( double*, const double );

int main( int argc, char* argv[] ) {
   
  /*check for command line arguments*/
  if( argc == 4 ) {
    double a;
    double b;
    double tol;
    int done;
    double f_a_sign;
    double f_b_sign;
    double f_a;
    double f_b;
    int n = 0;

    /*command line arguments*/
    a = atof( argv[ 1 ] );
    b = atof( argv[ 2 ] );
    tol = atof( argv[ 3 ] );
    
    /*function evaluation*/
    f( &f_a, a );
    f( &f_b, b );

    /*compute the sign of the function*/
    signum( &f_a_sign, f_a );
    signum( &f_b_sign, f_b );

    /*done variable*/
    done = 0;

    /*root variable*/
    double root;
	printf( "%8s %8s %8s\n", "n", "x", "f(x)" );
	printf( "---------" );
	printf( "---------" );
	printf( "--------\n" );
    while( !done ) {
      if( f_a_sign != f_b_sign ) {
        double mid;
        double f_mid;
        mid = ( a + b ) / 2;
        f( &f_mid, mid );
	printf( "%8d %8.5lf %8.5lf\n", n, mid, f_mid );
	n++;
        if( f_mid > -tol && f_mid < tol ) {
          root = mid;
          done = 1;
        } else {
          if( f_mid * f_b < 0.0 ) {
            a = mid;
          } else if( f_a * f_mid < 0.0 ) {
            b = mid;
          }else {
            done = 2;
          }
        }
      } else {
        done = 2;
      }
    }
    if( done == 1 ) {
      double funcVal;
      f( &funcVal, root );
      printf( "---------" );
      printf( "---------" );
      printf( "--------\n" );
      printf( "Total iterations: %d\n", n - 1 );
      printf( "f( %lf ) = %lf\n", root, funcVal );
    } else if( done == 2 ) {
      printf( "could not compute root\n" );
    }
  } else {
    printf( "Usage: %s a b tol\n", argv[ 0 ] );
  }
  return 0;
}

void signum( double* sign, double x ) {
  double result;
  if( x < 0.0 ) {
    result = -1;
  } else if( x > 0.0 ) {
    result = 1;
  } else {
    result = 0;
  }
  *sign = result;
}

void f( double* y, double x ) {
  *y = 0.76 * x * sin( ( 3 * x ) / 5.2 ) * tan( x / 4.7 ) +
    2.9 * cos( x + 2.5 ) * sin( 0.39 * ( 1.5 + x ) );
}
