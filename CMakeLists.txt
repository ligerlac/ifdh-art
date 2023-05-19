# ======================================================================
#  ifdh_art main build file
#
# ======================================================================
cmake_minimum_required(VERSION 3.19 FATAL_ERROR)

find_package(cetmodules 2.29.07 REQUIRED)
project(ifdh_art VERSION 2.13.15 LANGUAGES CXX)

include(CetCMakeEnv)
cet_cmake_env()

cet_set_compiler_flags(DIAGS VIGILANT
  WERROR
  NO_UNDEFINED
  EXTRA_FLAGS -pedantic
)

cet_report_compiler_flags(REPORT_THRESHOLD VERBOSE)

find_package(art REQUIRED)
find_package(libwda REQUIRED)
find_package(ifdhc REQUIRED PUBLIC)
find_package(ifbeam REQUIRED PUBLIC)
find_package(nucondb REQUIRED PUBLIC)
find_package(cetlib_except REQUIRED)


### STUFF FROM LINO
find_package(larcore REQUIRED EXPORT)
find_package(larcorealg REQUIRED EXPORT)
find_package(larcoreobj REQUIRED EXPORT)
find_package(lardata REQUIRED EXPORT)
find_package(lardataobj REQUIRED EXPORT)
find_package(larsim REQUIRED EXPORT)

find_package(nusimdata REQUIRED EXPORT)

find_package(art_root_io REQUIRED EXPORT)
find_package(art REQUIRED EXPORT)
find_package(messagefacility REQUIRED EXPORT)
find_package(canvas_root_io REQUIRED EXPORT)
find_package(canvas REQUIRED EXPORT)
find_package(fhiclcpp REQUIRED EXPORT)
find_package(cetlib REQUIRED)
find_package(cetlib_except REQUIRED)

find_package(ROOT COMPONENTS Core EG Hist MathMore Physics RIO Tree REQUIRED EXPORT)

message(STATUS "ENV{NPC_INSTALL_DIR}: [$ENV{NPC_INSTALL_DIR}]")
if (DEFINED ENV{NPC_INSTALL_DIR})
    message(STATUS "Detected user defined NPC_INSTALL_DIR...")
    set(CMAKE_INSTALL_PREFIX "$ENV{NPC_INSTALL_DIR}")
    set(CMAKE_PREFIX_PATH "$ENV{NPC_INSTALL_DIR}")
else()
    message(STATUS "NPC_INSTALL_DIR not set. Using default...")
endif()
message(STATUS "CMAKE_INSTALL_PREFIX: [${CMAKE_INSTALL_PREFIX}]")
message(STATUS "CMAKE_PREFIX_PATH: [${CMAKE_PREFIX_PATH}]")
find_library(npc_lib NAMES nopayloadclient)
find_path(npc_include NAMES nopayloadclient)
#####################


# macros
include(ArtMake)
include(BuildPlugins)

add_subdirectory (ifdh_art)
#add_subdirectory (tests)

# packaging utility
cet_cmake_config()
