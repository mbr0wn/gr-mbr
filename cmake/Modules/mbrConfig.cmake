INCLUDE(FindPkgConfig)
PKG_CHECK_MODULES(PC_MBR mbr)

FIND_PATH(
    MBR_INCLUDE_DIRS
    NAMES mbr/api.h
    HINTS $ENV{MBR_DIR}/include
        ${PC_MBR_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    MBR_LIBRARIES
    NAMES gnuradio-mbr
    HINTS $ENV{MBR_DIR}/lib
        ${PC_MBR_LIBDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/lib64
          /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
)

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(MBR DEFAULT_MSG MBR_LIBRARIES MBR_INCLUDE_DIRS)
MARK_AS_ADVANCED(MBR_LIBRARIES MBR_INCLUDE_DIRS)

