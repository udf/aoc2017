#include <complex>
#include <math.h>
#include <utility> 

// source: https://web.archive.org/web/20141202041502/https://danpearcymaths.wordpress.com/2012/09/30/infinity-programming-in-geogebra-and-failing-miserably/
std::pair<const int, const int> ulam_coord(const uint num) {
    using namespace std::complex_literals;

    const uint n = num - 1;
    const double p = floor(sqrt(4*n + 1));
    const double q = n - floor((p*p)/4);
    const std::complex<double> z = q * std::pow(1i, p) + (floor((p + 2) / 4) - floor((p + 1) / 4) * 1i) * std::pow(1i, p-1);

    return std::make_pair(round(z.real()), round(z.imag()));
}

std::pair<const int, const int> spiral_coord(const uint num) {
    auto[x, y] = ulam_coord(num);
    return std::make_pair(y, -x);
}
