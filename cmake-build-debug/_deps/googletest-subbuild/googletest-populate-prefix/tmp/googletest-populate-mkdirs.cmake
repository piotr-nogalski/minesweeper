# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "C:/Programowanie/mini_games/Minesweeper/cmake-build-debug/_deps/googletest-src"
  "C:/Programowanie/mini_games/Minesweeper/cmake-build-debug/_deps/googletest-build"
  "C:/Programowanie/mini_games/Minesweeper/cmake-build-debug/_deps/googletest-subbuild/googletest-populate-prefix"
  "C:/Programowanie/mini_games/Minesweeper/cmake-build-debug/_deps/googletest-subbuild/googletest-populate-prefix/tmp"
  "C:/Programowanie/mini_games/Minesweeper/cmake-build-debug/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp"
  "C:/Programowanie/mini_games/Minesweeper/cmake-build-debug/_deps/googletest-subbuild/googletest-populate-prefix/src"
  "C:/Programowanie/mini_games/Minesweeper/cmake-build-debug/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/Programowanie/mini_games/Minesweeper/cmake-build-debug/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp/${subDir}")
endforeach()
