

file(GLOB_RECURSE APP_SRC_LIST CONFIGURE_DEPENDS
	"${BMD_SOURCE_DIR}/app_cpp/*.cpp"
	"${BMD_SOURCE_DIR}/app_cpp/*.cc"
	"${BMD_SOURCE_DIR}/app_cpp/*.cxx"
	"${BMD_SOURCE_DIR}/app_cpp/*.c"
	)

file(GLOB_RECURSE APP_HEADER_LIST CONFIGURE_DEPENDS
	"${BMD_SOURCE_DIR}/app_cpp/*.h"
	"${BMD_SOURCE_DIR}/app_cpp/*.hpp"
	)

add_executable(app_cpp ${APP_SRC_LIST} ${APP_HEADER_LIST})
target_compile_features(app_cpp PRIVATE cxx_std_11)
#set_property(TARGET app PROPERTY C_STANDARD 11)

message(Magenta "Linking BMD library to the test app")
target_link_libraries(app_cpp PRIVATE ${BMD_LIB})

source_group (
TREE    "${BMD_SOURCE_DIR}/app_cpp"
FILES   ${APP_HEADER_LIST}
PREFIX  "Header Files"
)