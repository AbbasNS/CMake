cmake_minimum_required(VERSION 3.24)
project(cxx_modules_library NONE)

set(CMAKE_EXPERIMENTAL_CXX_MODULE_CMAKE_API "3c375311-a3c9-4396-a187-3227ef642046")

find_package(export_interfaces REQUIRED)

if (NOT TARGET CXXModules::export_interfaces)
  message(FATAL_ERROR
    "Missing imported target")
endif ()

get_property(file_sets TARGET CXXModules::export_interfaces
  PROPERTY INTERFACE_CXX_MODULE_SETS)
if (NOT file_sets STREQUAL "modules")
  message(FATAL_ERROR
    "Incorrect exported file sets in `CXXModules::export_interfaces`: `${file_sets}`")
endif ()

get_property(file_set_files TARGET CXXModules::export_interfaces
  PROPERTY CXX_MODULE_SET_modules)
if (NOT file_set_files STREQUAL "${expected_dir}/importable.cxx")
  message(FATAL_ERROR
    "Incorrect exported file set paths in CXXModules::export_interfaces`: `${file_set_files}`")
endif ()

get_property(imported_modules_set TARGET CXXModules::export_interfaces
  PROPERTY IMPORTED_CXX_MODULES_DEBUG SET)
if (imported_modules_set)
  message(FATAL_ERROR
    "Unexpected C++ modules specified.")
endif ()