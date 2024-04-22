#include <iostream>
#include <random>

#include "ThreadPool.h"

random_device rd;
mt19937 mt(rd());
uniform_int_distribution<int> dist(-1000, 1000);
auto rnd = bind(dist, mt);

void simulate_hard_computation()
{
    this_thread::sleep_for(chrono::milliseconds(2000 + rnd()));
}

// Simple function that adds multiplies two numbers and prints the result
void multiply(const int a, const int b)
{
    simulate_hard_computation();
    cout << a << " * " << b << " = " << a * b << endl;
}

// Same as before but now we have an output parameter
void multiply_output(int &out, const int a, const int b)
{
    simulate_hard_computation();
    out = a * b;
    cout << a << " * " << b << " = " << out << endl;
}

// Same as before but now we have an output parameter
int multiply_return(const int a, const int b)
{
    simulate_hard_computation();
    const int res = a * b;
    cout << a << " * " << b << " = " << res << endl;
    return res;
}

int main()
{
    // Create pool with 3 threads
    ThreadPool pool(3);

    // Initialize pool
    pool.init();

    // Submit (partial) multiplication table
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 10; ++j)
            pool.submit(multiply, i, j);

    // Submit function with output parameter passed by ref
    int output_ref;
    auto future1 = pool.submit(multiply_output, ref(output_ref), 5, 6);
    future1.get(); // Wait for multiplication output to finish
    cout << "Last operation result is equals to " << output_ref << endl;

    // Submit function with return parameter
    auto future2 = pool.submit(multiply_return, 5, 3);
    int res = future2.get(); // Wait for multiplication output to finish
    cout << "Last operation result is equals to " << res << endl;

    pool.shutdown();

    return 0;
}