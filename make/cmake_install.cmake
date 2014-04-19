# Install script for directory: /usr/games/cocos2d-x-3.0beta2/myGameSpace/towerDefend

# Set the install prefix
IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX "/usr/local")
ENDIF(NOT DEFINED CMAKE_INSTALL_PREFIX)
STRING(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
IF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  IF(BUILD_TYPE)
    STRING(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  ELSE(BUILD_TYPE)
    SET(CMAKE_INSTALL_CONFIG_NAME "DEBUG")
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

# Install shared libraries without execute permission?
IF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  SET(CMAKE_INSTALL_SO_NO_EXE "1")
ENDIF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)

IF(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  INCLUDE("/usr/games/cocos2d-x-3.0beta2/myGameSpace/towerDefend/make/cocos2d/cocos/math/kazmath/cmake_install.cmake")
  INCLUDE("/usr/games/cocos2d-x-3.0beta2/myGameSpace/towerDefend/make/cocos2d/external/chipmunk/src/cmake_install.cmake")
  INCLUDE("/usr/games/cocos2d-x-3.0beta2/myGameSpace/towerDefend/make/cocos2d/external/Box2D/cmake_install.cmake")
  INCLUDE("/usr/games/cocos2d-x-3.0beta2/myGameSpace/towerDefend/make/cocos2d/external/unzip/cmake_install.cmake")
  INCLUDE("/usr/games/cocos2d-x-3.0beta2/myGameSpace/towerDefend/make/cocos2d/external/tinyxml2/cmake_install.cmake")
  INCLUDE("/usr/games/cocos2d-x-3.0beta2/myGameSpace/towerDefend/make/cocos2d/cocos/audio/cmake_install.cmake")
  INCLUDE("/usr/games/cocos2d-x-3.0beta2/myGameSpace/towerDefend/make/cocos2d/cocos/base/cmake_install.cmake")
  INCLUDE("/usr/games/cocos2d-x-3.0beta2/myGameSpace/towerDefend/make/cocos2d/cocos/2d/cmake_install.cmake")
  INCLUDE("/usr/games/cocos2d-x-3.0beta2/myGameSpace/towerDefend/make/cocos2d/cocos/gui/cmake_install.cmake")
  INCLUDE("/usr/games/cocos2d-x-3.0beta2/myGameSpace/towerDefend/make/cocos2d/cocos/network/cmake_install.cmake")
  INCLUDE("/usr/games/cocos2d-x-3.0beta2/myGameSpace/towerDefend/make/cocos2d/extensions/cmake_install.cmake")
  INCLUDE("/usr/games/cocos2d-x-3.0beta2/myGameSpace/towerDefend/make/cocos2d/cocos/editor-support/spine/cmake_install.cmake")
  INCLUDE("/usr/games/cocos2d-x-3.0beta2/myGameSpace/towerDefend/make/cocos2d/cocos/editor-support/cocosbuilder/cmake_install.cmake")
  INCLUDE("/usr/games/cocos2d-x-3.0beta2/myGameSpace/towerDefend/make/cocos2d/cocos/editor-support/cocostudio/cmake_install.cmake")

ENDIF(NOT CMAKE_INSTALL_LOCAL_ONLY)

IF(CMAKE_INSTALL_COMPONENT)
  SET(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
ELSE(CMAKE_INSTALL_COMPONENT)
  SET(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
ENDIF(CMAKE_INSTALL_COMPONENT)

FILE(WRITE "/usr/games/cocos2d-x-3.0beta2/myGameSpace/towerDefend/make/${CMAKE_INSTALL_MANIFEST}" "")
FOREACH(file ${CMAKE_INSTALL_MANIFEST_FILES})
  FILE(APPEND "/usr/games/cocos2d-x-3.0beta2/myGameSpace/towerDefend/make/${CMAKE_INSTALL_MANIFEST}" "${file}\n")
ENDFOREACH(file)
