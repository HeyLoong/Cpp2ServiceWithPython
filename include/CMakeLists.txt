 # root of your msvc14 x64 prebuild, there should be a `/lib/cmake` dir

set( CMAKE_INCLUDE_CURRENT_DIR ON )
set( CMAKE_AUTOMOC ON )
  
file(GLOB_RECURSE HEAD_FILES "algorithm/*.cc") 

add_library(c_model SHARED ${HEAD_FILES}) 

target_link_libraries(c_model
    PUBLIC
	model.lib
	model.dll
	geos.lib
	geos_c.lib 
)   
target_link_directories(c_model 
	PUBLIC
)
 target_include_directories( c_model
	PUBLIC
	"E:\\C_training\\model_python\\include"
)
 

