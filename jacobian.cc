#include "system.h"
#include "prototypes.h"

//Package 8.5 - Calculate and fill jacobian matrix

void compute_jacobian ( int num_nodes, matrix <double> &jacobian, matrix <int> node_table, \
                        vector <int> link, vector <int> ipt, \
                        int reser_node, vector <double> beta_factors, bool debug )
{
//
  string fn = "jacobian" ;
  user_trace(1, fn, debug) ;
//
//set local variables
  string tab = "\t" ;
  double const dzero = 0.0 ;

  int kkount, k , pipe_sign, sn, en, link_start, link_end ;
//
cout << "Check 1" << endl << flush ;
// 1. zero all terms
  for (int m = 1 ; m< num_nodes ; m++)
    for (int k=1 ; k<num_nodes ; k++) jacobian(m,k) = dzero ;
cout << " Checl 2" << endl << flush;
// 2. Loop over all nodes (except reser_node)
  for (int m=1 ; m<=num_nodes ; m++)
  {
    cout << "check, entered loop 1" <<  endl <<  flush ;
//    a.  loop over all pipes INCIDENT ON Node
//        k = link(n), link(n+1) -1
//
//        i.  get pipe # from from nodal pipe_incidences
//            >> pipe# = k
    link_start = ipt(m) ;
    link_end = ipt(m+1) ;
    for (int i = link_start ; i<link_end ; i++)
    {
      k = link(i) ;
//        ii. save sign (+,=) of pipe, then fabs(link(pipe))
      if (k>0) pipe_sign = 1 ;
      if(k<0) pipe_sign = -1 ;
      k = fabs(k) ;
//        iii. set sn and en (start and end nodes) for pipe k
//               sn = incidences(p,1)
//               en = incidences(p,2)
      sn = node_table(k,1) ;
      en = node_table(k,2) ;
//        iv. build [J].
//            include beta value twice on row node of [J]
//              add if:         subtract if:
//              sign>0, sn      sign>0 , en
//              sign<0 , en     sign<0 , sn
      if (pipe_sign = 1)
      {
        jacobian(sn, k) = jacobian(sn,k) + beta_factors(k) ;
        jacobian(en, k) = jacobian(en,k) - beta_factors(k) ;
      }
      if (pipe_sign = -1)
      {
        jacobian(sn, k) = jacobian(sn, k) - beta_factors(k) ;
        jacobian(en, k) = jacobian(en, k) + beta_factors(k) ;
      }
      //row m extra beta
      jacobian(m, k) = jacobian(m, k) + beta_factors(k) ;
//    b. end k loop over pipes on nodes
}
//  3. end node loop over all nodesstr
    }
//  4. zero row r and column r of [J]
//     set J(r,r) = 1.0
  for (int i=1 ; i<=num_nodes ; i++)
  {
    jacobian (reser_node, i) = dzero ;
    jacobian(i, reser_node) = dzero ;
  }
  jacobian(reser_node, reser_node) = jacobian(reser_node, reser_node) / jacobian(reser_node, reser_node) ;;
      // ^ " " = 1.0, but a deconstructor was expected so I worked around
//
  if (debug)
  {
    cout << endl << "JACOBIAN CHECK:" <<endl << flush ;

    for(int k=1 ; k<=num_nodes ; k++)
    {
      for (int m=1 ; m<=num_nodes ; m++)
      {
        cout << m << ":" << tab << flush ;
        cout << setprecision(3) << setw(8) << right << fixed << jacobian(k,m);
      }
      cout << endl << flush ;
    }
  }

user_trace(2, fn, debug  ) ;

return ;
}
//  1. zero all terms
// 2. Loop over all nodes (except reser_node)
//    a.  loop over all pipes INCIDENT ON Node
//        k = link(n), link(n+1) -1
//        i.  get pipe # from from nodal pipe_incidences
//            >> pipe# = k
//        ii. save sign (+,=) of pipe, then fabs(link(pipe))
//        iii. set sn and en (start and end nodes) for pipe p
//               sn = incidences(p,1)
//            sn = incidences(p,2)
//        iv. compute beta using current fheads vector
//             keep beta>0 by using fabs(fhead(p))
//        v.  include beta value twice on row node of [J]
//              add if:         subtract if:
//              sign>0, sn      sign>0 , en
//              sign<0 , en     sign<0 , sn
//    b. end k loop over pipes on nodes
//  3. end node loop over all nodesstr
//  4. zero row r and column r of [J]
//  5. set J(r,r) = 1.0
