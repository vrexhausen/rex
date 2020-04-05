/********************************************************************
 *                                                                  *
 *    function:    p4                                               *
 *                                                                  *
 *    purpose: process packet type 4. external flows                *
 *    written by:  r. h. dodds                                      *
 *    last revision: rhd 3/12/2020 -- original coding               *
 *                                                                  *
 ********************************************************************/
//
#include "system.h"
#include "prototypes.h"
//
void p4( int packet_info, int num_nodes, vector <double> &external_flows, \
         bool networkcheck, bool debug )
{
	int i, node;
	double flow;
	string trash, fn = "p4";
//
    user_trace( 1, fn, debug );
//
	if( !networkcheck )
	 {
		cout << "No network is defined, please input network\n" \
             << "size first." << endl;
		for( i = 1; i <= packet_info; i++ )
			getline( cin, trash );
        user_trace( 2, fn, debug );
		return;
	 }
//
	for( int i=1; i<=packet_info; i++ )
	 {
		cin >> node >> flow;
        cout << "   " << node << "  " << flow << endl;
		if( node <= 0 || node > num_nodes )
		 {
          cout << "Node No." << node << ":" << endl;
          cout << "Node number out of range, flow ignored." << endl;
          continue;
		 }
		external_flows(node) = flow;
		if( debug )
			cout << "Node number: " << node << '\t' << "Flow rate: " \
                 << external_flows(node) << endl;
	 }
//
    user_trace( 2, fn, debug );
//
	return;
}
