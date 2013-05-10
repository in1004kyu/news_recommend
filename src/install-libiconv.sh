wget http://ftp.gnu.org/pub/gnu/libiconv/libiconv-1.14.tar.gz
tar xzf libiconv-1.14.tar.gz
cd libiconv-1.14
./configure --prefix=$(pwd)/../../ --enable-static=no --enable-shared=yes \
					 --enable-extra-encodings=yes
make;make install
