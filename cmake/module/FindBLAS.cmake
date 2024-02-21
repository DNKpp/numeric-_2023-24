message(TRACE "Start adding OpenBLAS.")

CPMGetPackage(OpenBLAS)

if (OpenBLAS_ADDED)

	message(TRACE "Configure OpenBLAS.")

	add_library(BLAS SHARED IMPORTED)
	target_include_directories(
		BLAS
		INTERFACE
		"${OpenBLAS_SOURCE_DIR}/include"
	)

	target_link_directories(
		BLAS
		INTERFACE
		"${OpenBLAS_SOURCE_DIR}/lib"
	)

	#set(BLAS_LINKER_FLAGS ${OpenBLAS_LINKER_FLAGS})
	set(BLAS_LIBRARIES "${OpenBLAS_SOURCE_DIR}/lib/libopenblas.lib")
	set(BLAS_FOUND YES)

	add_library(BLAS::BLAS ALIAS BLAS)

endif()

message(TRACE "Finished adding OpenBLAS.")
