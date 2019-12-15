cd dependencies
mkdir bison && cd bison
wget - ftp.gnu.org/gnu/bison/bison-3.5.tar.gz
tar xvzf bison-3.5.tar.gz
cd bison-3.5
./configure
make 
sudo make install

