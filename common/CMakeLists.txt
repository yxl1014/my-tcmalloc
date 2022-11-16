AUX_SOURCE_DIRECTORY(. DIR_TEST1_SRCS)
ADD_LIBRARY(COMMON ${DIR_TEST1_SRCS} mysizemap.cpp mysizemap.h common.h my_span.cpp my_span.h my_page.h linked_list.h)