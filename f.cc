#include "system.h"
#include "prototypes.h"

// Package 8.1 - Compute F Factors function

void compute_f_factors(int num_pipes, vector <double> lengths, vector <double> diameters,
    vector <double> hw_coeffs, vector <double> &f_factors, bool debug)
{
  //
  	string fn = "f factor function" ;
  	user_trace(1 , fn, debug) ;
  //
  double num , denom ;
  double const chw = 1.852, cd = 4.87, top = 8.52e5 ;
  for (int p=1 ; p<=num_pipes ; p++)
  {
    num = top*lengths(p) ;
    denom = ( pow(hw_coeffs(p) , chw) * pow(diameters(p) , cd ) ) ;
    f_factors(p) = num / denom ;
  }
//
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
