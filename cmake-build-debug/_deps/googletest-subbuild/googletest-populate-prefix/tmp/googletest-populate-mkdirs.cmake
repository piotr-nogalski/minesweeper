# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "C:/Programowanie/projekty_cpp/projekty_wlasne/Minesweeper/cmake-build-debug/_deps/googletest-src"
  "C:/Programowanie/projekty_cpp/projekty_wlasne/Minesweeper/cmake-build-debug/_deps/googletest-build"
  "C:/Programowanie/projekty_cpp/projekty_wlasne/Minesweeper/cmake-build-debug/_deps/googletest-subbuild/googletest-populate-prefix"
  "C:/Programowanie/projekty_cpp/projekty_wlasne/Minesweeper/cmake-build-debug/_deps/googletest-subbuild/googletest-populate-prefix/tmp"
  "C:/Programowanie/projekty_cpp/projekty_wlasne/Minesweeper/cmake-build-debug/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp"
  "C:/Programowanie/projekty_cpp/projekty_wlasne/Minesweeper/cmake-build-debug/_deps/googletest-subbuild/googletest-populate-prefix/src"
  "C:/Programowanie/projekty_cpp/projekty_wlasne/Minesweeper/cmake-build-debug/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/Programowanie/projekty_cpp/projekty_wlasne/Minesweeper/cmake-build-debug/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp/${subDir}")
endforeach()
