set(CMAKE_C_COMPILER       gcc-$ENV{GCC_VERSION}      )
set(CMAKE_CXX_COMPILER     g++-$ENV{GCC_VERSION}      ) 
set(CMAKE_Fortran_COMPILER gfortran-$ENV{GCC_VERSION} )

set( blacs_LIBRARIES "/usr/lib/x86_64-linux-gnu/libscalapack-mpich.so" )
