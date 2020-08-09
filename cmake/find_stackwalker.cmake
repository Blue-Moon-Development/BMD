message(STATUS "Looking for STACKWALKER library")

SET( STACKWALKER_SEARCH_PATHS
	./lib/StackWalker
	./libs/StackWalker
	"$ENV{PROGRAMFILES}/StackWalker"			# WINDOWS
	"$ENV{PROGRAMFILES\(X86\)}/StackWalker"		# WINDOWS
)

find_path(STACKWALKER_INCLUDE_DIRS
	NAMES StackWalker.h
	PATHS ${STACKWALKER_SEARCH_PATHS}
	PATH_SUFFIXES include
	DOC "Find the folder with StackWalker.h")

find_library(STACKWALKER_LIBRARIES
	NAMES StackWalker
	PATHS ${STACKWALKER_SEARCH_PATHS}
	PATH_SUFFIXES lib
	DOC "The StackWalker library")

if(STACKWALKER_INCLUDE_DIRS AND STACKWALKER_LIBRARIES)
	set(STACKWALKER_FOUND TRUE)
	message(STATUS "Found STACKWALKER library")
else()
	set(STACKWALKER_FOUND FALSE)
	message(STATUS "Could not find STACKWALKER library")
endif()