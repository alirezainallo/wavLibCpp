# Set library name
set(LIB_NAME WAV_CPP)

# Find all source files
file(GLOB_RECURSE ${LIB_NAME}_SRCS
    "include/*.hpp"
    "include/*.h"
    "src/*.cpp"
    "src/*.c"
)

# Declare the library
add_library(${LIB_NAME}_LIB STATIC
    ${${LIB_NAME}_SRCS}
)

# Set include directories
target_include_directories(${LIB_NAME}_LIB PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Install library
install(TARGETS ${LIB_NAME}_LIB DESTINATION lib)
install(FILES ${LIB_INC_FILES} DESTINATION include)
