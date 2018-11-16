using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace rgrapp
{
    static class TriagonalAlgorithm
    {
        public static void Solve(double[][] A, double[] B, double[] X, int n)
        {
            double[] Tau = new double[n];
            double[] Delta = new double[n];
            double[] Lmbd = new double[n];
            for (int i = 0; i < n; i++)
            {
                Tau[i] = 0;
                Delta[i] = 0;
                Lmbd[i] = 0;
            }

            Console.WriteLine("Solving A matrix using triagonal algorithm.");
            MatrixUtils.ShowSqM(A, n);

            // The algorithm.
            // Note, that in ditriagonal method there are specific first and last iterations.

            // First iteration.
            Tau[0] = A[0][0];
            Delta[0] = (-1) * A[0][1] / Tau[0];
            Lmbd[0] = B[0] / Tau[0];

            // Other iterations.
            for (int i = 1; i < n-1; i++)
            {
                Tau[i] = A[i][i] + A[i][i - 1] * Delta[i - 1];
                Delta[i] = (-1) * A[i][i + 1] / Tau[i];
                Lmbd[i] = (B[i] - A[i][i-1] * Lmbd[i-1]) / Tau[i];
            }

            // Last iteration.
            Tau[n - 1] = A[n - 1][n - 1] + A[n-1][n-2] * Delta[n - 2];
            Delta[n - 1] = 0;
            Lmbd[n - 1] = (B[n-1] - A[n-1][n-2] * Lmbd[n-2]) / Tau[n-1];

            // Check for the coef znamennik.
            for (int i = 0; i < n; i++)
            {
                if (Tau[i] == 0)
                {
                    Console.WriteLine("TDMA is incorrect, because one of the znamennik equals to 0");
                }
            }

            Console.WriteLine("Coefficients:");
            MatrixUtils.ShowVector(Tau, n);
            Console.WriteLine("Alpha:");
            MatrixUtils.ShowVector(Delta, n);
            Console.WriteLine("Betha:");
            MatrixUtils.ShowVector(Lmbd, n);

            // Solving for X.
            X[n - 1] = Lmbd[n - 1]; // last element.
            for (int i = n-2; i >= 0; i--) // others.
            {
                X[i] = Delta[i] * X[i + 1] + Lmbd[i];
            }


            double det = Det(Tau, n);
            Console.WriteLine("Determinant for the A matrix is: {0}\n", det);

            //// The algorithm.
            //for (int i = 1; i < n; i++)
            //{
            //    double m = Ad[i - 1] / Bd[i - 1];
            //    Bd[i] -= m * Cd[i - 1];
            //    B[i] -= m * B[i - 1];
            //}
            //// solve for the last x:
            //X[n - 1] = B[n - 1] / Bd[n - 1];
            //// remaining x, using back substitution:
            //for (int i = n - 2; i >= 0; i--)
            //    X[i] = (B[i] - Cd[i] * X[i + 1]) / Bd[i];
        }

        public static double Det(double[] Tau, int n)
        {
            double det = 1;
            for (int i = 0; i < n; i++)
            {
                det *= Tau[i];
            }
            return det;
        }

        public static void GetABCFromTridiagonal(double[][] Src, double[] A, double[] B, double[] C, int n)
        {
            for (int i = 0, j = 0; i < n; i++, j++)
            {
                if (i == 0)
                {
                    A[i] = Src[i + 1][j];
                    B[i] = Src[i][j];
                    C[i] = Src[i][j + 1];
                    continue;
                }

                if (i == n - 1)
                {
                    A[i - 1] = Src[i][j - 1];
                    B[i] = Src[i][j];
                    continue;
                }

                A[i - 1] = Src[i][j - 1];
                B[i] = Src[i][j];
                C[i] = Src[i][j + 1];
            }
        }
    }
}
