find_library(STATICSYS NAMES boost_exception)
set(SYSLIBS ${STATICSYS} boost_system ${STATICSYS})
add_executable(ins.${BUILDEXT} ${INSSRCS})
target_link_libraries(ins.${BUILDEXT} ${SYSLIBS})
add_executable(interconnect.${BUILDEXT} ${INTERCONNECTSRCS})
target_link_libraries(interconnect.${BUILDEXT} ${SYSLIBS})
add_executable(
               interconnect.test.${BUILDEXT}
               EXCLUDE_FROM_ALL
               ${INTERCONNECT.TEST.SRCS}
              )
target_link_libraries(interconnect.test.${BUILDEXT} ${SYSLIBS} "pthread")

add_executable(xcsoar.test.${BUILDEXT} EXCLUDE_FROM_ALL ${XCSOAR.TEST.SRCS})
target_link_libraries(xcsoar.test.${BUILDEXT} ${SYSLIBS} "pthread")

add_executable(ins.test.${BUILDEXT} EXCLUDE_FROM_ALL ${INS.TEST.SRCS})
target_link_libraries(ins.test.${BUILDEXT} ${SYSLIBS} "pthread")

add_executable(flarm.test.${BUILDEXT} EXCLUDE_FROM_ALL ${FLARM.TEST.SRCS})
target_link_libraries(flarm.test.${BUILDEXT} ${SYSLIBS} "pthread")

add_test(NAME faketest COMMAND echo "fake test")
add_test(NAME interconnect.test COMMAND interconnect.test.${BUILDEXT})
