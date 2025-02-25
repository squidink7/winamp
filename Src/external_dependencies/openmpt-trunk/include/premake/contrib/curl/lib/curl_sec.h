					#ifndef HEADER_CURL_SECURITY_H
					#define HEADER_CURL_SECURITY_H
					/***************************************************************************
                    *                                  _   _ ____  _
                    *  Project                     ___| | | |  _ \| |
                    *                             / __| | | | |_) | |
                    *                            | (__| |_| |  _ <| |___
                    *                             \___|\___/|_| \_\_____|
                    *
                    * Copyright (C) 1998 - 2016, Daniel Stenberg, <daniel@haxx.se>, et al.
                    *
                    * This software is licensed as described in the file COPYING, which
                    * you should have received as part of this distribution. The terms
                    * are also available at https://curl.haxx.se/docs/copyright.html.
                    *
                    * You may opt to use, copy, modify, merge, publish, distribute and/or sell
                    * copies of the Software, and permit persons to whom the Software is
                    * furnished to do so, under the terms of the COPYING file.
                    *
                    * This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY
                    * KIND, either express or implied.
                    *
                    ***************************************************************************/
					
					struct Curl_sec_client_mech {
                    const char *name;
                    size_t size;
                    int (*init)(void *);
                    int (*auth)(void *, struct connectdata *);
                    void (*end)(void *);
                    int (*check_prot)(void *, int);
                    int (*overhead)(void *, int, int);
                    int (*encode)(void *, const void *, int, int, void **);
                    int (*decode)(void *, void *, int, int, struct connectdata *);
					};
					
					#define AUTH_OK         0
					#define AUTH_CONTINUE   1
					#define AUTH_ERROR      2
					
					#ifdef HAVE_GSSAPI
					int Curl_sec_read_msg(struct connectdata *conn, char *,
enum protection_level);
					void Curl_sec_end(struct connectdata *);
					CURLcode Curl_sec_login(struct connectdata *);
					int Curl_sec_request_prot(struct connectdata *conn, const char *level);
					
					extern struct Curl_sec_client_mech Curl_krb5_client_mech;
					#endif
					
					#endif /* HEADER_CURL_SECURITY_H */
					