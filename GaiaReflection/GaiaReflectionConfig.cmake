cmake_minimum_required(3.10)

find_path(GaiaReflection_INCLUDE_DIRS "GaiaReflection")
find_library(GaiaReflection_LIBS "GaiaReflection")

if (GaiaReflection_INCLUDE_DIRS AND GaiaReflection_LIBS)
    set(GaiaReflection_FOUND TRUE)
endif()