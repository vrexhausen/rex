/********************************************************************
 *                                                                  *
 *    function:    p6                                               *
 *                                                                  *
 *    purpose: process packet type 6. convergence info              *
 *    written by:  r. h. dodds                                      *
 *    last revision: rhd 3/12/2020 -- original coding               *
 *                                                                  *
 ********************************************************************/
//
#include "system.h"
#include "prototypes.h"
//
void p6( double &tolerance, int &max_iterations, bool debug )
{
    double default_tol = 0.01, zero = 0.0;
	string trash, fn = "p5";
//
    user_trace( 1, fn, debug );
//
	cin >> tolerance >> max_iterations;
    cout << tolerance << "  " << max_iterations << endl;
	if( tolerance <= zero )
	 {
		cout << "Tolerance is <= 0, default = 0.01 used" << endl;
		tolerance = default_tol;
	 }
	if( max_iterations <= 0 )
	 {
		cout << "Maximum number of iterations < 1, default = 5 used" << endl;
		max_iterations = 5;
	 }
	if( debug )
		cout << "Tolerance: " << tolerance << '\t' \
             << "Maximum number of iterations: " << max_iterations << endl;
//
    user_trace( 2, fn, debug );
//
	return;
}
