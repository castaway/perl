/*
 *    reentr.c
 *
 *    Copyright (c) 1997-2002, Larry Wall
 *
 *    You may distribute under the terms of either the GNU General Public
 *    License or the Artistic License, as specified in the README file.
 *
 *  !!!!!!!   DO NOT EDIT THIS FILE   !!!!!!!
 *  This file is built by reentrl.pl from data in reentr.pl.
 *
 * "Saruman," I said, standing away from him, "only one hand at a time can
 *  wield the One, and you know that well, so do not trouble to say we!"
 *
 */

#include "EXTERN.h"
#define PERL_IN_REENTR_C
#include "perl.h"
#include "reentr.h"

void
Perl_reentrant_size(pTHX) {
#ifdef USE_REENTRANT_API
#ifdef HAS_ASCTIME_R
	PL_reentrant_buffer->_asctime_size = 256; /* Make something up. */
#endif /* HAS_ASCTIME_R */
#ifdef HAS_CRYPT_R
#endif /* HAS_CRYPT_R */
#ifdef HAS_CTIME_R
	PL_reentrant_buffer->_ctime_size = 256; /* Make something up. */
#endif /* HAS_CTIME_R */
#ifdef HAS_DRAND48_R
#endif /* HAS_DRAND48_R */
#ifdef HAS_GETGRNAM_R
#   if defined(HAS_SYSCONF) && defined(_SC_GETGR_R_SIZE_MAX) && !defined(__GLIBC__)
	PL_reentrant_buffer->_getgrent_size = sysconf(_SC_GETGR_R_SIZE_MAX);
#   else
#       if defined(__osf__) && defined(__alpha) && defined(SIABUFSIZ)
	PL_reentrant_buffer->_getgrent_size = SIABUFSIZ;
#       else
#           ifdef __sgi
	PL_reentrant_buffer->_getgrent_size = BUFSIZ;
#           else
	PL_reentrant_buffer->_getgrent_size = 256;
#           endif
#       endif
#   endif 
#endif /* HAS_GETGRNAM_R */
#ifdef HAS_GETHOSTBYNAME_R
#if   !(GETHOSTBYNAME_R_PROTO == REENTRANT_PROTO_I_CSD)
	PL_reentrant_buffer->_gethostent_size = 2048; /* Any better ideas? */
#endif
#endif /* HAS_GETHOSTBYNAME_R */
#ifdef HAS_GETLOGIN_R
	PL_reentrant_buffer->_getlogin_size = 256; /* Make something up. */
#endif /* HAS_GETLOGIN_R */
#ifdef HAS_GETNETBYNAME_R
#if   !(GETNETBYNAME_R_PROTO == REENTRANT_PROTO_I_CSD)
	PL_reentrant_buffer->_getnetent_size = 2048; /* Any better ideas? */
#endif
#endif /* HAS_GETNETBYNAME_R */
#ifdef HAS_GETPROTOBYNAME_R
#if   !(GETPROTOBYNAME_R_PROTO == REENTRANT_PROTO_I_CSD)
	PL_reentrant_buffer->_getprotoent_size = 2048; /* Any better ideas? */
#endif
#endif /* HAS_GETPROTOBYNAME_R */
#ifdef HAS_GETPWNAM_R
#   if defined(HAS_SYSCONF) && defined(_SC_GETPW_R_SIZE_MAX) && !defined(__GLIBC__)
	PL_reentrant_buffer->_getpwent_size = sysconf(_SC_GETPW_R_SIZE_MAX);
#   else
#       if defined(__osf__) && defined(__alpha) && defined(SIABUFSIZ)
	PL_reentrant_buffer->_getpwent_size = SIABUFSIZ;
#       else
#           ifdef __sgi
	PL_reentrant_buffer->_getpwent_size = BUFSIZ;
#           else
	PL_reentrant_buffer->_getpwent_size = 256;
#           endif
#       endif
#   endif 
#endif /* HAS_GETPWNAM_R */
#ifdef HAS_GETSERVBYNAME_R
#if   !(GETSERVBYNAME_R_PROTO == REENTRANT_PROTO_I_CCSD)
	PL_reentrant_buffer->_getservent_size = 2048; /* Any better ideas? */
#endif
#endif /* HAS_GETSERVBYNAME_R */
#ifdef HAS_GETSPNAM_R
	PL_reentrant_buffer->_getspent_size = 1024;
#endif /* HAS_GETSPNAM_R */
#ifdef HAS_GMTIME_R
#endif /* HAS_GMTIME_R */
#ifdef HAS_LOCALTIME_R
#endif /* HAS_LOCALTIME_R */
#ifdef HAS_RANDOM_R
#endif /* HAS_RANDOM_R */
#ifdef HAS_READDIR_R
	/* This is the size Solaris recommends.
	 * (though we go static, should use pathconf() instead) */
	PL_reentrant_buffer->_readdir_size = sizeof(struct dirent) + MAXPATHLEN + 1;
#endif /* HAS_READDIR_R */
#ifdef HAS_READDIR64_R
	/* This is the size Solaris recommends.
	 * (though we go static, should use pathconf() instead) */
	PL_reentrant_buffer->_readdir64_size = sizeof(struct dirent64) + MAXPATHLEN + 1;
#endif /* HAS_READDIR64_R */
#ifdef HAS_SETLOCALE_R
	PL_reentrant_buffer->_setlocale_size = 256; /* Make something up. */
#endif /* HAS_SETLOCALE_R */
#ifdef HAS_STRERROR_R
	PL_reentrant_buffer->_strerror_size = 256; /* Make something up. */
#endif /* HAS_STRERROR_R */
#ifdef HAS_TTYNAME_R
	PL_reentrant_buffer->_ttyname_size = 256; /* Make something up. */
#endif /* HAS_TTYNAME_R */

#endif /* USE_REENTRANT_API */
}

