set(TARGET_NAME exercise50)

find_package(blaze REQUIRED)
CPMGetPackage(matplotplusplus)
CPMGetPackage(catch2)
CPMGetPackage(range-v3)
CPMGetPackage(fmt)

add_executable(
	${TARGET_NAME}
	"main.cpp"
)

target_link_libraries(
	${TARGET_NAME}
	PRIVATE
	Catch2::Catch2WithMain
	blaze::blaze
	range-v3::range-v3
	matplot
	fmt::fmt
)

target_include_directories(
	${TARGET_NAME}
	PRIVATE
	"../include"
)
