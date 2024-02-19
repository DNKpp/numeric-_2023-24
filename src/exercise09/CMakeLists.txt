find_package(blaze REQUIRED)
CPMGetPackage(catch2)
CPMGetPackage(range-v3)

add_executable(
	exercise09
	"main.cpp"
)

target_link_libraries(
	exercise09
	PRIVATE
	Catch2::Catch2WithMain
	blaze::blaze
	range-v3::range-v3
)

target_include_directories(
	exercise09
	PRIVATE
	"../include"
)
