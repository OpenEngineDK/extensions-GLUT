SET( EXTENSION_NAME "Extensions_GLUT")

ADD_LIBRARY( ${EXTENSION_NAME}
  Display/GLUTFrame.h
  Display/GLUTFrame.cpp
  Devices/GLUTInput.h
  Devices/GLUTInput.cpp
  Core/GLUTEngine.h
  Core/GLUTEngine.cpp
)

TARGET_LINK_LIBRARIES( ${EXTENSION_NAME}
  ${GLUT_LIBRARIES}
)
