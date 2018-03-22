#ifndef CONVERT_H
#define CONVERT_H

#include <cstdio>

int CodeConvert(const char *from_charset, const char *to_charset, char *inbuf, size_t inlen, char *outbuf, size_t outlen);

#endif
