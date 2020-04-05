#include "system.h"
#include "prototypes.h"

int main ()
{
 const int max_pipes = 4000, max_nodes = 2000;
 int packet_type = 0, packet_info = 0, num_pipes = 0, num_nodes = 0, \
     reser_node = 0,  max_iterations = 5;
 double reser_head = 0.0, tolerance = 0.01;
 string title, trash;
 matrix <int> node_table;
 vector <double> lengths, diameters, hw_coeffs, external_flows, initial_heads, pipe_flows, heads;
 bool run = true, networkcheck = false, debug = true, net_solved = false;
//
 cout << endl << "Welcome to Water Network Analysis Program!" << endl << endl;
//
 while( run )
 {
  cin >> packet_type >> packet_info;
  cout << packet_type << "  " << packet_info << endl;
  switch( packet_type )
  {
   case 0:
     p0( packet_info, debug);
     break;
//
   case 1:
     p1( max_pipes, max_nodes, num_pipes, num_nodes, title, node_table, \
         lengths, diameters, hw_coeffs, external_flows, initial_heads, \
         pipe_flows, heads, networkcheck, debug );
     if( debug ) assert( networkcheck );
     break;
//
   case 2:
     p2( reser_node, reser_head, num_nodes, networkcheck, debug );
     break;
//
   case 3:
     p3( packet_info, num_pipes, num_nodes, node_table, lengths, diameters, \
         hw_coeffs, networkcheck, debug );
     break;
//
   case 4:
     p4( packet_info, num_nodes, external_flows, networkcheck, debug );
     break;
//
   case 5:
     p5( packet_info, num_nodes, reser_node, reser_head, initial_heads, \
         networkcheck, debug );
     break;
//
   case 6:
     p6( tolerance, max_iterations, debug );
     break;
//
   case 7:
     p7( packet_info, num_pipes, num_nodes, node_table, networkcheck, \
         debug );
     break;
//
   case 8:
   pac_8( packet_info, num_nodes, num_pipes, reser_node, reser_head, node_table, \
     initial_heads, external_flows, lengths, diameters, hw_coeffs, tolerance, max_iterations, \
     net_solved, heads, pipe_flows, networkcheck, debug ) ;
     break;
//
   case 9:
     if( packet_info == 2 )
      cout << "\n   >>>  Output results is not implemented " \
           << "in this version\n" << endl;
     else if( packet_info == 1 )
      p9( num_pipes, num_nodes, reser_node, reser_head, tolerance, \
          max_iterations, title, node_table, lengths, diameters, \
          hw_coeffs, external_flows, initial_heads, debug );
     else
      cout << "Wrong choice for the output command!" << endl;
     break;
//
   case 10:
     p10( packet_info, debug );
     break;
//
   case 11:
     {
      cout << endl << "Thank you for using Water Network" \
           << " Analysis!" << endl;
      return(0);
     }
//
   default:
     cout << endl << "Invalid packet type: " << packet_type << endl;
     if( packet_info > 0 ) // discard lines for bad packet
      {
         cin.ignore ();
         for( int i = 1; i<=packet_info; i++ ) {
            getline( cin, trash, '\n');
            cout << trash << endl;
           }
      }
     break;
  } // end of switch
 } // end of while

 return (0);
}
