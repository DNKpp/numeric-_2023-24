
CPMDeclarePackage(
	range-v3
	name range-v3
	GIT_TAG 0.12.0
	GITHUB_REPOSITORY ericniebler/range-v3
	EXCLUDE_FROM_ALL YES
	OPTIONS
		"RANGES_BUILD_CALENDAR_EXAMPLE OFF"
)

CPMDeclarePackage(
	sciplot
	NAME sciplot
	GIT_TAG v0.3.1
	GITHUB_REPOSITORY sciplot/sciplot
	EXCLUDE_FROM_ALL YES
	OPTIONS
		"SCIPLOT_BUILD_EXAMPLES OFF"
		"SCIPLOT_BUILD_TESTS OFF"
		"SCIPLOT_BUILD_DOCS OFF"
)

CPMDeclarePackage(
	matplotplusplus
	NAME matplotplusplus
	GIT_TAG v1.2.0
	GITHUB_REPOSITORY alandefreitas/matplotplusplus
	EXCLUDE_FROM_ALL YES
)

CPMDeclarePackage(
	fmt
	NAME fmt
	GIT_TAG 10.1.1
	GITHUB_REPOSITORY fmtlib/fmt
	EXCLUDE_FROM_ALL YES
)

CPMDeclarePackage(
	blaze
	NAME blaze
	GIT_TAG v3.8.2
	BITBUCKET_REPOSITORY blaze-lib/blaze
	DOWNLOAD_ONLY YES
	EXCLUDE_FROM_ALL YES
)

CPMDeclarePackage(
	xsimd
	NAME xsimd
	GIT_TAG 11.2.0
	GITHUB_REPOSITORY xtensor-stack/xsimd
	EXCLUDE_FROM_ALL YES
)
