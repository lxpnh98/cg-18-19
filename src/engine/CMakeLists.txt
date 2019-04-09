file(GLOB SOURCE_FILES *.cpp)
file(GLOB HEADER_FILES *.h)

add_library(engine ${SOURCE_FILES} ${HEADER_FILES})

target_include_directories(engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

if(NOT OPENGL_FOUND)
    message(ERROR " OPENGL not found!")
endif(NOT OPENGL_FOUND)

if  (WIN32)

	set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT class1)
	message(STATUS "GLUT_DIR set to: " ${GLUT_DIR})
	set(GLUT_DIR "" CACHE PATH "Path to GLUT folder")
	if (NOT EXISTS "${GLUT_DIR}/GL/glut.h" OR NOT EXISTS "${GLUT_DIR}/glut32.lib")
		message(ERROR ": GLUT not found")
	endif (NOT EXISTS "${GLUT_DIR}/GL/glut.h" OR NOT EXISTS "${GLUT_DIR}/glut32.lib")
	include_directories(${GLUT_DIR})
	link_directories(${GLUT_DIR})
	target_link_libraries(engine ${OPENGL_LIBRARIES} ${GLUT_DIR}/glut32.lib )

else (WIN32) #Linux and Mac

	find_package(GLUT REQUIRED)
	include_directories(${GLUT_INCLUDE_DIR})
	link_directories(${GLUT_LIBRARY_DIRS})
	add_definitions(${GLUT_DEFINITIONS})
	target_link_libraries(engine ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )
	if(NOT GLUT_FOUND)
	   message(ERROR ": GLUT not found!")
	endif(NOT GLUT_FOUND)

endif(WIN32)
