#!/bin/bash
echo "Starting Build Script..."
\rm *.o; \rm *.go; options="-w -O0";
g++ $options p0.cc -c
g++ $options p1.cc -c
g++ $options p2.cc -c
g++ $options p3.cc -c
g++ $options p4.cc -c
g++ $options p5.cc -c
g++ $options p6.cc -c
g++ $options p7.cc -c
g++ $options pac_8.cc -c
g++ $options p9.cc -c
g++ $options p10.cc -c
g++ $options main.cc -c
g++ $options user_trace.cc -c
g++ $options residuals.cc -c
g++ $options f.cc -c
g++ $options pipeflows.cc -c
g++ $options jacobian.cc -c
g++ $options beta.cc -c
g++ $options linear_solver.cc -c
g++ $options linkup.cc -c
g++ $options p0.o p1.o p2.o p3.o p4.o p5.o p6.o p7.o \
             pac_8.o p9.o p10.o main.o user_trace.o linkup.o \
			 residuals.o f.o pipeflows.o jacobian.o beta.o linear_solver.o -o p.go;
chmod u+rwx p.go;
echo "Done..."
exit
