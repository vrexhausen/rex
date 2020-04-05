/********************************************************************
 *                                                                  *
 *    function:    p10                                              *
 *                                                                  *
 *    purpose: process packet type 10. debug info                   *
 *    written by:  r. h. dodds                                      *
 *    last revision: rhd 3/12/2020 -- original coding               *
 *                                                                  *
 ********************************************************************/
//
#include "system.h"
#include "prototypes.h"
//
void p10( int packet_info, bool debug )
{
    string fn = "p10";
//
    user_trace( 1, fn, debug );
//
    if( packet_info == 0 )
      debug = false;
    else if( packet_info == 1 )
      debug = true;
    else
      {
        cout << "Wrong choice for the debugging status!\n" \
             << "Debugging turned off." << endl;
        debug = false;
      }
//	
    user_trace( 2, fn, debug );
	return;
}
