if(EXISTS "/home/samuel/Documents/helion-lang/build/test/catch_testing_tests-b12d07c.cmake")
  include("/home/samuel/Documents/helion-lang/build/test/catch_testing_tests-b12d07c.cmake")
else()
  add_test(catch_testing_NOT_BUILT-b12d07c catch_testing_NOT_BUILT-b12d07c)
endif()