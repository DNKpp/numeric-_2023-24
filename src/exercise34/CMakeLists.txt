find_package(blaze REQUIRED)
CPMGetPackage(matplotplusplus)
CPMGetPackage(catch2)
CPMGetPackage(range-v3)
CPMGetPackage(fmt)

add_executable(
	exercise34
	"main.cpp"
)

target_link_libraries(
	exercise34
	PRIVATE
	Catch2::Catch2WithMain
	blaze::blaze
	range-v3::range-v3
	matplot
	fmt::fmt
)

target_include_directories(
	exercise34
	PRIVATE
	"../include"
)
