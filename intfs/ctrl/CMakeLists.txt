add_subdirectory(CtrlIntfModule)
add_subdirectory(TCPCtrlIntfModule)
add_subdirectory(UARTCtrlIntfModule)
add_subdirectory(HTTPCtrlIntfModule)

set(MODULES_HDRS ${MODULES_HDRS} PARENT_SCOPE)
set(MODULES_SRCS ${MODULES_SRCS} PARENT_SCOPE)
