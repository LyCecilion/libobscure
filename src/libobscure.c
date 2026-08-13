/*
 * libobscure.c — LD_PRELOAD library
 *
 * Fixes the bug where Linux error messages were too readable:
 * replaces every strerror/perror output with the modern
 * commercial-OS style
 *   "Something went wrong. Error code: 0x8007xxxx. Ask your system administrator."
 *
 * Build: make
 * Use: LD_PRELOAD=$PWD/libobscure.so <any program>
 */

#define _GNU_SOURCE
#include <errno.h>
#include <netdb.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static _Thread_local char obscure_buf[128];

/* 0x80070000 | errno is exactly the Windows HRESULT_FROM_WIN32 definition,
 * so Linux errno -> "Windows error code" is a mathematically sound 1:1 mapping:
 * EACCES(13) -> 0x8007000D, ENOENT(2) -> 0x80070002. */
static void obscure_error(int errnum, char *buf, size_t len)
{
    snprintf(buf, len,
             "Something went wrong. Error code: 0x%08X. "
             "Ask your system administrator.",
             0x80070000U | (unsigned)errnum);
}

/* glibc's perror goes through __strerror_r internally rather than the
 * public strerror, so it must be intercepted separately; we build the
 * output ourselves instead of calling the real perror. */
void perror(const char *s)
{
    obscure_error(errno, obscure_buf, sizeof obscure_buf);
    if (s && *s)
        fprintf(stderr, "%s: %s\n", s, obscure_buf);
    else
        fprintf(stderr, "%s\n", obscure_buf);
}

char *strerror(int errnum)
{
    obscure_error(errnum, obscure_buf, sizeof obscure_buf);
    return obscure_buf;
}

/* GNU variant (returns char*). Callers of the POSIX variant (returns int)
 * get the pointer's low bits as a fake int — fragmented error styles,
 * very corporate. */
char *strerror_r(int errnum, char *buf, size_t buflen)
{
    obscure_error(errnum, buf, buflen);
    return buf;
}

/* Network errors: 0x8007274D is the genuine WSAECONNREFUSED */
const char *gai_strerror(int ecode)
{
    (void)ecode;
    return "Something went wrong. Error code: 0x8007274D. "
           "Ask your system administrator.";
}

/* coreutils (ls/cp/mv/rm…) go through glibc's error(), and glibc prints
 * errno via __strerror_r internally without going through the public
 * strerror, so error() must be intercepted too. grep/find/tar's error is a
 * U symbol (linked against glibc), so the prefix is filled in with
 * program_invocation_short_name. */
static void obscure_error_prefix(void)
{
    if (program_invocation_short_name && *program_invocation_short_name)
        fprintf(stderr, "%s: ", program_invocation_short_name);
}

static void obscure_verror(int status, int errnum, const char *filename, unsigned int line_number,
                           const char *format, va_list ap)
{
    fflush(stdout);
    obscure_error_prefix();
    if (filename) fprintf(stderr, "%s:%u: ", filename, line_number);
    vfprintf(stderr, format, ap);
    if (errnum)
    {
        char buf[sizeof obscure_buf];
        obscure_error(errnum, buf, sizeof buf);
        fprintf(stderr, ": %s\n", buf);
    }
    else
    {
        fputc('\n', stderr);
    }
    if (status) exit(status);
}

void error(int status, int errnum, const char *format, ...)
{
    va_list ap;
    va_start(ap, format);
    obscure_verror(status, errnum, NULL, 0, format, ap);
    va_end(ap);
}

void error_at_line(int status, int errnum, const char *filename, unsigned int line_number,
                   const char *format, ...)
{
    va_list ap;
    va_start(ap, format);
    obscure_verror(status, errnum, filename, line_number, format, ap);
    va_end(ap);
}
