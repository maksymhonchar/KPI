using System;
using System.Diagnostics;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace rgrapp
{
    class Program
    {
        static void Main(string[] args)
        {
            Random rnd = new Random();
            const int n = 10;

            // Conditions.
            double[][] A = new double[n][];
            A[0] = new double[] { 208, 90, -46, 5, -79, -116, -41, 45, -67, 94 };
            A[1] = new double[] { 90, 185, -40, 120, -1, 27, 18, 48, -31, 38 };
            A[2] = new double[] { -46, -40, 235, 15, 22, -47, -92, -46, -2, -149 };
            A[3] = new double[] { 5, 120, 15, 190, 13, 111, 39, 21, -32, -37 };
            A[4] = new double[] { -79, -1, 22, 13, 176, 62, 24, -36, 128, 43 };
            A[5] = new double[] { -116, 27, -47, 111, 62, 186, 94, 4, 21, -16 };
            A[6] = new double[] { -41, 18, -92, 39, 24, 94, 194, 154, 123, 110 };
            A[7] = new double[] { 45, 48, -46, 21, -36, 4, 154, 249, 130, 127 };
            A[8] = new double[] { -67, -31, -2, -32, 128, 21, 123, 130, 233, 117 };
            A[9] = new double[] { 94, 38, -149, -37, 43, -16, 110, 127, 117, 246 };

            double[] B = new double[] { -234, 55, 140, -163, -88, -40, -197, -99, 30, 250 };

            // Buffers.
            double[][] Inv = new double[n][];
            double[][] R = new double[n][];
            double[][] L = new double[n][];
            double[][] Lt = new double[n][];
            double[] X = new double[n];

            for (int i = 0; i < n; i++)
            {
                Inv[i] = new double[n];
                R[i] = new double[n];
                L[i] = new double[n];
                Lt[i] = new double[n];
                X[i] = 0;
                for (int j = 0; j < n; j++)
                {
                    Inv[i][j] = 0;
                    R[i][j] = 0;
                    L[i][j] = 0;
                    Lt[i][j] = 0;
                }
            }

            Console.WriteLine("A matrix: ");
            MatrixUtils.ShowSqM(A, n);

            Stopwatch stopWatch = new Stopwatch();
            stopWatch.Start();
            Console.WriteLine("Solving A using Choletsky.\n");
            Choletsky.CholetskyL(A, L, n);
            stopWatch.Stop();

            Console.WriteLine("Resulting L matrix:");
            MatrixUtils.ShowSqM(L, n);

            Console.WriteLine("transposed l matrix");
            MatrixUtils.CopySqM(Lt, L, n);
            MatrixUtils.TransposeSqM(Lt, n);
            MatrixUtils.ShowSqM(Lt, n);

            Console.WriteLine("Check for Choletsky L matrix: A=L*L^t");
            MatrixUtils.MultiplySqM(L, Lt, R, n);
            MatrixUtils.ShowSqM(R, n);

            Console.WriteLine("Get the roots using Choletsky method.");
            Choletsky.Solve(L, Lt, B, X, n);

            Console.WriteLine("Roots are:");
            MatrixUtils.ShowVector(X, n);

            double det = Choletsky.Det(L, n);
            Console.WriteLine("Determinant is: {0}\n", det);

            Stopwatch stopWatch2 = new Stopwatch();
            stopWatch2.Start();
            Console.WriteLine("Inverting using Choletsky method.");
            Choletsky.Inv(L, Lt, Inv, n);
            stopWatch2.Stop();
            Console.WriteLine("Inverted matrix:");
            MatrixUtils.ShowSqM(Inv, n);

            Console.WriteLine("Check for the inverted matrix:");
            MatrixUtils.MultiplySqM(A, Inv, R, n);
            MatrixUtils.ShowSqM(R, n);

            Console.WriteLine("Aglorithm time: {0}", stopWatch.Elapsed);
            Console.WriteLine("Inverting matrix time: {0}", stopWatch2.Elapsed);

            Console.ReadKey();
        }
    }
}
