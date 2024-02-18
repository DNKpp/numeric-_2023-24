#include <sciplot/sciplot.hpp>

#include "../PlotUtility.hpp"

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
	const auto ps = logspace(10, 0., 12., 11);

	sciplot::Plot2D positivePlot{};
	positivePlot.legend()
				.atOutsideTopLeft()
				.displayHorizontal();
	positivePlot.ytics().logscale(10);
	positivePlot.xtics().logscale(10);
	positivePlot.ylabel("Error");
	positivePlot.xlabel("p");
	positivePlot.drawCurve(
					ps,
					array_fun(
						ps,
						[](const double p)
						{
							return calc_rel_error(nst_stabil(p, 1).second, nst(p, 1).second);
						}))
				.label("Error of positive values.");

	sciplot::Plot2D negativePlot{};
	negativePlot.legend()
				.atOutsideTopLeft()
				.displayHorizontal();
	negativePlot.ytics().logscale(10);
	negativePlot.xtics().logscale(10);
	negativePlot.ylabel("Error");
	negativePlot.xlabel("-p");
	negativePlot.drawCurve(
					ps,
					array_fun(
						-ps,
						[](const double p)
						{
							return calc_rel_error(nst_stabil(p, 1).first, nst(p, 1).first);
						}))
				.label("Error of negative values.");

	sciplot::Figure figure{
		{positivePlot},
		{negativePlot}
	};
	figure.palette("dark2");
	sciplot::Canvas canvas{{figure}};
	canvas.size(1200, 600);
	canvas.show();
}
