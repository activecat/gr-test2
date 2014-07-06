INCLUDE(FindPkgConfig)
PKG_CHECK_MODULES(PC_TEST1 test1)

FIND_PATH(
    TEST1_INCLUDE_DIRS
    NAMES test1/api.h
    HINTS $ENV{TEST1_DIR}/include
        ${PC_TEST1_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    TEST1_LIBRARIES
    NAMES gnuradio-test1
    HINTS $ENV{TEST1_DIR}/lib
        ${PC_TEST1_LIBDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/lib64
          /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
)

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(TEST1 DEFAULT_MSG TEST1_LIBRARIES TEST1_INCLUDE_DIRS)
MARK_AS_ADVANCED(TEST1_LIBRARIES TEST1_INCLUDE_DIRS)

