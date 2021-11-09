set ROOT_DIR = %CD%

cd src

set path=%path%I:\tools\swigwin-4.0.2;
swig -c++ -python -cppext cpp kansuji2digit.i
nmake -f Makefile.msvc

cd %ROOT_DIR%
