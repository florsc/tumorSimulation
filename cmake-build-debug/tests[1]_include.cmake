if(EXISTS "/home/florian/CLionProjects/tumorSimulation/cmake-build-debug/tests[1]_tests.cmake")
  include("/home/florian/CLionProjects/tumorSimulation/cmake-build-debug/tests[1]_tests.cmake")
else()
  add_test(tests_NOT_BUILT tests_NOT_BUILT)
endif()
