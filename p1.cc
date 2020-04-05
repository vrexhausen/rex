/********************************************************************
 *                                                                  *
 *    function:    p1                                               *
 *                                                                  *
 *    purpose: process packet type 1. network size, title           *
 *    written by:  r. h. dodds                                      *
 *    last revision: rhd 3/12/2020 -- original coding               *
 *                                                                  *
 ********************************************************************/
//
#include "system.h"
#include "prototypes.h"
//
void p1 (const int max_pipes, const int max_nodes, int &num_pipes, \
         int &num_nodes, string &title, matrix <int> &node_table, \
         vector <double> &lengths, vector <double> &diameters, \
         vector <double> &hw_coeffs, vector <double> &external_flows, \
         vector <double> &initial_heads, vector <double> &pipe_flows, \
         vector <double> &heads, bool &networkcheck, bool debug )
{
	int i, lead_spaces;
    const double zero = 0.0;
    string fn = "p1";
//
    user_trace( 1, fn, debug );
//
	cin.ignore ();
	getline (cin, title, '\n');
    cout << title << endl;
	lead_spaces = title.find_first_not_of(' ');
	title.erase (0, lead_spaces);
	if( debug ) cout << "Title: " << title << endl;
//
	cin >> num_pipes >> num_nodes;
    cout << num_pipes << "  " << num_nodes << endl;
	if( num_pipes <= 0 || num_nodes <= 0 )
	{
		cout << "Number of pipes or number of nodes or both\n" << \
                "are negative or equal to zero.\n" << \
                "Both of the values have been set to default (0)." << endl;
		num_pipes = 0;
		num_nodes = 0;
		networkcheck = false;
		return;
	}
	if( num_pipes > max_pipes )
	{
		cout << "Number of pipes is greater than the maximum allowed\n," \
             << "it has been set to the maximum." << endl;
		num_pipes = max_pipes;
	}
	if( num_nodes > max_nodes )
	{
		cout << "Number of nodes is greater than the maximum allowed,\n" \
             << "It has been set to the maximum." << endl;
		num_nodes = max_nodes;
	}
	if( debug ) cout << "Number of pipes: " << num_pipes << '\t' \
                << "Number of nodes: " << num_pipes << endl;
//
	if( networkcheck )
	{
		node_table.free();
		lengths.free();
		diameters.free();
		hw_coeffs.free();
		external_flows.free();
		initial_heads.free();
    pipe_flows.free();
    heads.free();
	}
//
	node_table.create(1, num_pipes, 1, 2);
	lengths.create(1, num_pipes);
	diameters.create(1, num_pipes);
	hw_coeffs.create(1, num_pipes);
	external_flows.create(1, num_nodes);
	initial_heads.create(1, num_nodes);
  pipe_flows.create(1,num_pipes) ;
  heads.create(1,num_pipes) ;
//
	for( int i= 1; i<= num_pipes; i++ )
	{
		node_table(i,1) = 0;
		node_table(i,2) = 0;
		lengths(i)   = zero;
		diameters(i) = zero;
		hw_coeffs(i) = zero;
	}
	for( int i = 1; i<= num_nodes; i++ )
	{
		external_flows(i) = zero;
		initial_heads(i)  = zero;
	}
//
	networkcheck = true;
    user_trace( 2, fn, debug );
	return;
}
