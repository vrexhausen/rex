/********************************************************************
 *                                                                  *
 *    function:    p7                                               *
 *                                                                  *
 *    purpose: process packet type 7. check network, run linkup     *
 *             and output lists of pipes connected to nodes         *
 *    written by:  r. h. dodds                                      *
 *    last revision: rhd 3/12/2020 -- original coding               *
 *                                                                  *
 ********************************************************************/
//
#include "system.h"
#include "prototypes.h"
//
void p7( int packet_info, int num_pipes, int num_nodes, \
         matrix <int> &node_table, bool networkcheck, bool debug )
{
    bool bad_node_table, error;
    int sn, en;
    vector <int> ipt, link;
//
	string fn = "p7", space ="    ", bspace = space + space + space;
    string mess1 = \
     "\n>>> No network is defined, please input the network sizes....";
    string mess2 = \
     "\n>>> Building lists of pipes connected to nodes....";
    string mess3 = ".... Node table has the following errors ....";
    string mess4 = "\n" + space + \
     ".... Errors in node table prevent generation of pipes\n";
    string mess5 = "     connected to each node ....\n\n";
//
    user_trace( 1, fn, debug );
//
	if( !networkcheck )
	 {
		cout << mess1 << endl;
        user_trace( 2, fn, debug );
		return;
	 }
//
    cout << mess2 << endl;
//
//             check that connectivity has been input for all pipes
//
    bad_node_table = false;
	for( int pipe = 1; pipe <= num_pipes; pipe++ )
	 {
        sn = node_table(pipe,1);
        en = node_table(pipe,2);
		if( sn <= 0 )
		 {
          if( !bad_node_table )
            cout << "\n" << space << mess3 << endl;
          cout << bspace << "Pipe " << pipe << " starting node: "
               << sn << endl;
          bad_node_table = true;
		 }
		if( en <= 0 )
		 {
            if( !bad_node_table )
              cout<< "\n" << space << mess3 << endl;
            cout << bspace << "Pipe " << pipe << " ending node: "
                 << en << endl;
            bad_node_table = true;
		 }
	 } // for on pipes
//
    if( bad_node_table )
     {
        cout << mess4 <<  space << mess5 << endl;
        user_trace( 2, fn, debug );
	 }
//
//             use linkup to build ipt-link for lists of pipes connected
//             to nodes and output
//
    ipt.create(1,num_nodes+1);
    link.create(1,2*num_pipes);
    linkup(num_pipes, num_nodes, debug, node_table, ipt, link);
//
    user_trace( 2, fn, debug );
	return;
}
