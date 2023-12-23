# TODO 14: Remove mysqrt.cxx from the list of sources

# TODO 1: Add a library called MathFunctions with sources MathFunctions.cxx
# and mysqrt.cxx
add_library(MathFunctions STATIC MathFunctions.cxx)
# Hint: You will need the add_library command

# TODO 7: Create a variable USE_MYMATH using option and set default to ON
option(USE_MYMATH "Use mymath sqrt" ON)

# TODO 8: If USE_MYMATH is ON, use target_compile_definitions to pass
# USE_MYMATH as a precompiled definition to our source files
if(USE_MYMATH)
    target_compile_definitions(MathFunctions PRIVATE "USE_MY_FUCKING_MATH")
    #target_sources(MathFunctions PUBLIC "${PROJECT_SOURCE_DIR}/MathFunctions/mysqrt.cxx")
    add_library(SqrtLib STATIC mysqrt.cxx)
    target_link_libraries(MathFunctions PUBLIC SqrtLib)
endif()
# TODO 12: When USE_MYMATH is ON, add a library for SqrtLibrary with
# source mysqrt.cxx

# TODO 13: When USE_MYMATH is ON, link SqrtLibrary to the MathFunctions Library
