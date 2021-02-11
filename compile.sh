
sudo rm QtE-Demo/*

sudo git clone https://github.com/atrotech/QtE-Demo.git temp

sudo mv temp/* QtE-Demo/

sudo rm -rf temp/

cd QtE-Demo/build

sudo qmake-qt5 ../
sudo make

cd ../

. setqt5env

./QtE-Demo
