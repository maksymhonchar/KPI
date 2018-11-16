using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace rgrapp
{
    static class LUDecomposition
    {
        public static void LU(double[][] A, double[][] L, double[][] U, int n)
        {
            // Check for the oporniye elements on the main diagonal.
            for (int i = 0; i < n; i++)
            {
                if (A[i][i] == 0)
                {
                    Console.WriteLine("Cant solve matrix A using LU decomposition.");
                    Console.WriteLine("Reason: A[{0}][{0}] equals to 0", i);
                    throw new ArgumentException();
                }
            }

            // The algorithm.
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    U[i][j] = A[i][j];

            for (int i = 0; i < n; i++)
                for (int j = i; j < n; j++)
                    L[j][i] = U[j][i] / U[i][i];

            for (int k = 1; k < n; k++)
            {
                for (int i = k - 1; i < n; i++)
                    for (int j = i; j < n; j++)
                        L[j][i] = U[j][i] / U[i][i];

                for (int i = k; i < n; i++)
                    for (int j = k - 1; j < n; j++)
                        U[i][j] = U[i][j] - L[i][k - 1] * U[k - 1][j];
            }
        }

        public static double Det(double[][] L, double[][] U, int n)
        {
            double detL = MatrixUtils.DeterminantSqM(L, n);
            double detU = MatrixUtils.DeterminantSqM(U, n);
            double detLU = detL * detU;

            return detLU;
        }

        public static void Solve(double[][] L, double[][] U, double[] B, double[] X, int n)
        {
            /*
             * AX = b; LUX = b;
             * LZ = b
             * UX = Z
             */
            double[] Z = new double[n];

            SubsForth(L, B, Z, n);
            SubsBack(U, Z, X, n);
        }

        public static void SubsForth(double[][] A, double[] b, double[] R, int n)          
        {
            /* 
             * Function solves Ax = b for A as a lower triangular matrix 
             */

            for (int i = 0; i < n; i++)
            {
                R[i] = b[i];
                for (int j = 0; j < i; j++)
                    R[i] -= A[i][j] * R[j];
                R[i] = R[i] / A[i][i];
            }
        }

        public static void SubsBack(double[][] A, double[] b, double[] R, int n)
        {
            /*
             * Function solves Ax = b for A as an upper triangular matrix
             */

            for (int i = n - 1; i > -1; i--)
            {
                R[i] = b[i];
                for (int j = n - 1; j > i; j--)
                    R[i] -= A[i][j] * R[j];
                R[i] = R[i] / A[i][i];
            }
        }

        public static void InvKronecker(double[][] L, double[][] U, double[][] Inv, int n)
        {
            int kroneker = 0;

            for (int i = 0; i < n; i++)
            {
                Inv[i][i] = 1;
            }

            for (int helper = n-1; helper >= 0; helper--)
            {
                int i = helper;
                for (int j = i; j >= 0; j--)
                {
                    double summ = 0;
                    for (int k = j+1; k < n; k++)
                    {
                        summ += Inv[i][k] * L[k][j];
                    }
                    kroneker = i == j ? 1 : 0;
                    Inv[i][j] = 1 / L[j][j] * (kroneker - summ);
                }

                int j1 = helper;
                for (int i1 = j1-1; i1 >= 0; i1--)
                {
                    double summ = 0;
                    for (int k = i1+1; k < n; k++)
                    {
                        summ += U[i1][k] * Inv[k][j1];
                    }
                    Inv[i1][j1] = (-1) * summ;
                }
            }

        }

        public static void Inv(double[][] L, double[][] U, double[][] Inv, int n)
        {
            /*
            * A^-1 = 
            *  [ B11 B12 B13 ]
            *  [ B21 B22 B23 ]
            *  [ B31 B32 B33 ]
            * =  
            *  [ 1 0 0 ]
            *  [ 0 1 0 ]
            *  [ 0 0 1 ]
            */

            for (int i = 0; i < n; i++)
            {
                // N-th column of inverse matrix.
                double[] colValues = new double[n];
                for (int j = 0; j < n; j++)
                    colValues[j] = 0;

                // Vector with one 1.
                double[] b = new double[n];
                for (int j = 0; j < n; j++)
                    b[j] = 0;
                b[i] = 1;

                // Solve it == find the X and copy it to colValues.
                // L*Z = B
                // U*X = Z
                Solve(L, U, b, colValues, n);

                // Copy result to Inverse matrix.
                for (int j = 0; j < n; j++)
                {
                    Inv[j][i] = colValues[j];
                }
            }
        }
    }
}