void
Perl_reentrant_init(pTHX) {
#ifdef USE_REENTRANT_API
	New(31337, PL_reentrant_buffer, 1, REENTR);
	Perl_reentrant_size(aTHX);
#ifdef HAS_ASCTIME_R
	New(31338, PL_reentrant_buffer->_asctime_buffer, PL_reentrant_buffer->_asctime_size, char);
#endif /* HAS_ASCTIME_R */
#ifdef HAS_CRYPT_R
#ifdef __GLIBC__
	PL_reentrant_buffer->_crypt_struct.initialized = 0;
#endif
#endif /* HAS_CRYPT_R */
#ifdef HAS_CTIME_R
	New(31338, PL_reentrant_buffer->_ctime_buffer, PL_reentrant_buffer->_ctime_size, char);
#endif /* HAS_CTIME_R */
#ifdef HAS_DRAND48_R
#endif /* HAS_DRAND48_R */
#ifdef HAS_GETGRNAM_R
#   ifdef USE_GETGRENT_FPTR
	PL_reentrant_buffer->_getgrent_fptr = NULL;
#   endif
	New(31338, PL_reentrant_buffer->_getgrent_buffer, PL_reentrant_buffer->_getgrent_size, char);
#endif /* HAS_GETGRNAM_R */
#ifdef HAS_GETHOSTBYNAME_R
#if   !(GETHOSTBYNAME_R_PROTO == REENTRANT_PROTO_I_CSD)
	New(31338, PL_reentrant_buffer->_gethostent_buffer, PL_reentrant_buffer->_gethostent_size, char);
#endif
#endif /* HAS_GETHOSTBYNAME_R */
#ifdef HAS_GETLOGIN_R
	New(31338, PL_reentrant_buffer->_getlogin_buffer, PL_reentrant_buffer->_getlogin_size, char);
#endif /* HAS_GETLOGIN_R */
#ifdef HAS_GETNETBYNAME_R
#if   !(GETNETBYNAME_R_PROTO == REENTRANT_PROTO_I_CSD)
	New(31338, PL_reentrant_buffer->_getnetent_buffer, PL_reentrant_buffer->_getnetent_size, char);
#endif
#endif /* HAS_GETNETBYNAME_R */
#ifdef HAS_GETPROTOBYNAME_R
#if   !(GETPROTOBYNAME_R_PROTO == REENTRANT_PROTO_I_CSD)
	New(31338, PL_reentrant_buffer->_getprotoent_buffer, PL_reentrant_buffer->_getprotoent_size, char);
#endif
#endif /* HAS_GETPROTOBYNAME_R */
#ifdef HAS_GETPWNAM_R
#   ifdef USE_GETPWENT_FPTR
	PL_reentrant_buffer->_getpwent_fptr = NULL;
#   endif
	New(31338, PL_reentrant_buffer->_getpwent_buffer, PL_reentrant_buffer->_getpwent_size, char);
#endif /* HAS_GETPWNAM_R */
#ifdef HAS_GETSERVBYNAME_R
#if   !(GETSERVBYNAME_R_PROTO == REENTRANT_PROTO_I_CCSD)
	New(31338, PL_reentrant_buffer->_getservent_buffer, PL_reentrant_buffer->_getservent_size, char);
#endif
#endif /* HAS_GETSERVBYNAME_R */
#ifdef HAS_GETSPNAM_R
	New(31338, PL_reentrant_buffer->_getspent_buffer, PL_reentrant_buffer->_getspent_size, char);
#endif /* HAS_GETSPNAM_R */
#ifdef HAS_GMTIME_R
#endif /* HAS_GMTIME_R */
#ifdef HAS_LOCALTIME_R
#endif /* HAS_LOCALTIME_R */
#ifdef HAS_RANDOM_R
#endif /* HAS_RANDOM_R */
#ifdef HAS_READDIR_R
	PL_reentrant_buffer->_readdir_struct = (struct dirent*)safemalloc(PL_reentrant_buffer->_readdir_size);
#endif /* HAS_READDIR_R */
#ifdef HAS_READDIR64_R
	PL_reentrant_buffer->_readdir64_struct = (struct dirent64*)safemalloc(PL_reentrant_buffer->_readdir64_size);
#endif /* HAS_READDIR64_R */
#ifdef HAS_SETLOCALE_R
	New(31338, PL_reentrant_buffer->_setlocale_buffer, PL_reentrant_buffer->_setlocale_size, char);
#endif /* HAS_SETLOCALE_R */
#ifdef HAS_STRERROR_R
	New(31338, PL_reentrant_buffer->_strerror_buffer, PL_reentrant_buffer->_strerror_size, char);
#endif /* HAS_STRERROR_R */
#ifdef HAS_TTYNAME_R
	New(31338, PL_reentrant_buffer->_ttyname_buffer, PL_reentrant_buffer->_ttyname_size, char);
#endif /* HAS_TTYNAME_R */

#endif /* USE_REENTRANT_API */
}

