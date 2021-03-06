mkdir -p build
cd build

rm -rf CMakeCache.txt
rm -rf CMakeFiles

HYPRE_DIR=${HOME}/hypre
SUITESPARSE_DIR=${HOME}/SuiteSparse

CXX=mpic++ CC=mpicc cmake .. \
    -DLINALGCPP_ENABLE_MPI=Yes \
    -DLINALGCPP_ENABLE_METIS=Yes \
    -DLINALGCPP_ENABLE_SUITESPARSE=Yes \
    -DHypre_DIR=${HYPRE_DIR} \
    -DSUITESPARSE_INCLUDE_DIR_HINTS=${SUITESPARSE_DIR}/include \
    -DSUITESPARSE_LIBRARY_DIR_HINTS=${SUITESPARSE_DIR}/lib
