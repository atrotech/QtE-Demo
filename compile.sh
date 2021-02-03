echo "starting..."
sudo rm -rf QtE-Demo
echo "environment cleared"
echo "cloning..."
sudo git clone https://github.com/atrotech/QtE-Demo.git
echo "cloning completed !"
cd QtE-Demo
echo "building..."
mkdir build
cd build
echo "making..."
qmake-qt5 ../
make -j4
cd ../
echo "set environment..."
. setqt5env
echo "compiling completed! Thank you for your patience"
echo "running"

./QtE-Demo
