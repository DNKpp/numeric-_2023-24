find_package(blaze REQUIRED)
CPMGetPackage(matplotplusplus)
CPMGetPackage(catch2)
CPMGetPackage(range-v3)

add_executable(
	exercise10
	"main.cpp"
)

target_link_libraries(
	exercise10
	PRIVATE
	Catch2::Catch2WithMain
	blaze::blaze
	range-v3::range-v3
	matplot
)

target_include_directories(
	exercise10
	PRIVATE
	"../include"
)
