/**
* \file net.h
*
* \brief Deprecated header file that includes net_sockets.h
*
* \deprecated Superseded by mbedtls/net_sockets.h
*/
/*
*  Copyright The Mbed TLS Contributors
*  SPDX-License-Identifier: Apache-2.0
*
*  Licensed under the Apache License, Version 2.0 (the "License"); you may
*  not use this file except in compliance with the License.
*  You may obtain a copy of the License at
*
*  http://www.apache.org/licenses/LICENSE-2.0
*
*  Unless required by applicable law or agreed to in writing, software
*  distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
*  WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*  See the License for the specific language governing permissions and
*  limitations under the License.
*/
#if !defined(MBEDTLS_CONFIG_FILE)
#include "mbedtls/config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif

#if !defined(MBEDTLS_DEPRECATED_REMOVED)
#include "mbedtls/net_sockets.h"
#if defined(MBEDTLS_DEPRECATED_WARNING)
#warning "Deprecated header file: Superseded by mbedtls/net_sockets.h"
#endif /* MBEDTLS_DEPRECATED_WARNING */
#endif /* !MBEDTLS_DEPRECATED_REMOVED */
