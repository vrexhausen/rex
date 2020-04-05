#include "system.h"
#include "prototypes.h"

//Package 8  - Requests Solution

void pac_8( int packet_info, int num_nodes, int num_pipes, int reser_node, double reser_head, matrix <int> &node_table, \
	vector <double> &initial_heads, vector <double> &external_flows, vector <double> &lengths, vector <double> &diameters, \
	vector <double> &hw_coeffs, double tolerance, int max_iterations, bool &net_solved,  \
	vector <double> &heads, vector <double> &pipe_flows, bool networkcheck, bool debug )
{
//
	string fn = "pac_8 function" ;
	user_trace(1, fn, debug) ;
//
	string mess1 = \
 	"\n>>> No network is defined, please input the network sizes....";
//
if( !networkcheck )
 {
	cout << mess1 << endl;
			user_trace( 2, fn, debug );
	return;
 }
//
	cout << endl << "The user has called for the solution of this network." << endl << flush ;
//
// 1. create variables, vectors, and arrays
//
	int n, p, iteration = 1 ;
	double maxterm ;
	double const dzero = 0.0 ;
	vector <int> ipt, link ;
	vector <double> fheads, residual_flows, f_factors, beta_factors ;
	matrix <double> jacobian ;
	bool net_complete = true ;

	ipt.create ( 1, num_nodes+1 ) ;
	for (int i=1 ; i<= num_nodes+1; i++) ipt(i)=0 ;
	link.create ( 1 , num_pipes*2 ) ;
	for (int i=1 ; i<= num_nodes+1; i++) link(i)=0 ;

	fheads.create(1, num_nodes) ;
	residual_flows.create(1,num_nodes) ;
	f_factors.create(1, num_pipes) ;
	beta_factors.create(1, num_pipes) ;
	jacobian.create(1, num_nodes, 1, num_nodes) ;
//
	if (debug) cout << "local variables/vectors/arrays assembled." << endl << flush ;
//
// 2. check network for completeness
//
//cout << "headcheck: " << initial_heads(1) << ", " << initial_heads(2) << ", " << initial_heads(3) << endl << flush ;
//cout << external_flows(2) << endl << flush ;
	cout << "beginning network check for completion... " << endl << flush ;
	for (p=1 ; p<=num_pipes ; p++ )
	{
		if (node_table(p,1) == 0) net_complete = false ;
		if (node_table(p,2) == 0) net_complete = false ;
		if (lengths(p) == 0 ) net_complete = false ;
		if (diameters(p) == 0) net_complete = false ;
		if (hw_coeffs(p) == 0) net_complete = false ;
	}
//
	if (!net_complete)
	{
		cout << "The network is not complete enough to utilize solver tool." << endl \
			<< "Please review. Call Packet 7 to determine if any nodes have no connections." << \
			 	endl << endl << flush;
		return ;
	}
	if (debug && net_complete) cout << "\tcheck 1 complete." << endl << flush ;
//
// 3. generate nodal incidences for the network
//		aka, call linkup function
//

	cout << "Building network connectivity using linkup function..." << endl << flush ;
	linkup(num_pipes, num_nodes, debug, node_table, ipt, link);
	//

		if (!linkup)
		{
			cout << "... network connectivity build failed. exiting solver." << endl << flush ;
			return ;
		}
		if (debug) //cout linkup results... see how that works in my linkup func.
//
// 4. initialize iterative solution process
//		build initial head vector for nodal heads [nodes(n,2)]
//
		if (debug) cout << "   >> building inital head vector" << endl << flush ;
		for (int n = 1 ; n <= num_nodes ; n++)
		{
			heads(n) = initial_heads(n);
		}
		heads(reser_node) = reser_head ;
		if (debug) cout << "   >> initial head vector finished." << endl << flush ;
//
// 5. execute Newton iterations to compute nodal heads
//
//		a. compute f values of all pipes
//
			compute_f_factors(num_pipes, lengths, diameters, hw_coeffs, f_factors, debug);

// writing pointer vectors to pass in node_table to beta function
// because for whatever reason the matrix breaks when I try to pass that
//
	cout << "NODE TABLE (for reference)" << endl << flush ;
	cout << "PIPE    POS NODE    NEG NODE"<< endl << flush;
	for (int r=1; r<=num_pipes; r++)
		cout << r << "        " << node_table(r,1) << "       " << node_table(r,2) << endl ;
		cout << "\t >> okur. now build pointer vectors." << endl ;
	vector <int> positive ;
	vector <int> negative ;
	positive.create(1,num_pipes) ;
	for (int q=1; q<=num_pipes; q++)
		positive(q) = node_table(q,1) ;
	negative.create(1,num_pipes) ;
	for (int q=1; q<=num_pipes; q++)
		negative(q) = node_table(q,2) ;

cout << "f factors " << endl << flush ;
if (debug)
{
	for (int i = 1 ; i<=num_pipes ; i++)
		cout << i << ":\t" << f_factors(i) << endl << flush ;
}
		while (iteration <= max_iterations)
		{

			if(debug) cout << "\n\n----------------------------------\n" << \
				"starting iteration:\t" << iteration << "...." << endl << flush ;

			cout << "f factors \n" << flush ;
			if (debug)
			{
				for (int i = 1 ; i<=num_pipes ; i++)
					cout << i << ":\t" << f_factors(i) << endl << flush ;
			}
//
//		b. compute residual flows
//
			compute_residuals(num_nodes, num_pipes, reser_node, positive, negative, residual_flows, \
												ipt, link, heads, external_flows, \
												max_iterations, f_factors, maxterm, debug) ;
												// need to change the rest of code to match
												// iheads and eflows vectors
//
			cout << "f factors \n" << flush ;
			if (debug)
			{
				for (int i = 1 ; i<=num_pipes ; i++)
					cout << i << ":\t" << f_factors(i) << endl << flush ;
				}
//		c. check for convergence
//				examine maximum residual
//
			if (maxterm <= tolerance)
			{
				cout << "   >> nonlinear solution converged..." << endl << flush ;
				compute_pipe_flows(num_pipes, node_table, heads, pipe_flows, f_factors, debug) ;\
				net_solved = true ;
				return ;
			}
//
//		d. compute beta factors using current solutionestimate
//
			cout << "check: pos(1): " << positive(1) << ";\t neg(2)" << negative(2) << endl << flush ;
			cout << "f factors \n" << flush ;
			if (debug)
			{
				for (int i = 1 ; i<=num_pipes ; i++)
					cout << i << ":\t" << f_factors(i) << endl << flush ;
			}
			compute_beta_factors( num_pipes, f_factors, heads, beta_factors, positive, negative, debug ) ;
//
//		e. form the jacobian matrix using current estimate of nodal heads
//
			compute_jacobian ( num_nodes, jacobian, node_table, link, ipt, \
												reser_node, beta_factors, debug ) ;
//
//		f. zero solution vector for linear equations (fheads)
//				solve linear system for fheads using jacobian and residual_flows
//
			for (int n = 1 ; n <= num_nodes ; n++)
			{
				fheads(n) = dzero ;
			}

			if (linear_solver ( jacobian, fheads, residual_flows, num_nodes, debug))
			{
				cout << "\nlinear solver failed" << endl << flush ;
				user_trace(2, fn, debug) ;
				return ;
			}

			if (debug)
			{
				cout << "corrective heads from solver and new heads"
				 	<< "for next iteration: " << endl << flush ;
				for (int n=1 ; n<= num_nodes ; n++ )
				{
					cout << "\t>> node, delta H, new H: " << n << ",  " << \
						fheads(n) << ",  " << fheads(n) + heads(n) << endl ;
				}
			}
//
//		g. update heads!
//
			for (int n=1 ; n<=num_nodes ; n++)
				heads(n) = heads(n) + fheads(n) ;
//
//		END OF ITERATION
//
			if (debug)
			{
				cout << "...completed iteration \t" << iteration << "...." << \
				endl << "----------------------------------\n" << flush ;
			}
			++iteration ;
		} //iteration while loop
//
	user_trace(2 , fn, debug) ;
//
	return ;
}
