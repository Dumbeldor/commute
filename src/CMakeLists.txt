include_directories(
        # for cmake_config.h
        ${PROJECT_BINARY_DIR}/include)

set(SOURCE_FILES commute.c engine.c graphics.c timer.c)
set(SDL2_INCLUDE_DIR /usr/include/SDL2)
set(SDL2_LIBRARY /usr/lib/libSDL2.so)
set(LIBRARY m sndfile)

if (ENABLE_UNITTESTS)
    message("-- Unittests enabled")
    set(UNITTESTS 1)
    set(PROJECT_LIBS ${PROJECT_LIBS} cppunit)
    set(SOURCE_FILES ${SOURCE_FILES} unittests/tests.h)
else()
    message("-- Unittests disabled")
endif()

find_package (Threads)
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} ${PROJECT_LIBS})
target_link_libraries (${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY})
target_link_libraries(${PROJECT_NAME} ${LIBRARY})

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

install(TARGETS ${PROJECT_NAME}
        RUNTIME DESTINATION ${BINDIR}
        BUNDLE DESTINATION .
        )
