/********************************************************************
 *                                                                  *
 *    function:    p0                                               *
 *                                                                  *
 *    purpose: process packet type 0. comment lines                 *
 *    written by:  r. h. dodds                                      *
 *    last revision: rhd 3/12/2020 -- original coding               *
 *                                                                  *
 ********************************************************************/
//
#include "system.h"
#include "prototypes.h"

void p0 ( int packet_info, bool debug  )
{
	string comment, fn = "p0";
//
    user_trace( 1, fn, debug );
//
    cin.ignore ();
    for( int i = 1; i<=packet_info; i++ ) {
     getline( cin, comment, '\n');
     cout << comment << endl;
    }
    user_trace( 2, fn, debug );
	return;
}
