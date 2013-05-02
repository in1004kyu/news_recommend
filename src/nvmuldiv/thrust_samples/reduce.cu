#include <thrust/version.h>
#include <iostream>
#include <thrust/device_vector.h>

int main(void)
{
	int major = THRUST_MAJOR_VERSION;
	int minor = THRUST_MINOR_VERSION;

	std::cout << "Thrust v" << major << "." << minor << std::endl;

// put three 1s in a device_vector
	thrust::device_vector<int> vec(5,0);
	vec[1] = 1;
	vec[3] = 1;
	vec[4] = 1;

	int sum = thrust::reduce(vec.begin(), vec.end(), (int) 0, thrust::plus<int>());

	std::cout << "Sum:" << sum << std::endl;

// Multiply
	thrust::device_vector<float> d1(5, 0);
	d1[0] = 1.2;
	d1[1] = 2.3;
	d1[2] = 3.4;
	d1[3] = 4.5;
	d1[4] = 5.6;

	float mul = thrust::reduce(d1.begin(), d1.end(), (float) 1, thrust::multiplies<float>());

	std::cout << "Mul:" << mul << std::endl;
	return 0;
}
