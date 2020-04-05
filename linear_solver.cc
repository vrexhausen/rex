#include "system.h"
#include "prototypes.h"

//Package 8.6 - Solver check

int linear_solver ( matrix <double> &jacobian, vector <double> &fheads, \
                  vector <double> &residual_flows, int num_nodes, bool debug)
{
//  Set local parameters
  int n, m, ll, lk, j ;
  vector <int> iwork ;
  vector <double> dwork ;
  double tolerance, workmax, rmax, r, xmult, sum ;
  double const zero = 0.0;
//
  string fn = "linear solver" ;
  user_trace(1, fn, debug) ;
//
//  1. set up pivoting indexes and vector to store maximum term on each row ;
//      create work vectors ;
//
  iwork.create(1,num_nodes) ;
  dwork.create(1,num_nodes) ;
  for (int n=1 ; n<=num_nodes; n++)
  {
    iwork(n) = n ;
    workmax = zero ;
    for (int m=1 ; m<=num_nodes ; m++)
      if ( fabs(jacobian(n,m)) > workmax) workmax = fabs(jacobian(n,m)) ;
    dwork(n) = workmax ;
  }
//
//  2.  Preform triagulation of [J] with partial pivoting.
//      terminate if a divide by zero diagonal occurs
//
  for (int k=1 ; n<=num_nodes ; n++)
  {
    rmax = zero ;
    for (n=k ; n<=num_nodes ; n++)
    {
      ll = iwork(n) ;
      if(dwork(ll) <= tolerance)
        { iwork.free() ; dwork.free() ; return(1) ; }
      r = fabs(jacobian(ll,k)) / dwork(ll) ;
      if (r > rmax)
        { rmax = r ; m = n ; }
    }
//
    lk = iwork(m) ;
    iwork(m) = iwork(k) ;
    iwork(k) = lk ;
//
    for(n=k+1 ; n<=num_nodes ; n++)
    {
      ll = iwork(n) ;
      if( fabs(jacobian(lk, k)) <= tolerance )
        { iwork.free() ; dwork.free() ; return(1) ; }
      xmult = jacobian(ll,k) / jacobian(lk,k) ;
      for(m=k+1 ; m<=num_nodes ; m++)
        jacobian(ll,m) = jacobian(ll,m) - xmult*jacobian(lk,m) ;
      jacobian(ll,k) = xmult ;
    }
  }
//
//  3.  perform back substitution to recoveer solution vector
//
  fheads(num_nodes) = residual_flows(iwork(num_nodes)) / jacobian(iwork(num_nodes),num_nodes) ;
  for(n=num_nodes-1 ; n>=1 ; n--)
  {
    ll = iwork(n) ;
    sum = residual_flows(ll) ;
    for (m=n+1 ; m<=num_nodes ; j++)
      sum = sum - jacobian(ll,j) *fheads(m) ;
    fheads(n) = sum / jacobian(ll,n) ;
  }
//
  user_trace(2, fn, debug) ;
//
  iwork.free() ;
  dwork.free() ;
//
  return(0) ;
}
// i=n , j=m , k=k, ll=ll, a = jacobian, x=fheads, b=residual_flows
