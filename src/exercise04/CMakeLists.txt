CPMGetPackage(sciplot)

add_executable(
	exercise04 WIN32
	"main.cpp"
)

target_link_libraries(
	exercise04
	PRIVATE
	sciplot
)

target_link_options(
	exercise04
	PRIVATE
	$<$<CXX_COMPILER_ID:MSVC>:/ENTRY:mainCRTStartup>
)
