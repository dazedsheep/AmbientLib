# Install script for directory: C:/Users/Mauke/Documents/muhkuh/ambientLib/npapi_activex_plugin/firebreath-1.5.2

# Set the install prefix
IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX "C:/Program Files/FireBreath")
ENDIF(NOT DEFINED CMAKE_INSTALL_PREFIX)
STRING(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
IF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  IF(BUILD_TYPE)
    STRING(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  ELSE(BUILD_TYPE)
    SET(CMAKE_INSTALL_CONFIG_NAME "Release")
  ENDIF(BUILD_TYPE)
  MESSAGE(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
ENDIF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)

# Set the component getting installed.
IF(NOT CMAKE_INSTALL_COMPONENT)
  IF(COMPONENT)
    MESSAGE(STATUS "Install component: \"${COMPONENT}\"")
    SET(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  ELSE(COMPONENT)
    SET(CMAKE_INSTALL_COMPONENT)
  ENDIF(COMPONENT)
ENDIF(NOT CMAKE_INSTALL_COMPONENT)

IF(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  INCLUDE("C:/Users/Mauke/Documents/muhkuh/ambientLib/npapi_activex_plugin/firebreath-1.5.2/cmake_common/cmake_install.cmake")
  INCLUDE("C:/Users/Mauke/Documents/muhkuh/ambientLib/npapi_activex_plugin/firebreath-1.5.2/boost/libs/thread/cmake_install.cmake")
  INCLUDE("C:/Users/Mauke/Documents/muhkuh/ambientLib/npapi_activex_plugin/firebreath-1.5.2/boost/libs/system/cmake_install.cmake")
  INCLUDE("C:/Users/Mauke/Documents/muhkuh/ambientLib/npapi_activex_plugin/firebreath-1.5.2/ScriptingCore/cmake_install.cmake")
  INCLUDE("C:/Users/Mauke/Documents/muhkuh/ambientLib/npapi_activex_plugin/firebreath-1.5.2/PluginCore/cmake_install.cmake")
  INCLUDE("C:/Users/Mauke/Documents/muhkuh/ambientLib/npapi_activex_plugin/firebreath-1.5.2/NpapiCore/cmake_install.cmake")
  INCLUDE("C:/Users/Mauke/Documents/muhkuh/ambientLib/npapi_activex_plugin/firebreath-1.5.2/ActiveXCore/cmake_install.cmake")
  INCLUDE("C:/Users/Mauke/Documents/muhkuh/ambientLib/npapi_activex_plugin/firebreath-1.5.2/projects/ambient/PluginAuto/cmake_install.cmake")
  INCLUDE("C:/Users/Mauke/Documents/muhkuh/ambientLib/npapi_activex_plugin/firebreath-1.5.2/projects/ambient/cmake_install.cmake")
  INCLUDE("C:/Users/Mauke/Documents/muhkuh/ambientLib/npapi_activex_plugin/firebreath-1.5.2/unittest-cpp/UnitTest++/cmake_install.cmake")
  INCLUDE("C:/Users/Mauke/Documents/muhkuh/ambientLib/npapi_activex_plugin/firebreath-1.5.2/NPAPIHost/cmake_install.cmake")
  INCLUDE("C:/Users/Mauke/Documents/muhkuh/ambientLib/npapi_activex_plugin/firebreath-1.5.2/ScriptingCoreTest/cmake_install.cmake")
  INCLUDE("C:/Users/Mauke/Documents/muhkuh/ambientLib/npapi_activex_plugin/firebreath-1.5.2/ActiveXCoreTest/cmake_install.cmake")

ENDIF(NOT CMAKE_INSTALL_LOCAL_ONLY)

IF(CMAKE_INSTALL_COMPONENT)
  SET(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
ELSE(CMAKE_INSTALL_COMPONENT)
  SET(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
ENDIF(CMAKE_INSTALL_COMPONENT)

FILE(WRITE "C:/Users/Mauke/Documents/muhkuh/ambientLib/npapi_activex_plugin/firebreath-1.5.2/${CMAKE_INSTALL_MANIFEST}" "")
FOREACH(file ${CMAKE_INSTALL_MANIFEST_FILES})
  FILE(APPEND "C:/Users/Mauke/Documents/muhkuh/ambientLib/npapi_activex_plugin/firebreath-1.5.2/${CMAKE_INSTALL_MANIFEST}" "${file}\n")
ENDFOREACH(file)
