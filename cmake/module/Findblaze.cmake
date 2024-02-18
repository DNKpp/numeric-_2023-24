message(TRACE "Start adding blaze.")

CPMGetPackage(xsimd)
CPMGetPackage(blaze)
if (blaze_ADDED)

	message(TRACE "Configure blaze.")

	include("${blaze_SOURCE_DIR}/cmake/Blaze_Import.cmake")
	Blaze_Import(
		REQUIRED
		#DEBUG
		BLAS OFF
		LAPACK OFF
		THREADING C++11
		CACHE_SIZE auto
		STORAGE_ORDER rowMajor
		VECTORIZATION ON
		FUNCTION_TRACES OFF
	)

	add_library(blaze::blaze ALIAS Blaze)

endif()

message(TRACE "Finished adding blaze.")
