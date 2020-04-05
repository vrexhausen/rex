#include "system.h"
#include "prototypes.h"

//Package 8.2 - Compute F factors

void compute_residuals(int num_nodes, int num_pipes, int reser_node, vector <int> positive, vector <int> negative, \
                        vector <double> &residual_flows, vector <int> ipt, \
                        vector <int> link, vector <double> &heads, vector <double> external_flows, \
                        int max_iterations, vector <double> f_factors, double &maxterm, bool debug)
{
//
	string fn = "flow residuals function" ;
	user_trace(1, fn, debug) ;
//
//
// 1. initialize local variables
//
  int sn , en, n;
  double dhead, f, q ;
  double const dzero = 0.0, a = 0.54;

//
// 2. initialize residual_flows to negative of iflow
//

  //cout << "check: " << initial_heads(1) << ", " << initial_heads(2) << ", " << initial_heads(3) << endl << flush ;
  //cout << external_flows(2) << endl << flush ;
  for (int n = 1 ; n <= num_nodes ; n++)
    residual_flows(n) = -external_flows(n) ;
//
// 3. process each pipe to compute current flow rate
//
  for(int p = 1 ; p <= num_pipes; p++)
  {
    sn = positive(p) ;
    en = negative(p) ;
    dhead = heads(sn) - heads(en) ;
    f = f_factors(p) ;
    q = pow(fabs(dhead)/f , a) ;

    if (debug)
    {
      cout << "pipe, sn, en, dhead, f, q :" << endl ;
      cout << p << " ; " << sn << " ; " << en << " ; " << dhead << " ; " << \
        f << " ; " << q << endl << flush ;
    }
    if (dhead < dzero) q = -q ;
    residual_flows(sn) = residual_flows(sn) - q ;
    residual_flows(en) = residual_flows(en) + q ;
  }
  if (debug)
  {
    cout << "checkpoint" << endl << flush;
    for(int n =1 ; n<=num_nodes ; n++)
      cout << n << " :\t" << residual_flows(n) << endl << flush ;
  }
//
//    b. zero residual flow from reservoir nodes,
//        calculate maximum flow
//        prepare RHS of equation
//
  maxterm = dzero ;
  residual_flows(reser_node) = dzero ;
  for (int n=1 ; n <= num_nodes ; n++)
  {
    residual_flows(n) = -residual_flows(n) ; //RHS
    if (fabs(residual_flows(n)) > maxterm )
      maxterm = fabs(residual_flows(n)) ;
  }

  if (debug)
  {
    cout << " finished computing residuals." << endl << flush ;
    cout << "node \t \t residual flow" << endl << flush ;
    for (n=1 ; n<=num_nodes ; n++)
    {
      cout << setw(7) << n ;
      cout << fixed << setprecision(6) << setw(16) << -residual_flows(n) ;
      cout << endl << flush ;
    }
    cout << endl <<  "   >> max residual:\t" << maxterm << endl << endl << flush ;
  }

  cout << "f factors \n" << flush ;
  if (debug)
  {
  	for (int i = 1 ; i<=num_pipes ; i++)
  		cout << i << ":\t" << f_factors(i) << endl << flush ;
  }
//
  user_trace(2, fn, debug) ;
//
  return ;
}
