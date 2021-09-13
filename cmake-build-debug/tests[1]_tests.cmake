add_test( Test.BasicAssertions /home/florian/CLionProjects/tumorSimulation/cmake-build-debug/tests [==[--gtest_filter=Test.BasicAssertions]==] --gtest_also_run_disabled_tests)
set_tests_properties( Test.BasicAssertions PROPERTIES WORKING_DIRECTORY /home/florian/CLionProjects/tumorSimulation/cmake-build-debug SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
set( tests_TESTS Test.BasicAssertions)
