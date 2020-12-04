AC_PREREQ([2.69])
AC_INIT([buf], [0.0.1], [mochalov.n@ya.ru])
AC_CONFIG_SRCDIR([buf.c])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC
AM_INIT_AUTOMAKE

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([stddef.h stdlib.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T
AC_CHECK_TYPES([ptrdiff_t])

# Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_REALLOC

AC_CONFIG_FILES([Makefile])


CURR_DATE=`date +%F`
FILES=$(ls | grep -E '\.(h|c)$')
MARK="AC_PACKAGE_NAME, AC_PACKAGE_VERSION: $CURR_DATE"

for file in $FILES
do
    HEADER=$(head -n 1 $file | sed '/COMMENT::/! s/^.*$/\/* COMMENT::\n&/g; 1s/COMMENT::.*/COMMENT:: '"$MARK"' *\//')
    sed -i '1!b; /COMMENT::/d' $file
    sed -i '1 i\'"$HEADER" $file
done


AC_OUTPUT
