set(system_supported_qt_versions "Auto" 5 6)

if (NOT DEFINED SYSTEM_QT_VERSION)
  set(SYSTEM_QT_VERSION "Auto" CACHE
    STRING "Expected Qt major version. Valid values are Auto, 5, 6.")
  set_property(CACHE SYSTEM_QT_VERSION PROPERTY STRINGS "${system_supported_qt_versions}")
endif ()

if (NOT SYSTEM_QT_VERSION IN_LIST system_supported_qt_versions)
  string(REPLACE ";" "\", \"" system_supported_qt_versions_string "${system_supported_qt_versions}")
  message(FATAL_ERROR
    "Supported Qt versions are \"${system_supported_qt_versions_string}\". "
    "But `SYSTEM_QT_VERSION` is set to \"${SYSTEM_QT_VERSION}\".")
endif ()

set(SYSTEM_QT_MAJOR_VERSION 6)
if (SYSTEM_QT_VERSION STREQUAL "Auto")
  find_package(Qt${SYSTEM_QT_MAJOR_VERSION} QUIET COMPONENTS Core)
  set(_system_qt_version 6)
  if (NOT Qt6_FOUND)
    find_package(Qt5 QUIET COMPONENTS Core)
    if (NOT Qt5_FOUND)
      message(FATAL_ERROR
        "Could not find a valid Qt installation.")
    endif ()
    set(_system_qt_version 5)
  endif ()
else ()
  set(_system_qt_version "${SYSTEM_QT_VERSION}")
endif ()

set(SYSTEM_QT_MAJOR_VERSION "${_system_qt_version}")
message(STATUS "Qt Version: ${SYSTEM_QT_MAJOR_VERSION}")
