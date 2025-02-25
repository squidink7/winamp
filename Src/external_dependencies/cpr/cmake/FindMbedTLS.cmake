	# Source: https://github.com/curl/curl/blob/curl-7_82_0/CMake/FindMbedTLS.cmake
	find_path(MBEDTLS_INCLUDE_DIRS mbedtls/ssl.h)
	
	find_library(MBEDTLS_LIBRARY mbedtls)
	find_library(MBEDX509_LIBRARY mbedx509)
	find_library(MBEDCRYPTO_LIBRARY mbedcrypto)
	
	set(MBEDTLS_LIBRARIES "${MBEDTLS_LIBRARY}" "${MBEDX509_LIBRARY}" "${MBEDCRYPTO_LIBRARY}")
	
	include(FindPackageHandleStandardArgs)
	find_package_handle_standard_args(MbedTLS DEFAULT_MSG
MBEDTLS_INCLUDE_DIRS MBEDTLS_LIBRARY MBEDX509_LIBRARY MBEDCRYPTO_LIBRARY)
	
	mark_as_advanced(MBEDTLS_INCLUDE_DIRS MBEDTLS_LIBRARY MBEDX509_LIBRARY MBEDCRYPTO_LIBRARY)
	