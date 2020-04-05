/********************************************************************
 *                                                                  *
 *    function:    p2                                               *
 *                                                                  *
 *    purpose: process packet type 2. reservoir info                *
 *    written by:  r. h. dodds                                      *
 *    last revision: rhd 3/12/2020 -- original coding               *
 *                                                                  *
 ********************************************************************/
//
#include "system.h"
#include "prototypes.h"
//
void p2( int &reser_node, double &reser_head, int num_nodes, \
         bool networkcheck, bool debug )
{
    string fn = "p2";
    double zero = 0.0, thousand = 1000.0;
//
    user_trace( 1, fn, debug );
//
	cin >> reser_node >> reser_head;
    cout << "   " << reser_node << "  " << reser_head << endl;
	if( !networkcheck )
	{
		cout << "\n   >>> No network is defined, please input the" \
             << " network first." << endl;
        user_trace( 2, fn, debug );
		return;
	}
	if( reser_node <= 0 || reser_node > num_nodes )
	{
		cout << "Reservoir node number is out of the acceptable range,\n" \
             << "it has been set to the default (1)." << endl;
		reser_node = 1;
	}
	if( reser_head <= zero )
	{
		cout << "Reservoir head is negative or equal to zero,\n" \
             << "it has been set to the default (1000.0)." << endl;
		reser_head = thousand;
	}
	if( debug )
		cout << "Reservoir node number: " << reser_node << '\t' \
             << "Reservoir head: " << reser_head << endl;
//
    user_trace( 2, fn, debug );
	return;
}
