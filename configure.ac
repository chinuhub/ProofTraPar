#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([ProofTraPar], [1.2], [chinu.pandey@gmail.com])
AM_INIT_AUTOMAKE(ProofTraPar, 1.2)
AC_OUTPUT(Makefile)
#AC_CONFIG_SRCDIR([extlib/libfaudes-2_26g/include/cfl_regular.h])
#AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC

# Checks for libraries.
# FIXME: Replace `main' with a function in `-lpthread':
AC_CHECK_LIB([pthread], [main])
# FIXME: Replace `main' with a function in `-lz3':
#AC_CHECK_LIB([z3], [main])

# Checks for header files.
AC_FUNC_ALLOCA
AC_CHECK_HEADERS([argz.h arpa/inet.h fcntl.h fenv.h float.h inttypes.h libintl.h limits.h locale.h malloc.h memory.h netdb.h netinet/in.h stddef.h stdint.h stdlib.h string.h strings.h sys/file.h sys/ioctl.h sys/param.h sys/socket.h sys/time.h termios.h unistd.h wchar.h wctype.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_TYPE_UID_T
AC_C_INLINE
AC_TYPE_INT16_T
AC_TYPE_INT32_T
AC_TYPE_INT64_T
AC_TYPE_INT8_T
AC_TYPE_MODE_T
AC_TYPE_OFF_T
AC_TYPE_PID_T
AC_C_RESTRICT
AC_TYPE_SIZE_T
AC_TYPE_SSIZE_T
AC_TYPE_UINT16_T
AC_TYPE_UINT32_T
AC_TYPE_UINT64_T
AC_TYPE_UINT8_T
AC_CHECK_TYPES([ptrdiff_t])

# Checks for library functions.
AC_FUNC_ERROR_AT_LINE
AC_FUNC_FORK
AC_FUNC_LSTAT_FOLLOWS_SLASHED_SYMLINK
AC_FUNC_MALLOC
AC_FUNC_MKTIME
AC_FUNC_MMAP
AC_FUNC_REALLOC
AC_FUNC_STRERROR_R
AC_FUNC_STRTOD
AC_CHECK_FUNCS([atexit btowc clock_gettime fesetround floor ftime ftruncate getcwd gethostname getpagesize gettimeofday iswprint localtime_r mblen memchr memmove memset mkdir modf munmap pathconf pow putenv rint select setenv setlocale socket sqrt stpcpy strchr strdup strerror strndup strrchr strstr strtol strtoul])

AC_CONFIG_FILES([ src/Makefile])
AC_OUTPUT
