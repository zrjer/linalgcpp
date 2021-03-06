/*! @file */

#ifndef PARUTILITIES_HPP__
#define PARUTILITIES_HPP__

#include "seq_mv.h"

#include "coomatrix.hpp"
#include "parmatrix.hpp"
#include "parvector.hpp"

namespace linalgcpp
{

class ParMatrix;

/// Split a square matrix between processes
ParMatrix ParSplit(MPI_Comm comm, const linalgcpp::SparseMatrix<double>& A_global, const std::vector<int>& proc_part);

/// Generate offsets given local sizes
std::vector<HYPRE_Int> GenerateOffsets(MPI_Comm comm, int local_size);

/// Generate multiple offsets given local sizes
std::vector<std::vector<HYPRE_Int>> GenerateOffsets(MPI_Comm comm, const std::vector<int>& local_sizes);

/// Sort a column map and permute the corresponding coo matrix
void SortColumnMap(std::vector<HYPRE_Int>& col_map, linalgcpp::CooMatrix<double>& coo_offd);

/// Compute C = A * B
ParMatrix Mult(const ParMatrix& lhs, const ParMatrix& rhs);

/// Compute C = A^T
ParMatrix Transpose(const ParMatrix& mat);

/// Compute C = R^T * A * P
ParMatrix RAP(const ParMatrix& R, const ParMatrix& A, const ParMatrix& P);

/// Compute C = P^T * A * P
ParMatrix RAP(const ParMatrix& A, const ParMatrix& P);

/// Compute C = A + B
/** @note Row starts must match between A and B */
ParMatrix ParAdd(const ParMatrix& A, const ParMatrix& B);

/// Compute C = (alpha * A) + (beta * B)
/** @note Row starts must match between A and B */
ParMatrix ParAdd(double alpha, const ParMatrix& A, double beta, const ParMatrix& B);

/// Compute C = (alpha * A) + (beta * B)
/** @note Row starts must match between A and B */
/** @note Uses array of size global columns as workspace,
    reuse this array if multiple additions. */
/** @note This may be made more efficient, goes through
    CooMatrix instead of building in place */
ParMatrix ParAdd(double alpha, const ParMatrix& A, double beta, const ParMatrix& B,
                 std::vector<int>& marker);

/// Compute C = A - B
/** @note Row starts must match between A and B */
ParMatrix ParSub(const ParMatrix& A, const ParMatrix& B);

/// Compute C = (alpha * A) - (beta * B)
/** @note Row starts must match between A and B */
/** @note Uses array of size global columns as workspace,
    reuse this array if multiple additions. */
ParMatrix ParSub(double alpha, const ParMatrix& A, double beta, const ParMatrix& B);

/// Compute C = (alpha * A) - (beta * B)
/** @note Row starts must match between A and B */
ParMatrix ParSub(double alpha, const ParMatrix& A, double beta, const ParMatrix& B, std::vector<int>& marker);

} // namespace linalgcpp
#endif // PARUTILITIES_HPP__
