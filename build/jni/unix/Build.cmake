find_library(STATICSYS NAMES boost_exception)
set(SYSLIBS ${STATICSYS} boost_system ${STATICSYS})
add_executable(ins.${BUILDEXT} ${INSSRCS})
target_link_libraries(ins.${BUILDEXT} ${SYSLIBS})
add_executable(interconnect.${BUILDEXT} ${INTERCONNECTSRCS})
target_link_libraries(interconnect.${BUILDEXT} ${SYSLIBS})
