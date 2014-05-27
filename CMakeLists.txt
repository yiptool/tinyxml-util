
ADD_LIBRARY(tinyxml-util STATIC
	tinyxml-util.cpp
	tinyxml-util.h
)

TARGET_LINK_LIBRARIES(tinyxml-util tinyxml strtod)
