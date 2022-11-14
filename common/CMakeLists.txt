AUX_SOURCE_DIRECTORY(. DIR_TEST1_SRCS)
ADD_LIBRARY(COMMON ${DIR_TEST1_SRCS} mysizemap.cpp mysizemap.h ClassSize.cpp ClassSize.h)