void
Perl_reentrant_free(pTHX) {
#ifdef USE_REENTRANT_API
#ifdef HAS_ASCTIME_R
	Safefree(PL_reentrant_buffer->_asctime_buffer);
#endif /* HAS_ASCTIME_R */
#ifdef HAS_CRYPT_R
#endif /* HAS_CRYPT_R */
#ifdef HAS_CTIME_R
	Safefree(PL_reentrant_buffer->_ctime_buffer);
#endif /* HAS_CTIME_R */
#ifdef HAS_DRAND48_R
#endif /* HAS_DRAND48_R */
#ifdef HAS_GETGRNAM_R
	Safefree(PL_reentrant_buffer->_getgrent_buffer);
#endif /* HAS_GETGRNAM_R */
#ifdef HAS_GETHOSTBYNAME_R
#if   !(GETHOSTBYNAME_R_PROTO == REENTRANT_PROTO_I_CSD)
	Safefree(PL_reentrant_buffer->_gethostent_buffer);
#endif
#endif /* HAS_GETHOSTBYNAME_R */
#ifdef HAS_GETLOGIN_R
	Safefree(PL_reentrant_buffer->_getlogin_buffer);
#endif /* HAS_GETLOGIN_R */
#ifdef HAS_GETNETBYNAME_R
#if   !(GETNETBYNAME_R_PROTO == REENTRANT_PROTO_I_CSD)
	Safefree(PL_reentrant_buffer->_getnetent_buffer);
#endif
#endif /* HAS_GETNETBYNAME_R */
#ifdef HAS_GETPROTOBYNAME_R
#if   !(GETPROTOBYNAME_R_PROTO == REENTRANT_PROTO_I_CSD)
	Safefree(PL_reentrant_buffer->_getprotoent_buffer);
#endif
#endif /* HAS_GETPROTOBYNAME_R */
#ifdef HAS_GETPWNAM_R
	Safefree(PL_reentrant_buffer->_getpwent_buffer);
#endif /* HAS_GETPWNAM_R */
#ifdef HAS_GETSERVBYNAME_R
#if   !(GETSERVBYNAME_R_PROTO == REENTRANT_PROTO_I_CCSD)
	Safefree(PL_reentrant_buffer->_getservent_buffer);
#endif
#endif /* HAS_GETSERVBYNAME_R */
#ifdef HAS_GETSPNAM_R
	Safefree(PL_reentrant_buffer->_getspent_buffer);
#endif /* HAS_GETSPNAM_R */
#ifdef HAS_GMTIME_R
#endif /* HAS_GMTIME_R */
#ifdef HAS_LOCALTIME_R
#endif /* HAS_LOCALTIME_R */
#ifdef HAS_RANDOM_R
#endif /* HAS_RANDOM_R */
#ifdef HAS_READDIR_R
	Safefree(PL_reentrant_buffer->_readdir_struct);
#endif /* HAS_READDIR_R */
#ifdef HAS_READDIR64_R
	Safefree(PL_reentrant_buffer->_readdir64_struct);
#endif /* HAS_READDIR64_R */
#ifdef HAS_SETLOCALE_R
	Safefree(PL_reentrant_buffer->_setlocale_buffer);
#endif /* HAS_SETLOCALE_R */
#ifdef HAS_STRERROR_R
	Safefree(PL_reentrant_buffer->_strerror_buffer);
#endif /* HAS_STRERROR_R */
#ifdef HAS_TTYNAME_R
	Safefree(PL_reentrant_buffer->_ttyname_buffer);
#endif /* HAS_TTYNAME_R */

	Safefree(PL_reentrant_buffer);
#endif /* USE_REENTRANT_API */
}

