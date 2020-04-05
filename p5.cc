/********************************************************************
 *                                                                  *
 *    function:    p5                                               *
 *                                                                  *
 *    purpose: process packet type 5. initial pressures             *
 *    written by:  r. h. dodds                                      *
 *    last revision: rhd 3/12/2020 -- original coding               *
 *                                                                  *
 ********************************************************************/
//
#include "system.h"
#include "prototypes.h"
//
void p5( int packet_info, int num_nodes, int reser_node, \
         double reser_head, vector <double> &initial_heads, \
         bool networkcheck, bool debug )
{
	int i, node;
	double head;
	string trash, fn = "p5";
//
    user_trace( 1, fn, debug );
//
	if( !networkcheck )
	{
       cout << "No network is defined, please input sizes first." << endl;
       for( i = 1; i <= packet_info; i++ )
         getline( cin,trash );
       user_trace( 2, fn, debug );
       return;
	}
//
	for( int i = 1; i <= packet_info; i++ )
	{
		cin >> node >> head;
        cout << "   " << node << " " << head << endl;
		if( node <= 0 || node > num_nodes )
		{
			cout << "Node No." << node << ":" << endl;
			cout << "Node number out of range, head ignored." << endl;
			continue;
		}
		else if( node == reser_node )
		{
			cout << "Reservoir head cannot be set through this \n" \
                 << "packet, the input information ignored" << endl;
			continue;
		}
		if( head <= 0 || head >= reser_head )
		{
			cout << "Node No." << node << ":" << endl;
			cout << "Node head out of range, input head ignored." << endl;
			continue;
		}
		initial_heads(node) = head;
		if( debug )
			cout << "Node number: " << node << '\t' << "Head: " \
                 << initial_heads(node) << endl;
	}
    user_trace( 2, fn, debug );
//
	return;
}
