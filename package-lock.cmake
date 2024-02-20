
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
	glad
	NAME glad
	GIT_TAG v0.1.36
	GITHUB_REPOSITORY Dav1dde/glad
	EXCLUDE_FROM_ALL YES
)

CPMDeclarePackage(
	matplotplusplus
	NAME matplotplusplus
	GIT_TAG v1.2.1
	GITHUB_REPOSITORY alandefreitas/matplotplusplus
	EXCLUDE_FROM_ALL YES
	OPTIONS
		"MATPLOTPP_BUILD_EXPERIMENTAL_OPENGL_BACKEND ON"
		"MATPLOTPP_BUILD_TESTS OFF"
		"MATPLOTPP_BUILD_EXAMPLES OFF"
)

CPMDeclarePackage(
	fmt
	NAME fmt
	GIT_TAG 10.2.1
	GITHUB_REPOSITORY fmtlib/fmt
	EXCLUDE_FROM_ALL YES
)
#[[
CPMDeclarePackage(
	OpenBLAS
	NAME OpenBLAS
	GIT_TAG v0.3.26
	GITHUB_REPOSITORY OpenMathLib/OpenBLAS
	EXCLUDE_FROM_ALL YES
)
#]]

CPMDeclarePackage(
	OpenBLAS
	NAME OpenBLAS
	URL "https://github.com/OpenMathLib/OpenBLAS/releases/download/v0.3.26/OpenBLAS-0.3.26-x64-64.zip"
	EXCLUDE_FROM_ALL YES
)

CPMDeclarePackage(
	FlexiBLAS
	NAME FlexiBLAS
	GIT_TAG v3.4.1
	GITHUB_REPOSITORY mpimd-csc/flexiblas
	EXCLUDE_FROM_ALL YES
	OPTIONS
		"LAPACK OFF"
)

CPMDeclarePackage(
	BLIS
	NAME BLIS
	GIT_TAG 0.9.0
	GITHUB_REPOSITORY flame/blis
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
	GIT_TAG 12.1.1
	GITHUB_REPOSITORY xtensor-stack/xsimd
	EXCLUDE_FROM_ALL YES
)

CPMDeclarePackage(
	catch2
	NAME catch2
	GIT_TAG v3.5.2
	GITHUB_REPOSITORY catchorg/Catch2
	EXCLUDE_FROM_ALL YES
)
