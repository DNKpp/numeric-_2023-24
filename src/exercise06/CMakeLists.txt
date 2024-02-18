find_package(blaze REQUIRED)
CPMGetPackage(sciplot)
CPMGetPackage(catch2)
CPMGetPackage(range-v3)

add_executable(
	exercise06
	"main.cpp"
)

target_link_libraries(
	exercise06
	PRIVATE
	Catch2::Catch2WithMain
	sciplot
	blaze::blaze
	range-v3::range-v3
)

target_include_directories(
	exercise06
	PRIVATE
	"../include"
)
