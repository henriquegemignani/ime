
# Inicializando...
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(horus_eye CXX)
SET(GAME_UNIXNAME trecos)
SET(GAME_NAME "Trecos")
SET(GAME_VERSION "0.0.1")
SET(CMAKE_BUILD_TYPE Release)
# Arquivos de código fonte vão aqui!
SET(GAME_SRCS ./base/display/Layer.cpp ./base/display/Sprite.cpp ./base/draw/Rect.cpp ./base/draw/Circle.cpp ./base/Engine.cpp ./base/InputManager.cpp ./base/Vector2D.cpp ./base/VideoManager.cpp ./base/display/Layer.h ./base/display/Sprite.h ./base/Displayable.h ./base/draw/Rect.h ./base/draw/Circle.h ./base/Drawable.h ./base/Engine.h ./base/InputManager.h ./base/types.h ./base/Vector2D.h ./base/VideoManager.h ./main.cpp ./Bomb.cpp ./Game.cpp ./GameObject.cpp ./Treco.cpp ./Bomb.h ./Game.h ./GameObject.h ./Treco.h )

MESSAGE("${GAME_NAME} version ${GAME_VERSION}")

# #define's que voce queira incluir na compilacao
# separe por espacos
SET(DEFS "" CACHE STRING "#define's que voce queira incluir na compilacao; separe por espacos")
IF(WIN32)
  SET(DEFS "${DEFS} WIN32")
  IF(MSVC)
    SET(DEFS "${DEFS} _CRT_SECURE_NO_DEPRECATE __MSVC__")
  ENDIF(MSVC)
ENDIF(WIN32)

# CFLAGS: flags que voce queira enviar ao compilador
# LDFLAGS: flags que voce queira enviar ao ligador
SET(CFLAGS "" CACHE STRING "flags enviadas ao compilador")
SET(LDFLAGS "" CACHE STRING "flags enviadas ao linker")
IF(UNIX)
  # se for o g++ para *nix:
  SET(CFLAGS "${CFLAGS} -g -Wall -ansi -O3 -U_FORTIFY_SOURCE")
  SET(LDFLAGS "${LDFLAGS}")
ELSE(UNIX)
  IF(MINGW)
    # se for o g++ para Windows:
    SET(CFLAGS "${CFLAGS} -Wall -ansi -O3 -U_FORTIFY_SOURCE")
    SET(LDFLAGS "${LDFLAGS}")
  ELSE(MINGW)
    # se for o Microsoft Visual C++:
    SET(CFLAGS "${CFLAGS}")
    SET(LDFLAGS "${LDFLAGS}")
  ENDIF(MINGW)
ENDIF(UNIX)

# Encontrando as bibliotecas necessarias:
IF(WIN32)
	FIND_LIBRARY(LFREEGLUT NAMES freeglut PATH "${CMAKE_LIBRARY_PATH}")
  IF(NOT LFREEGLUT)
  	MESSAGE(FATAL_ERROR "Erro fatal: libfreelut nao encontrada!")
  ENDIF(NOT LFREEGLUT)
ENDIF(WIN32)

# pre-processor: #define's
IF(MSVC)
  FOREACH(d ${DEFS})
    SET(CFLAGS_EXTRA "${CFLAGS_EXTRA} /D${d}")
  ENDFOREACH(d)
ELSE(MSVC)
  FOREACH(d ${DEFS})
    SET(CFLAGS_EXTRA "${CFLAGS_EXTRA} -D${d}")
  ENDFOREACH(d)
ENDIF(MSVC)

# *nix executable
IF(UNIX)
  ADD_EXECUTABLE(${GAME_UNIXNAME} ${GAME_SRCS})
  SET_TARGET_PROPERTIES(${GAME_UNIXNAME} PROPERTIES LINK_FLAGS "${LDFLAGS}")
  TARGET_LINK_LIBRARIES(${GAME_UNIXNAME} m GL GLU glut)
  SET_TARGET_PROPERTIES(${GAME_UNIXNAME} PROPERTIES COMPILE_FLAGS "${CFLAGS} ${CFLAGS_EXTRA}")
ENDIF(UNIX)

