using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace rgrapp
{
    static class MatrixUtils
    {
        public static void MultiplySqM(double[][] A, double[][] B, double[][] R, int n)
        {
            for (int i = 0; i < n; i++)
            { 
                for (int j = 0; j < n; j++)
                {
                    R[i][j] = 0;
                    for (int k = 0; k < n; k++)
                    {
                        R[i][j] += A[i][k] * B[k][j];
                    }
                }
            }
        }

        public static void ShowSqM(double[][] A, int n)
        {
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                    Console.Write(String.Format("{0, 8:0.000}", A[i][j]));
                Console.Write("\n");
            }
            Console.WriteLine("");
        }

        public static void ShowM(double[][] A, int rows, int cols)
        {
            for (int i = 0; i < rows; i++)
            {
                for (int j = 0; j < cols; j++)
                {
                    Console.Write(String.Format("{0, 9:0.0000}", A[i][j]));
                }
                Console.Write("\n");
            }
            Console.WriteLine("");
        }

        public static void ShowVector(double[] A, int n)
        {
            for (int i = 0; i < n; i++)
            {
                Console.WriteLine(String.Format("{0, 8:0.000}", A[i]));
            }
            Console.WriteLine("");
        }

        public static double DeterminantSqM(double[][] A, int n)
        {
            double detA = 0;

            if (n == 1)
                return A[0][0];

            int sign = 1;
            double[][] cofactorsTmp = new double[n][];
            for (int i = 0; i < n; i++)
                cofactorsTmp[i] = new double[n];

            for (int i = 0; i < n; i++)
            {
                MinorSqR(A, cofactorsTmp, 0, i, n);
                detA += sign * A[0][i] * DeterminantSqM(cofactorsTmp, n - 1);
                sign = -sign;
            }

            return detA;
        }

        public static void MinorSqR(double[][] A, double[][] R, int p, int q, int n)
        {
            int i = 0, j = 0;
            for (int row = 0; row < n; row++)
            {
                for (int col = 0; col < n; col++)
                {
                    if (row != p && col != q)
                    {
                        R[i][j++] = A[row][col];

                        if (j == n-1)
                        {
                            j = 0;
                            i++;
                        }
                    }
                }
            }
        }

        public static void AdjointSqM(double[][] A, double[][] Adj, int n)
        {
            int sign = 1;
            double[][] cofactorTmp = new double[n][];
            for (int i = 0; i < n; i++)
                cofactorTmp[i] = new double[n];

            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    MinorSqR(A, cofactorTmp, i, j, n);
                    sign = ( (i+j) % 2 == 0 ) ? 1 : -1;

                    Adj[j][i] = sign * DeterminantSqM(cofactorTmp, n-1);
                }
            }
        }

        public static void InvertSqM(double[][] A, double[][] Inv, int n)
        {
            double detA = DeterminantSqM(A, n);
            if (0 == detA)
                return;

            double[][] adjoint = new double[n][];
            for (int i = 0; i < n; i++)
                adjoint[i] = new double[n];

            AdjointSqM(A, adjoint, n);

            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    Inv[i][j] = adjoint[i][j] / detA;
        }

        public static void RoundSqM(double[][] A, int n)
        {
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    double rounded = Math.Round(A[i][j], 2);
                    if (Math.Abs(rounded - A[i][j]) > 0.001)
                    {
                        A[i][j] = Math.Round(A[i][j], 5);
                    }
                    else
                    {
                        A[i][j] = Math.Round(A[i][j]);
                    }
                }
            }
        }

        public static void TransposeSqM(double[][] A, int n)
        {
            double[][] aCopy = new double[n][];
            for (int i = 0; i < n; i++)
            {
                aCopy[i] = new double[n];
                for (int j = 0; j < n; j++)
                {
                    aCopy[i][j] = A[i][j];
                }
            }

            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    A[j][i] = aCopy[i][j];
                }
            }
        }

        public static void CopySqM(double[][] To, double[][] From, int n)
        {
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    To[i][j] = From[i][j];
                }
            }
        }
    }
}
