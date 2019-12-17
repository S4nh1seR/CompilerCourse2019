cd dependencies
mkdir flex && cd flex
wget https://github.com/westes/flex/releases/download/v2.6.3/flex-2.6.3.tar.gz
tar xvzf flex-2.6.3.tar.gz
cd flex-2.6.3
./configure
make 
sudo make install
