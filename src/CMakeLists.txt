include(filter)

file(GLOB_RECURSE HEADER_LIST CONFIGURE_DEPENDS
	${BMD_SOURCE_DIR}/include/*.h
	${BMD_SOURCE_DIR}/include/*.hpp
	)

file(GLOB_RECURSE SRC_LIST CONFIGURE_DEPENDS
	${BMD_SOURCE_DIR}/src/*.cpp
	${BMD_SOURCE_DIR}/src/*.cc
	${BMD_SOURCE_DIR}/src/*.cxx
	${BMD_SOURCE_DIR}/src/*.c
	)


if(MSVC)
	set(BMD_INCLUDES "../include")
else()
	set(BMD_INCLUDES "../include")
endif()

message(Blue "Adding static library ${BMD_LIB}")

add_library(${BMD_LIB} STATIC ${SRC_LIST} ${HEADER_LIST})
set_property(TARGET ${BMD_LIB} PROPERTY C_STANDARD 11)
define_property(TARGET PROPERTY HEADERS BRIEF_DOCS "Header files for the target" FULL_DOCS "Header files for the target to be used in source grouping")
set_property(TARGET ${BMD_LIB} PROPERTY HEADERS ${HEADER_LIST})

define_property(TARGET PROPERTY SRCS BRIEF_DOCS "Header files for the target" FULL_DOCS "Header files for the target to be used in source grouping")
set_property(TARGET ${BMD_LIB} PROPERTY SRCS ${SRC_LIST})

message(STATUS "Setting include directories for ${BMD_LIB}, dirs: ${BMD_INCLUDES}")
target_include_directories(${BMD_LIB} PUBLIC ${BMD_INCLUDES})
#target_compile_features(${BMD_LIB} PUBLIC cxx_std_11)

message(Blue "Creating folders for project ${BMD_STATIC}")
target_source_group(
				ROOT_DIR "${CMAKE_SOURCE_DIR}/src" "${CMAKE_SOURCE_DIR}/include"
				TARGET ${BMD_LIB}
				PREFIX "Sources" "Headers")