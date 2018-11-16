import math
import numpy


def main_func(x):
    return (math.sinh(math.sqrt(1 - x))) / (math.sqrt(1 - x))


class Trapezoidal(object):
    def __init__(self, integral_func):
        self.func = integral_func

    def integral(self, a_start, b_end, n_sub_intervals):
        # Check for some incorrect input.
        if a_start > b_end:
            raise ValueError('[A] is greater than [B]')
        if n_sub_intervals <= 0:
            raise ValueError('[n] is equal or less than 0')
        if a_start == b_end:
            return {
                'x_coord_intervals': a_start,
                'y_coord_intervals': self.func(a_start),
                'h_interval': 0.0,
                'integral': 0.0
            }

        # Array to hold X coordinates for each interval. Type: array of doubles.
        x_coord_intervals = list()
        # Array to hold Y coordinates for each interval. Type: array of doubles.
        y_coord_intervals = list()
        # Variable to hold sum of inner trapezoid values. Type: double.
        sum_inner_trapezoids = 0.0
        # Get elementary interval length. Type: double.
        h_interval = (b_end - a_start) / n_sub_intervals
        # Get exact X and Y values for start of each interval.
        for i in range(n_sub_intervals + 1):  # Loop: (i=0;i<=n;i++)
            x_coord_intervals.append(a_start + i * h_interval)
            y_coord_intervals.append(
                self.func(x_coord_intervals[i])
            )
        # Evaluate sum of elementary trapezoids, excluding starting and ending points.
        for i in range(1, n_sub_intervals):  # Loop: (i=1;i<n;i++)
            sum_inner_trapezoids += h_interval * y_coord_intervals[i]
        # Evaluate final integral value. Type: double.
        two_outer_trapezoids = (y_coord_intervals[0] + y_coord_intervals[-1]) / 2.0
        integral_value = h_interval * two_outer_trapezoids + sum_inner_trapezoids
        # Return data from whole algorithm as dictionary.
        return {
            'x_coord_intervals': x_coord_intervals,
            'y_coord_intervals': y_coord_intervals,
            'h_interval': h_interval,
            'integral': integral_value
        }


class Romberg(object):
    def __init__(self, integral_func, epsilon_pwr):
        self.func = integral_func
        self.epsilon_pwr = epsilon_pwr

    def integral(self, a_start, b_end, n_max):  # n_max: maximal levels of recursion
        r_kminus1_hi_holder = list()
        h_step_holder = list()

        main_array = numpy.array([[0] * (n_max + 1)] * (n_max + 1), float)
        h = b_end - a_start  # h0
        main_array[0, 0] = 0.5 * h * (self.func(a_start) + self.func(b_end))
        power_of_2 = 1
        i = 0

        h_step_holder.append(h)

        while True:
            i += 1

            # Update stepsize: halve it.
            # Use updated h to sum at all the new points (in between the points already computed)
            h = 0.5 * h

            sum = 0.0
            power_of_2 = 2 * power_of_2
            for k in range(1, power_of_2, 2):
                sum += self.func(a_start + k * h)

            # Compute the composite trapezoid rule for the next level of subdivision.
            # Use Richardson extrapolation to make these values more accurate.
            main_array[i, 0] = 0.5 * main_array[i - 1, 0] + sum * h

            h_step_holder.append(h)

            power_of_4 = 1
            for j in range(1, i + 1):
                power_of_4 = 4 * power_of_4
                r_kminus1_hi = (main_array[i, j - 1] - main_array[i - 1, j - 1]) / (power_of_4 - 1)
                r_kminus1_hi_holder.append(r_kminus1_hi)
                main_array[i, j] = main_array[i, j - 1] + r_kminus1_hi
                if math.fabs(r_kminus1_hi) <= math.pow(math.e, self.epsilon_pwr):
                    main_array_jsonify = main_array.tolist()
                    return {
                        'final_step': i + 1,
                        'r_kminus1_hi_values': r_kminus1_hi_holder,
                        'final_array': main_array_jsonify,
                        'h_step_holder': h_step_holder
                    }
