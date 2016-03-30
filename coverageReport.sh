MYPWD=${PWD}
rsync -acv --filter='+ */' --filter='+ *.cpp' --filter='+ *.h' --filter='+ *.gcno' --filter='- *' $MYPWD/build/test/applib/CMakeFiles/testapp.dir/ $GCOV_PREFIX/applib/CMakeFiles/testapp.dir
rsync -acv --filter='+ */' --filter='+ *.cpp' --filter='+ *.h' --filter='+ *.gcno' --filter='- *' $MYPWD/build/app/CMakeFiles/applib.dir/src $GCOV_PREFIX/CMakeFiles/applib.dir
cd build
make coverage
