#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void f( double*, double );

void f_prime( double*, double );

void g( double*, double );

int timeToStop( double, double, double );

int main( int argc, char* argv[] ) {
  if( argc == 3 ) {
    double prevX = -1e12;
    double curX = atof( argv[ 1 ] );
    double tol = atof( argv[ 2 ] );
    int done = 0;
    int n = 0;
    printf( "%8s %8s %8s\n", "n", "x", "f(x)" );
    printf( "---------" );
    printf( "---------" );
    printf( "--------\n" );
    while( !done ) {
      double nextX;
      double f_curX;
      g( &nextX, curX );
      prevX = curX;
      curX = nextX;
      if( timeToStop( curX, prevX, tol ) ) {
        done = 1;
      }
      n++;
      f( &f_curX, curX );
      printf( "%8d %8.5lf %8.5lf\n", n, curX, f_curX );
    }
    double f_curX;
    f( &f_curX, curX );
    printf( "f( %lf ) = %lf\n", curX, f_curX );
  } else {
    printf( "Usage: %s x0 tol\n", argv[ 0 ] );
  }
}

void f( double* y, double x ) {
  *y = 0.76 * x * sin( ( 3 * x ) / 5.2 ) * tan( x / 4.7 ) +
    2.9 * cos( x + 2.5 ) * sin( 0.39 * ( 1.5 + x ) );
}

void f_prime( double* y, double x ) {
  *y = 0.76 * ( x * ( sin( ( 3 * x ) / 5.2 ) * ( 1 / 4.7 ) *
                      ( 1 / cos( x / 4.7 ) ) * ( 1 / cos( x / 4.7 ) )
                      + ( 3 / 5.2 ) * cos( ( 3 * x ) / 5.2 ) * tan( x / 4.7 ) )
                + sin( ( 3 * x ) / 5.2 ) * tan( x / 4.7 )
                + 2.9 * ( cos( x + 2.5 ) * 0.39 * cos( 1.5 + x )
                          - sin( x + 2.5 ) * sin( 0.39 * ( 1.5 + x ) ) ) );
}

void g( double* x_next, double x ) {
  double f_x;
  double f_prime_x;
  f( &f_x, x );
  f_prime( &f_prime_x, x );
  *x_next = x - f_x / f_prime_x;
}

 int timeToStop( double x_now, double x_before, double tol ) {
   int result = 0;
   if( ( x_now - x_before ) < tol &&
       ( x_now - x_before ) > -tol ) {
     result = 1;
   }
   return result;
 }
