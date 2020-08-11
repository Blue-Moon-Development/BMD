

file(GLOB_RECURSE APP_SRC_LIST CONFIGURE_DEPENDS
	"${BMD_SOURCE_DIR}/app/*.cpp"
	"${BMD_SOURCE_DIR}/app/*.cc"
	"${BMD_SOURCE_DIR}/app/*.cxx"
	"${BMD_SOURCE_DIR}/app/*.c"
	)

file(GLOB_RECURSE APP_HEADER_LIST CONFIGURE_DEPENDS
	"${BMD_SOURCE_DIR}/app/*.h"
	"${BMD_SOURCE_DIR}/app/*.hpp"
	)

add_executable(app ${APP_SRC_LIST} ${APP_HEADER_LIST})
#target_compile_features(app PRIVATE cxx_std_11)
set_property(TARGET app PROPERTY C_STANDARD 11)

message(Magenta "Linking BMD library to the test app")
target_link_libraries(app PRIVATE ${BMD_LIB})

source_group (
TREE    "${BMD_SOURCE_DIR}/app"
FILES   ${APP_HEADER_LIST}
PREFIX  "Header Files"
)