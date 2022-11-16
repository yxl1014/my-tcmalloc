cmake_minimum_required(VERSION 3.23)
project(My_TCMalloc)

set(CMAKE_CXX_STANDARD 11)


ADD_SUBDIRECTORY(back-end)
ADD_SUBDIRECTORY(front-end)
ADD_SUBDIRECTORY(middle-end)
ADD_SUBDIRECTORY(common)

AUX_SOURCE_DIRECTORY(. DIR_SRCS)

add_executable(My_TCMalloc ${DIR_SRCS} try/com/Span.cpp try/com/Span.h try/com/page.cpp try/com/page.h)

TARGET_LINK_LIBRARIES(My_TCMalloc BACK_END FRONT_END MIDDLE_END COMMON)