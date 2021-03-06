cmake_minimum_required(VERSION 2.6)

if(enable_smpi AND enable_smpi_MPICH3_testsuite AND SMPI_F2C)
  if(WIN32)
    set(CMAKE_C_FLAGS "-include ${CMAKE_HOME_DIRECTORY}/include/smpi/smpi_main.h")
  else()
    set(CMAKE_C_COMPILER "${CMAKE_BINARY_DIR}/smpi_script/bin/smpicc")
    set(CMAKE_Fortran_COMPILER "${CMAKE_BINARY_DIR}/smpi_script/bin/smpiff")
  endif()

  set(EXECUTABLE_OUTPUT_PATH "${CMAKE_CURRENT_BINARY_DIR}")
  include_directories("${CMAKE_HOME_DIRECTORY}/include/smpi")
  include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../include/")

  add_executable(allctypesf allctypesf.f ../util/mtestf.f)
  add_executable(gaddressf gaddressf.f ../util/mtestf.f)
  add_executable(hindex1f hindex1f.f ../util/mtestf.f)
  add_executable(hindexed_blockf hindexed_blockf.f ../util/mtestf.f)
  add_executable(packef packef.f ../util/mtestf.f)
  add_executable(typeaints typeaints.h ../util/mtestf.f)
  add_executable(typecntsf typecntsf.f ../util/mtestf.f)
  add_executable(typem2f typem2f.f ../util/mtestf.f)
  add_executable(typename3f typename3f.f ../util/mtestf.f)
  add_executable(typenamef typenamef.f ../util/mtestf.f)
  add_executable(typesnamef typesnamef.f ../util/mtestf.f)
  add_executable(typesubf typesubf.f ../util/mtestf.f)

  target_link_libraries(allctypesf  simgrid)
  target_link_libraries(gaddressf  simgrid)
  target_link_libraries(hindex1f  simgrid)
  target_link_libraries(hindexed_blockf  simgrid)
  target_link_libraries(packef  simgrid)
  target_link_libraries(typeaints  simgrid)
  target_link_libraries(typecntsf  simgrid)
  target_link_libraries(typem2f  simgrid)
  target_link_libraries(typename3f  simgrid)
  target_link_libraries(typenamef  simgrid)
  target_link_libraries(typesnamef  simgrid)
  target_link_libraries(typesubf  simgrid)

endif()

set(tesh_files
  ${tesh_files}
  PARENT_SCOPE
  )
set(xml_files
  ${xml_files}
  PARENT_SCOPE
  )
set(examples_src
  ${examples_src}
  ${CMAKE_CURRENT_SOURCE_DIR}/allctypesf.f
  ${CMAKE_CURRENT_SOURCE_DIR}/gaddressf.f
  ${CMAKE_CURRENT_SOURCE_DIR}/hindex1f.f
  ${CMAKE_CURRENT_SOURCE_DIR}/hindexed_blockf.f
  ${CMAKE_CURRENT_SOURCE_DIR}/packef.f
  ${CMAKE_CURRENT_SOURCE_DIR}/typeaints.h
  ${CMAKE_CURRENT_SOURCE_DIR}/typecntsf.f
  ${CMAKE_CURRENT_SOURCE_DIR}/typem2f.f
  ${CMAKE_CURRENT_SOURCE_DIR}/typename3f.f
  ${CMAKE_CURRENT_SOURCE_DIR}/typenamef.f
  ${CMAKE_CURRENT_SOURCE_DIR}/typesnamef.f
  ${CMAKE_CURRENT_SOURCE_DIR}/typesubf.f
  PARENT_SCOPE
  )
set(bin_files
  ${bin_files}
  PARENT_SCOPE
  )
set(txt_files
  ${txt_files}
  ${CMAKE_CURRENT_SOURCE_DIR}/testlist
  ${CMAKE_CURRENT_SOURCE_DIR}/../util/mtestf.f
  PARENT_SCOPE
  )
