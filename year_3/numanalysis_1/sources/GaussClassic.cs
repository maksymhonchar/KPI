using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace rgrapp
{
    static class GaussClassic
    {
        public static void GaussElimination(double[][] A, double[] X, int n)
        {
            int swappingFlag = 0;

            // Pivoting.
            for (int i = 0; i < n; i++)
            {
                for (int k = i + 1; k < n; k++)
                {
                    if (Math.Abs(A[i][i]) < Math.Abs(A[k][i]))
                    {
                        swappingFlag++;
                        for (int j = 0; j <= n; j++)
                        {
                            double temp = A[i][j];
                            A[i][j] = A[k][j];
                            A[k][j] = temp;
                        }
                    }
                }
            }

            Console.WriteLine("Matrix after pivoting:");
            MatrixUtils.ShowM(A, n, n + 1);

            // Elimination.
            for (int i = 0; i < n - 1; i++)
            { 
                for (int k = i + 1; k < n; k++)
                {
                    double t = A[k][i] / A[i][i];
                    for (int j = 0; j <= n; j++)
                    {
                        //make the elements below the pivot elements equal to zero or elimnate the variables.
                        A[k][j] = A[k][j] - t * A[i][j];    
                    }
                }
            }

            Console.WriteLine("Matrix after elimination:");
            MatrixUtils.ShowM(A, n, n + 1);

            // Check if some of the arguments on the main diagonal equals to 0.
            for (int i = 0; i < n; i++)
            {
                if (A[i][i] == 0)
                {
                    Console.WriteLine("Noticed FREE argument with index {0}, starting from 0", i);
                }
            }

            // Check if at least one B[i] after elimination does not equal to 0.
            bool matrixHasSolution = false;
            for (int i = 0; i < n; i++)
            {
                if (A[i][n] != 0)
                {
                    matrixHasSolution = true;
                }
            }
            if (!matrixHasSolution)
            {
                Console.WriteLine("Matrix A does not have solutions.");
                Console.WriteLine("Reason: after elimination there are no B[i], which does not equal to 0");
                throw new ArgumentException();
            }
            // Check if there are MORE AMOUNT OF VARIABLES THAN EQUATIONS.
            for (int i = 0; i < n; i++)
            { /* TODO */  }

            // Back-substitution.
            for (int i = n - 1; i >= 0; i--)
            {
                X[i] = A[i][n];
                for (int j = n - 1; j > i; j--)
                {
                    X[i] -= A[i][j] * X[j];
                }
                X[i] = X[i] / A[i][i];
            }

            // Determinant of a matrix.
            double det = 1;
            for (int i = 0; i < n; i++)
            {
                det *= A[i][i]; 
            }
            det = (swappingFlag % 2 == 0) ? det : -det;
            Console.WriteLine("Determinant is: {0}\n", det);
        }

        public static void Inv(double[][] A, int n)
        {
            // Init n*2 matrix to invert.
            double[][] Inv = new double[n][];
            for (int i = 0; i < n; i++)
            {
                Inv[i] = new double[n * 2];
                for (int j = 0; j < n*2; j++)
                {
                    Inv[i][j] = 0;
                }
            }

            // LEFT SIDE: Fill up Inv matrix with values from A.
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    Inv[i][j] = A[i][j];
                }
            }

            // RIGHT SIDE: Full up with ones on the main diagonal.
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n*2; j++)
                {
                    if (j == (i+n))
                    {
                        Inv[i][j] = 1;
                    }
                }
            }

            Console.WriteLine("Inverting, using such matrix:");
            MatrixUtils.ShowM(Inv, n, n * 2);

            // Pivoting.
            for (int i = n - 1; i >= 1; i--)
            {
                // if (Inv[i - 1][0] < Inv[i][0])
                if (Math.Abs(Inv[i - 1][0]) < Math.Abs(Inv[i][0]))
                { 
                    for (int j = 0; j < n * 2; j++)
                    {
                        double d = Inv[i][j];
                        Inv[i][j] = Inv[i - 1][j];
                        Inv[i - 1][j] = d;
                    }
                }
            }

            Console.WriteLine("Matrix after pivoting:");
            MatrixUtils.ShowM(Inv, n, n * 2);

            // Reducing.
            for (int j = 0; j < n; j++)
            {
                for (int i = 0; i < n; i++)
                {
                    if (i != j)
                    {
                        double d = Inv[i][j];
                        for (int k = 0; k < 2*n; k++)
                        {
                            Inv[i][k] -= (Inv[j][k] / Inv[j][j]) * d;
                        }
                    }
                    else
                    {
                        double d = Inv[i][j];
                        for (int k = 0; k < 2 * n; k++)
                        {
                            Inv[i][k] /= d;
                        }
                    }
                }
            }

            Console.WriteLine("Matrix after reducing:");
            MatrixUtils.ShowM(Inv, n, n * 2);

            Console.WriteLine("The inversed matrix is on the right side.");
        }
    }
}