void*
Perl_reentrant_retry(const char *f, ...)
{
    dTHX;
    void *retptr = NULL;
#ifdef USE_REENTRANT_API
    void *p0, *p1;
    size_t asize;
    int anint;
    va_list ap;

    va_start(ap, f);

#define REENTRANTHALFMAXSIZE 32768 /* The maximum may end up twice this. */

    switch (PL_op->op_type) {
#ifdef USE_GETHOSTENT_BUFFER
    case OP_GHBYADDR:
    case OP_GHBYNAME:
    case OP_GHOSTENT:
	{
	    if (PL_reentrant_buffer->_gethostent_size <= REENTRANTHALFMAXSIZE) {
		PL_reentrant_buffer->_gethostent_size *= 2;
		Renew(PL_reentrant_buffer->_gethostent_buffer,
		      PL_reentrant_buffer->_gethostent_size, char);
		switch (PL_op->op_type) {
	        case OP_GHBYADDR:
		    p0    = va_arg(ap, void *);
		    asize = va_arg(ap, size_t);
		    anint  = va_arg(ap, int);
		    retptr = gethostbyaddr(p0, asize, anint); break;
	        case OP_GHBYNAME:
		    p0 = va_arg(ap, void *);
		    retptr = gethostbyname(p0); break;
	        case OP_GHOSTENT:
		    retptr = gethostent(); break;
	        default:
		    break;
	        }
	    }
	}
	break;
#endif
#ifdef USE_GETGRENT_BUFFER
    case OP_GGRNAM:
    case OP_GGRGID:
    case OP_GGRENT:
	{
	    if (PL_reentrant_buffer->_getgrent_size <= REENTRANTHALFMAXSIZE) {
		Gid_t gid;
		PL_reentrant_buffer->_getgrent_size *= 2;
		Renew(PL_reentrant_buffer->_getgrent_buffer,
		      PL_reentrant_buffer->_getgrent_size, char);
		switch (PL_op->op_type) {
	        case OP_GGRNAM:
		    p0 = va_arg(ap, void *);
		    retptr = getgrnam(p0); break;
	        case OP_GGRGID:
		    gid = va_arg(ap, Gid_t);
		    retptr = getgrgid(gid); break;
	        case OP_GGRENT:
		    retptr = getgrent(); break;
	        default:
		    break;
	        }
	    }
	}
	break;
#endif
#ifdef USE_GETNETENT_BUFFER
    case OP_GNBYADDR:
    case OP_GNBYNAME:
    case OP_GNETENT:
	{
	    if (PL_reentrant_buffer->_getnetent_size <= REENTRANTHALFMAXSIZE) {
		Netdb_net_t net;
		PL_reentrant_buffer->_getnetent_size *= 2;
		Renew(PL_reentrant_buffer->_getnetent_buffer,
		      PL_reentrant_buffer->_getnetent_size, char);
		switch (PL_op->op_type) {
	        case OP_GNBYADDR:
		    net = va_arg(ap, Netdb_net_t);
		    anint = va_arg(ap, int);
		    retptr = getnetbyaddr(net, anint); break;
	        case OP_GNBYNAME:
		    p0 = va_arg(ap, void *);
		    retptr = getnetbyname(p0); break;
	        case OP_GNETENT:
		    retptr = getnetent(); break;
	        default:
		    break;
	        }
	    }
	}
	break;
#endif
#ifdef USE_GETPWENT_BUFFER
    case OP_GPWNAM:
    case OP_GPWUID:
    case OP_GPWENT:
	{
	    if (PL_reentrant_buffer->_getpwent_size <= REENTRANTHALFMAXSIZE) {
		Uid_t uid;
		PL_reentrant_buffer->_getpwent_size *= 2;
		Renew(PL_reentrant_buffer->_getpwent_buffer,
		      PL_reentrant_buffer->_getpwent_size, char);
		switch (PL_op->op_type) {
	        case OP_GPWNAM:
		    p0 = va_arg(ap, void *);
		    retptr = getpwnam(p0); break;
	        case OP_GPWUID:
		    uid = va_arg(ap, Uid_t);
		    retptr = getpwuid(uid); break;
	        case OP_GPWENT:
		    retptr = getpwent(); break;
	        default:
		    break;
	        }
	    }
	}
	break;
#endif
#ifdef USE_GETPROTOENT_BUFFER
    case OP_GPBYNAME:
    case OP_GPBYNUMBER:
    case OP_GPROTOENT:
	{
	    if (PL_reentrant_buffer->_getprotoent_size <= REENTRANTHALFMAXSIZE) {
		PL_reentrant_buffer->_getprotoent_size *= 2;
		Renew(PL_reentrant_buffer->_getprotoent_buffer,
		      PL_reentrant_buffer->_getprotoent_size, char);
		switch (PL_op->op_type) {
	        case OP_GPBYNAME:
		    p0 = va_arg(ap, void *);
		    retptr = getprotobyname(p0); break;
	        case OP_GPBYNUMBER:
		    anint = va_arg(ap, int);
		    retptr = getprotobynumber(anint); break;
	        case OP_GPROTOENT:
		    retptr = getprotoent(); break;
	        default:
		    break;
	        }
	    }
	}
	break;
#endif
#ifdef USE_GETSERVENT_BUFFER
    case OP_GSBYNAME:
    case OP_GSBYPORT:
    case OP_GSERVENT:
	{
	    if (PL_reentrant_buffer->_getservent_size <= REENTRANTHALFMAXSIZE) {
		PL_reentrant_buffer->_getservent_size *= 2;
		Renew(PL_reentrant_buffer->_getservent_buffer,
		      PL_reentrant_buffer->_getservent_size, char);
		switch (PL_op->op_type) {
	        case OP_GSBYNAME:
		    p0 = va_arg(ap, void *);
		    p1 = va_arg(ap, void *);
		    retptr = getservbyname(p0, p1); break;
	        case OP_GSBYPORT:
		    anint = va_arg(ap, int);
		    p0 = va_arg(ap, void *);
		    retptr = getservbyport(anint, p0); break;
	        case OP_GSERVENT:
		    retptr = getservent(); break;
	        default:
		    break;
	        }
	    }
	}
	break;
#endif
    default:
	/* Not known how to retry, so just fail. */
	break;
    }

    va_end(ap);
#endif
    return retptr;
}

