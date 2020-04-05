#include "system.h"
#include "prototypes.h"

// Package 7 - Linkup / nodal incidences

bool linkup( int num_pipes, int num_nodes, bool &debug, matrix <int> &node_table, vector <int> &ipt, vector <int> &link)
{
//
	string fn = "linkup function" ;
	user_trace(1, fn, debug) ;
//
	//linkup local variables
	int pos_node , neg_node , pipe_id ;

	//allocate kount
		//create kount vector
	vector <int> kount ;
	kount.create ( 1, num_nodes) ;
	for (int i=1 ; i<=num_nodes ; i++) kount(i) = 0;
		//fill kount
			//NOTE: POSITIVE NODE  = ORIGIN ; NEG NODE = TERMINUS
	for (int branch_id = 1; branch_id <=num_pipes; branch_id++)
	{
		pos_node = node_table(branch_id, 1);
		neg_node = node_table(branch_id, 2) ;

		++kount(pos_node) ;
		++kount (neg_node) ;

	}

	//check kount for 0 entries ;
		// build kount 0 vector to store vector point
	vector <int> kountzero ;
	kountzero.create( 1, num_nodes ) ;
	bool header_output = false ;
	for (int i=1 ; i<=num_nodes ; i++ )
	{

		if ( kount(i) == 0 )
		{
			kountzero (i) = 1 ;
		}
		else {
			kountzero (i) = 0 ;
		}
	}
	//print error message for 0s in kount
	for ( int i = 1 ; i <= num_nodes ; i++ )
	{
		if ( kountzero(i)  == 1 )
		{
			header_output = true ;
			break ;
		}
	}

	if (header_output) // if there are any 0s in kount:
	{
		//print 'pretty' error
		cout << endl << "The following nodes had zero connections: \n" << flush ;
		for ( int i = 1 ; i <= num_nodes ; i++ )
		{
			if ( kountzero(i) == 1 )
			{
				cout << "     " << i << endl << flush ;
			}
		}
		cout << "Please correct the network before solving." << endl << flush;
		//return to main with linkup = false
		return false;
	}

	//fill ipt vector
	ipt(1) = kount(1)+1 ;
	for(int n=2 ; n<=num_nodes ; n++)
			ipt(n) = kount(n) + ipt(n-1) ;
	ipt(num_nodes+1) = ipt(num_nodes) ;

	//fill link vector
	for (int pipe=1 ; pipe<=num_pipes ; pipe++)
	{
		pos_node = node_table(pipe,1);
    neg_node = node_table(pipe,2);
    --ipt(pos_node);
    link(ipt(pos_node)) = pipe;
    --ipt(neg_node);
    link(ipt(neg_node)) = -pipe;
	}
	//free kount
	kount.free() ;
//output results
	cout << "\nNODE No. \t BRANCHES ATTACHED" << endl << flush ;
			//for loop which runs for the number of nodes in network
	for (int w = 1 ; w<=num_nodes ; w++)
	{
		//print NODE no.
		cout << endl << setw(5) << right << w << flush ;
		cout << "             " << flush ;
		//read where to start listing items from LINK
		int link_start = ipt(w) ;
		//read where to stop listing items from link
		int link_end = ipt(w+1) ;
		//print values in LINK (listing branches attached)
			//for loop interates while in between link_start and link_end
		for ( int j = link_start ; j < link_end ; j++ )
		{
			cout << link(j) << " " << flush ;
		}
	}
	cout << endl << endl << flush ;

//
	user_trace(2, fn, debug) ;
	return true;
}
