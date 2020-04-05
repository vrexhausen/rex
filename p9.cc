/********************************************************************
 *                                                                  *
 *    function:    p9                                               *
 *                                                                  *
 *    purpose: process packet type 9. output requests               *
 *    written by:  r. h. dodds                                      *
 *    last revision: rhd 3/12/2020 -- original coding               *
 *                                                                  *
 ********************************************************************/
//
#include "system.h"
#include "prototypes.h"
//
void p9( int num_pipes, int num_nodes, int reser_node, double reser_head, \
         double tolerance, int max_iterations, string title, \
         matrix <int> &node_table, vector <double> &lengths, \
         vector <double> &diameters, vector <double> &hw_coeffs, \
         vector <double> &external_flows, vector <double> &initial_heads, \
         bool debug )
{
	int nspace;
    string fn = "p9";
//
    user_trace( 1, fn, debug );
//
	cout << endl << fixed << setw(55) \
        << "Water Network Analysis Output" << endl << endl;
//
	nspace = ((80-title.length())/2)+title.length();
	cout << fixed << setw (nspace) << title << endl << endl;
//
	cout << "Number of Nodes: " << num_nodes << endl;
	cout << "Number of Pipes: " << num_pipes << endl;
	cout << "Reservoir Node: " << reser_node << endl;
	cout << "Reservoir Head: " << setprecision(1) << \
         reser_head << endl << endl;
//
	cout << "Pipe   " << "Start-Node   " << "End-Node   " \
         << "Length (ft)   " << "Diameter(in)   " << \
            "Hazen coefficient" << endl;
	for( int i = 1; i <= num_pipes; i++ )
	{
		cout << right << fixed << setw(3) << i;
		cout << right << fixed << setw(10) << node_table(i,1);
		cout << right << fixed << setw(10) << node_table(i,2);
		cout << right << fixed << setw(17) << setprecision(1) << lengths(i);
		cout << right << fixed << setw(12) << setprecision(1) << diameters(i);
		cout << right << fixed << setw(16) << setprecision(1) \
             << hw_coeffs(i) << endl;
	}
//
	cout << endl << "Node" << '\t' << "External Flow Rate (cfs)" \
         << '\t' << "Initial Head (ft)" << endl;
	for( int i = 1; i <= num_nodes; i++ )
	{
		cout << right << fixed << setw(3) << i;
		cout << right << fixed << setw(15) << setprecision(1) \
             << external_flows(i);
		cout << right << fixed << setw(25) << setprecision(1) \
             << initial_heads(i) << endl;
	}
//
	cout << setprecision(3) << endl << "Newton Tolerance: " \
         << tolerance << endl;
	cout << "Newton Iteration Limit: " << max_iterations \
         << endl << endl;
//
    user_trace( 2, fn, debug );
	return;
}
