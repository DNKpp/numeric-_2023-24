#include <matplot/matplot.h>

#include <cmath>
#include <concepts>

[[nodiscard]]
inline std::pair<double, double> nst(const double p, const double q)
{
	const auto r = std::sqrt(p * p + q);
	return {
		-p - r,
		-p + r
	};
}

[[nodiscard]]
inline std::pair<double, double> nst_stabil(const double p, const double q)
{
	const auto r = std::sqrt(p * p + q);
	if (0. <= p)
	{
		return {
			-(p + r),
			q / (p + r)
		};
	}

	return {
		q / (p - r),
		-(p - r)
	};
}

[[nodiscard]]
inline double calc_rel_error(const double x, const double approx)
{
	return std::abs(x - approx) / std::abs(x);
}

int main()
{
	const auto ps = matplot::logspace(0., 12., 120);

	matplot::legend()->location(matplot::legend::general_alignment::topleft);
	matplot::ylabel("Relative Error");
	matplot::xlabel("p");
	matplot::tiledlayout(2, 1);

	loglog(
			matplot::nexttile(),
			ps,
			matplot::transform(
				ps,
				[](const double p) { return calc_rel_error(nst_stabil(p, 1).second, nst(p, 1).second); }))
		->display_name("Relative error of 10^p.");

	loglog(
			matplot::nexttile(),
			ps,
			matplot::transform(
				ps,
				[](const double p) { return calc_rel_error(nst_stabil(-p, 1).first, nst(-p, 1).first); }))
		->display_name("Relative error of -10^p.");

	matplot::show();
}
