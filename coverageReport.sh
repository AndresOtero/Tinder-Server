MYPWD=${PWD}
GCOV_PREFIX=$MYPWD/build/coverage-data
export GCOV_PREFIX="$MYPWD/build/coverage-data"
export GCOV_PREFIX_STRIP=`echo $GCOV_PREFIX | tr -d -c '/\n' | awk '{ print length; }'`
cd build
echo  $GCOV_PREFIX
mkdir -p $GCOV_PREFIX/applib/CMakeFiles/testapp.dir
mkdir -p $GCOV_PREFIX/CMakeFiles/applib.dir
rsync -acv --filter='+ */' --filter='+ *.cpp' --filter='+ *.h' --filter='+ *.gcno' --filter='- *' $MYPWD/build/test/applib/CMakeFiles/testapp.dir/ $GCOV_PREFIX/applib/CMakeFiles/testapp.dir
rsync -acv --filter='+ */' --filter='+ *.cpp' --filter='+ *.h' --filter='+ *.gcno' --filter='- *' $MYPWD/build/app/CMakeFiles/applib.dir/src $GCOV_PREFIX/CMakeFiles/applib.dir

make coverage
