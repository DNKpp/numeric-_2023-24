message(TRACE "Start adding blaze.")

CPMGetPackage(xsimd)
CPMGetPackage(blaze)
if (blaze_ADDED)

	message(TRACE "Configure blaze.")

	find_package(BLAS REQUIRED)

	include("${blaze_SOURCE_DIR}/cmake/Blaze_Import.cmake")
	Blaze_Import(
		REQUIRED
		#DEBUG
		BLAS ON
		LAPACK OFF
		THREADING C++11
		CACHE_SIZE auto
		STORAGE_ORDER rowMajor
		VECTORIZATION ON
		FUNCTION_TRACES OFF
		BLAS_INCLUDE "<${OpenBLAS_SOURCE_DIR}/include/cblas.h>"
	)

	add_library(blaze::blaze ALIAS Blaze)

endif()

message(TRACE "Finished adding blaze.")
