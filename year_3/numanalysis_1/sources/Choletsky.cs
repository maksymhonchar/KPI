using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace rgrapp
{
    static class Choletsky
    {
        public static void CholetskyL(double[][] A, double[][] L, int n)
        {
            // Solves the L of input matrix A.
            // Satisfies the equation: L*L^T = A.

            // First, check if all elements on the main diagonal are positive.
            for (int i = 0; i < n; i++)
            {
                if (A[i][i] <= 0)
                {
                    Console.WriteLine("Cant solve matrix A using Cholesky method.");
                    Console.WriteLine("Reason: element on the main diagonal is not positive.");
                    throw new ArgumentException();
                }
            }

            /*
             * КРИТЕРИЙ СИЛЬВЕСТРА
             * 
             * Определители всех угловых миноров матриц положительны.
             * 
             * В соответствии с этим критерием у положительно полуопределённых матриц все угловые миноры
             * неотрицательны, что, тем не менее, не является достаточным условием для положительной полуопределённости матрицы,
             * как видно из следующего примера:
             * |1 1 1|
             * |1 1 1|
             * |1 1 0|
             */

            Console.WriteLine("Getting the L matrix using Choletsky method.");
            
            for (int i = 0; i < n; i++)
            { 
                for (int k = 0; k < i+1; k++)
                {
                    double sum = 0;
                    for (int j = 0; j < k; j++)
                    {
                        sum += L[i][j] * L[k][j];
                    }

                    if (i == k)
                    {
                        L[i][k] = Math.Sqrt(A[i][i] - sum);
                    }
                    else
                    {
                        L[i][k] = (1.0 / L[k][k] * (A[i][k] - sum));
                    }
                }
            }
        }

        public static double Det(double[][] L, int n)
        {
            double det = 1;
            for (int i = 0; i < n; i++)
            {
                det *= Math.Pow(L[i][i], 2);
            }

            return det;
        }

        public static void Inv(double[][] L, double[][] Lt, double[][] Inv, int n)
        {
            /*
             * A^(-1)*A = I
             * 
             * if A = L*L^T:
             *   then A^(-1)*L*L^T = I
             *   
             * let T = A^(-1)*L
             *   
             * then T*L^T = I  
             */

            // Identity matrix: I
            double[][] ident_matrix = new double[n][];
            for (int i = 0; i < n; i++)
            {
                ident_matrix[i] = new double[n];
                for (int j = 0; j < n; j++)
                {
                    if (i == j)
                        ident_matrix[i][j] = 1;
                    else
                        ident_matrix[i][j] = 0;
                }
            }

            // Temporary matrix: T
            double[][] T = new double[n][];
            for (int i = 0; i < n; i++)
            {
                T[i] = new double[n];
                for (int j = 0; j < n; j++)
                {
                    T[i][j] = 0;
                }
            }

            // Find T matrix
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    double summ = 0;
                    for (int k = i; k < j; k++)
                    {
                        summ += T[i][k] * Lt[k][j];
                    }
                    T[i][j] = (ident_matrix[i][j] - summ) / Lt[j][j];
                }
            }            

            // Find inverse matrix
            for (int i = n-1; i >= 0; i--)
            {
                for (int j = n-1; j >= 0; j--)
                {
                    double summ = 0;
                    for (int k = n-1; k > i; k--)
                    {
                        summ += L[k][i] * Inv[j][k];
                    }
                    Inv[j][i] = (T[j][i] - summ) / L[i][i];
                }
            }
        }

        public static void Solve(double[][] L, double[][] Lt, double[] B, double[] X, int n)
        {
            /*
             * L*L^T * X = B
             * 
             * L^T * X = Z
             * L * Z = B
             * 
             * where L is lower tr matrix
             *       L^T is upper tr matrix
             */

            double[] Z = new double[n];

            SubsForth(L, B, Z, n);
            SubsBack(Lt, Z, X, n);
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
    }
}
