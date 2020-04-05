/********************************************************************
 *                                                                  *
 *    function:    p3                                               *
 *                                                                  *
 *    purpose: process packet type 3. pipe properties               *
 *    written by:  r. h. dodds                                      *
 *    last revision: rhd 3/12/2020 -- original coding               *
 *                                                                  *
 ********************************************************************/
//
#include "system.h"
#include "prototypes.h"

void p3( int packet_info, int num_pipes, int num_nodes, \
         matrix <int> &node_table, vector <double> &lengths, \
         vector <double> &diameters, vector <double> &hw_coeffs, \
         bool networkcheck, bool debug )
{
	int sn, en, pipe;
	double len, dia, hw, zero = 0.0;
	string trash, fn = "p3";
//
    user_trace( 1, fn, debug );
//
	if (!networkcheck )
	 {
		cout << "No network is defined, please input the network sizes." << endl;
		for( int i=1; i<=packet_info; i++ )
			getline( cin, trash );
        user_trace( 2, fn, debug );
		return;
	 }
//
	for( int i = 1; i <= packet_info; i++ )
	 {
		cin >> pipe >> sn >> en >> len >> dia >> hw;
        cout << "   " << pipe << " " << sn << " " << en << " " << len << " "\
             << dia << " " << hw << endl;
		if( pipe <= 0 || pipe > num_pipes )
		 {
			cout << "Pipe No." << pipe << ":" << endl;
			cout << "Pipe number is out of the acceptable range;" \
                 << " pipe ignored." << endl;
			continue;
		 }
		if( sn <= 0 )
		 {
			cout << "Pipe No." << pipe << ":" << endl;
			cout << "Starting node not acceptable, set to" \
                 << " default (0)." << endl;
			sn = 0;
		 }
		if( en <= 0 )
		 {
			cout << "Pipe No." << pipe << ":" << endl;
			cout << "Ending node not acceptable, set to default (0)." << endl;
			en = 0;
		 }
		if( len <= zero )
		 {
			cout << "Pipe No." << pipe << ":" << endl;
			cout << "Length not acceptable, set to default (0)." << endl;
			len = zero;
		 }
		if( dia <= zero )
		 {
			cout << "Pipe No." << pipe << ":" << endl;
			cout << "Diameter not acceptable, set to default (0)." << endl;
			dia = zero;
		 }
		if( hw <= zero )
		 {
			cout << "Pipe No." << pipe << ":" << endl;
			cout << "Hazen-Williams coefficient not acceptable, " \
                 << "set to default (0)." << endl;
			hw = zero;
		 }
		node_table(pipe,1) = sn;
		node_table(pipe,2) = en;
		lengths(pipe)      = len;
		diameters(pipe)    = dia;
		hw_coeffs(pipe)    = hw;
	 } // for over pipe data lines
//
	 if( debug )
	  {
	   cout << "Pipe   " << "Start-Node   " << "End-Node" << "Length (ft)   " \
            << "Diameter(in)   " << "H-W coefficient" << endl;
       for( int i=1; i<=num_pipes; i++ )
		 cout << i << '\t' << node_table(i,1) << '\t' << node_table(i,2) << \
          '\t' << lengths(i) << '\t' << diameters(i) << '\t' << hw_coeffs(i) \
          << '\t' << endl;
	  }
//
    user_trace( 2, fn, debug );
	return;
}
