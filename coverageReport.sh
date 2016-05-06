MYPWD=${PWD}
GCOV_PREFIX=$MYPWD/build/coverage-data
export GCOV_PREFIX="$MYPWD/build/coverage-data"
export GCOV_PREFIX_STRIP=`echo $GCOV_PREFIX | tr -d -c '/\n' | awk '{ print length; }'`
echo "Directorio donde almacenar $GCOV_PREFIX strips $GCOV_PREFIX_STRIP"
cd build
make
echo "Creo los directorios necesarios"
mkdir -p $GCOV_PREFIX/applib/CMakeFiles/testapp.dir
mkdir -p $GCOV_PREFIX/CMakeFiles/applib.dir
echo "Copiando gcno desde $MYPWD/build/test/applib/CMakeFiles/testapp.dir/ a $GCOV_PREFIX/applib/CMakeFiles/testapp.dir"
rsync -acv --filter='+ */' --filter='+ *.cpp' --filter='+ *.h' --filter='+ *.gcno' --filter='- *' $MYPWD/build/test/applib/CMakeFiles/testapp.dir/ $GCOV_PREFIX/applib/CMakeFiles/testapp.dir
echo "Copando gcno desde $MYPWD/build/app/CMakeFiles/applib.dir/src  $GCOV_PREFIX/CMakeFiles/applib.dir "
rsync -acv --filter='+ */' --filter='+ *.cpp' --filter='+ *.h' --filter='+ *.gcno' --filter='- *' $MYPWD/build/app/CMakeFiles/applib.dir/src $GCOV_PREFIX/CMakeFiles/applib.dir
make coverage
