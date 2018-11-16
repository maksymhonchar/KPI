from django.shortcuts import render
from django.utils.decorators import method_decorator
from django.views.decorators.csrf import csrf_exempt

from .integrals import Trapezoidal, Romberg, main_func


def index(req):
    return render(req, 'index.html')


@method_decorator(csrf_exempt, name='dispatch')
def trapezoid(req):
    n_amount = 68286
    if req.method == 'POST':
        n_amount = int(req.POST['n'])
    t = Trapezoidal(main_func)
    t_solution = t.integral(-13, -5, n_amount)
    return render(req, 'trapezoid.html', context={
        'x_first_ten_coord': t_solution['x_coord_intervals'][0:10],
        'x_last_ten_coord': t_solution['x_coord_intervals'][-11:-1],
        'y_first_ten_coord': t_solution['y_coord_intervals'][0:10],
        'y_last_ten_coord': t_solution['y_coord_intervals'][-11:-1],
        'h_interval': t_solution['h_interval'],
        'n_amount': n_amount,
        'integral': t_solution['integral']
    })


def romberg(req):
    epsilon_pow = -9
    r = Romberg(main_func, epsilon_pow)
    r_solution = r.integral(-13, -5, 10)
    print(r_solution['final_array'][0][0])
    return render(req, 'romberg.html', context={
        'final_step': r_solution['final_step'],
        'r_kminus1_hi_values': r_solution['r_kminus1_hi_values'],
        'final_array': r_solution['final_array'],
        'h_step_holder': r_solution['h_step_holder']
    })
