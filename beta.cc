#include "system.h"
#include "prototypes.h"

//Package 8.4 - Comput beta factors

void compute_beta_factors( int num_pipes, vector <double> &f_factors, vector <double> &heads, \
                          vector <double> &beta_factors, vector <int> &positive, vector <int> &negative, bool debug )
{
//
  string fn = "beta factors..." ;
  user_trace(1, fn, debug) ;
//
  int sn , en ;
  double const alpha = 0.54, beta = alpha-1 ;

//
//
//  loop over pipes (int k)
//    1. set sn and en
//       >  node_table(k,1) - node_table(k,2)
//    2. find abs. value of difference in heads from start node (sn) to end node (en)
//    3.  divind num by f_factor(k)
//    4.  raise to "beta" constant
//    5. multiply by "alpha"
//    6. divide by f_factor(k)

  for (int k=1 ; k<=num_pipes ; k++)
  {
    //  1
    sn = positive(k) ;
    en = negative(k) ;
    //  2
    beta_factors(k) = fabs(heads(sn)-heads(en)) ;
    if (debug) cout << k << "(2):\t" << beta_factors(k) << endl << flush ;
    //  3
    beta_factors(k) = beta_factors(k)/f_factors(k) ;
    if(debug) cout << "f: " << f_factors(k) << endl << flush ;
    if (debug) cout << k << "(3):\t" << beta_factors(k) << endl << flush ;
    //  4
    beta_factors(k) = pow(beta_factors(k), beta ) ;
    if (debug) cout << k << "(4):\t" << beta_factors(k) << endl << flush ;
    //  5 and 6
    beta_factors(k) = beta_factors(k)*alpha/f_factors(k) ;
    if (debug) cout << k << "(5):\t" << beta_factors(k) << endl << flush ;
  }
//
  user_trace  (2, fn, debug) ;
//
return ;
}
