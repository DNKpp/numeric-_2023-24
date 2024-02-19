CPMGetPackage(matplotplusplus)

add_executable(
	exercise04
	"main.cpp"
)

target_link_libraries(
	exercise04
	PRIVATE
	matplot
)
