
if (NOT EXISTS "/home/e20160018322/Bureau/IMAGINE1-s2/IMAGINE1-S2/HMIN212/TP4 - Transformations-20210316/TP4_code/build/external/glfw-3.1.2/install_manifest.txt")
  message(FATAL_ERROR "Cannot find install manifest: \"/home/e20160018322/Bureau/IMAGINE1-s2/IMAGINE1-S2/HMIN212/TP4 - Transformations-20210316/TP4_code/build/external/glfw-3.1.2/install_manifest.txt\"")
endif()

file(READ "/home/e20160018322/Bureau/IMAGINE1-s2/IMAGINE1-S2/HMIN212/TP4 - Transformations-20210316/TP4_code/build/external/glfw-3.1.2/install_manifest.txt" files)
string(REGEX REPLACE "\n" ";" files "${files}")

foreach (file ${files})
  message(STATUS "Uninstalling \"$ENV{DESTDIR}${file}\"")
  if (EXISTS "$ENV{DESTDIR}${file}")
    exec_program("/usr/bin/cmake" ARGS "-E remove \"$ENV{DESTDIR}${file}\""
                 OUTPUT_VARIABLE rm_out
                 RETURN_VALUE rm_retval)
    if (NOT "${rm_retval}" STREQUAL 0)
      MESSAGE(FATAL_ERROR "Problem when removing \"$ENV{DESTDIR}${file}\"")
    endif()
  elseif (IS_SYMLINK "$ENV{DESTDIR}${file}")
    EXEC_PROGRAM("/usr/bin/cmake" ARGS "-E remove \"$ENV{DESTDIR}${file}\""
                 OUTPUT_VARIABLE rm_out
                 RETURN_VALUE rm_retval)
    if (NOT "${rm_retval}" STREQUAL 0)
      message(FATAL_ERROR "Problem when removing symlink \"$ENV{DESTDIR}${file}\"")
    endif()
  else()
    message(STATUS "File \"$ENV{DESTDIR}${file}\" does not exist.")
  endif()
endforeach()
