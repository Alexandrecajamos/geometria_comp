
cmake_minimum_required(VERSION 3.5.1)
 
project(ImageToOBJ)
 
find_package(ITK REQUIRED)
include(${ITK_USE_FILE})
if (ITKVtkGlue_LOADED)
  find_package(VTK REQUIRED)
  include(${VTK_USE_FILE})
else()
  find_package(ItkVtkGlue REQUIRED)
  include(${ItkVtkGlue_USE_FILE})
  set(Glue ItkVtkGlue)
endif()
 
add_executable(ImageToOBJ MACOSX_BUNDLE ImageToOBJ.cxx)
target_link_libraries(ImageToOBJ
  ${Glue}  ${VTK_LIBRARIES} ${ITK_LIBRARIES})
