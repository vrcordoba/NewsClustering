# additional target to perform cppcheck run, requires cppcheck

file(GLOB_RECURSE ALL_SOURCE_FILES
   *.cpp
)

add_custom_target(
   cppcheck
   COMMAND /usr/bin/cppcheck
   --enable=all
   --std=c++11
   --verbose
   --quiet
   --suppress=missingIncludeSystem
   -I . ${ALL_SOURCE_FILES}
)