# Windows executable
IF(WIN32)

  # MSVC fix
  IF(MSVC)
    STRING(REGEX REPLACE "[.]cpp" ".h" GAME_HEADERS "${GAME_SRCS}")
    SET(GAME_SRCS ${GAME_SRCS} ${GAME_HEADERS})
  ENDIF(MSVC)

  # Executables
  ADD_EXECUTABLE(${GAME_UNIXNAME} WIN32 ${GAME_SRCS})
  
  # Other properties
  IF(MSVC)

    # Release properties
    SET_TARGET_PROPERTIES(${GAME_UNIXNAME} PROPERTIES LINK_FLAGS "${LDFLAGS}")
    SET_TARGET_PROPERTIES(${GAME_UNIXNAME} PROPERTIES COMPILE_FLAGS "/D_CRT_SECURE_NO_DEPRECATE /D__WIN32__ /D__MSVC__ ${CFLAGS} ${CFLAGS_EXTRA}")
    TARGET_LINK_LIBRARIES(${GAME_UNIXNAME} freeglut OpenGL32 glu32)

  ELSE(MSVC)

    # RC compiler
    IF(NOT CMAKE_RC_COMPILER)
      SET(CMAKE_RC_COMPILER windres)
    ENDIF(NOT CMAKE_RC_COMPILER)

    SET_TARGET_PROPERTIES(${GAME_UNIXNAME} PROPERTIES LINK_FLAGS "${LDFLAGS}")
    SET_TARGET_PROPERTIES(${GAME_UNIXNAME} PROPERTIES COMPILE_FLAGS "${CFLAGS} ${CFLAGS_EXTRA}")
    TARGET_LINK_LIBRARIES(${GAME_UNIXNAME} m mingw32 freeglut OpenGL32 glu32)

    # icone
	#EXECUTE_PROCESS(COMMAND ${CMAKE_RC_COMPILER} -O coff -o ./horus_eye.res -i ./horus_eye.rc)
	#SET_TARGET_PROPERTIES(${GAME_UNIXNAME} PROPERTIES LINK_FLAGS "horus_eye.res")
	#SET_TARGET_PROPERTIES(${GAME_DEBUGNAME} PROPERTIES LINK_FLAGS "horus_eye.res")

  ENDIF(MSVC)

ENDIF(WIN32)

# Misc
SET_TARGET_PROPERTIES(${GAME_UNIXNAME} PROPERTIES PROJECT_NAME "${GAME_NAME}")

# Installing on *nix
#IF(UNIX)
#  SET(GAME_INSTALL_DIR "/usr/share/${GAME_UNIXNAME}")
#  SET(GAME_FINAL_DIR "/usr/bin")
#  
#  INSTALL(CODE "MESSAGE(\"Installing ${GAME_NAME} ${GAME_VERSION}... Make sure you have root privileges.\")")
#  
#  INSTALL(TARGETS ${GAME_UNIXNAME} RUNTIME DESTINATION ${GAME_INSTALL_DIR})
#  INSTALL(DIRECTORY data DESTINATION ${GAME_INSTALL_DIR} PATTERN ".svn" EXCLUDE)
#
#  INSTALL(CODE "MESSAGE(\"Creating files at ${GAME_FINAL_DIR}...\")")
#  INSTALL(CODE "EXECUTE_PROCESS(COMMAND \"cmake\" \"-E\" \"copy\" \"${GAME_INSTALL_DIR}/${GAME_UNIXNAME}\" \"${GAME_FINAL_DIR}/${GAME_UNIXNAME}\")")
#  INSTALL(CODE "EXECUTE_PROCESS(COMMAND \"mkdir\" \"$ENV{HOME}/.horus_eye\")")
#  INSTALL(CODE "SET(USER_GROUP \"\")")
#  INSTALL(CODE "EXECUTE_PROCESS(COMMAND \"id\" \"-g\" OUTPUT_VARIABLE USER_GROUP)")
#  INSTALL(CODE "EXECUTE_PROCESS(COMMAND \"chown\" \"$ENV{USER}:${USER_GROUP}\" \"$ENV{HOME}/.horus_eye\")")
#  INSTALL(CODE "EXECUTE_PROCESS(COMMAND \"echo\" \"-n\" \"${GAME_INSTALL_DIR}/\" OUTPUT_FILE \"$ENV{HOME}/.horus_eye/rootpath.txt\")")
#
#  INSTALL(CODE "MESSAGE(\"Done! Please run ${GAME_UNIXNAME} to start ${GAME_NAME}.\")")
#ENDIF(UNIX)
#
#SET(USER_HOME "$ENV{HOME}")
#
#CONFIGURE_FILE(
#    "${PROJECT_SOURCE_DIR}/config.h.in"
#    "${PROJECT_SOURCE_DIR}/config.h"
#)

