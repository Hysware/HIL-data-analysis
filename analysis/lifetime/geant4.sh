sudo apt-get update
sudo apt install build-essential
mkdir geant4
cd geant4
## Install cmake
# sudo apt install cmake
wget https://github.com/Kitware/CMake/releases/download/v4.1.0-rc4/cmake-4.1.0-rc4.tar.gz
mkdir cmake
mv cmake-4.1.0-rc4.tar.gz cmake
cd cmake
tar -zxvf cmake-4.1.0-rc4.tar.gz
cd cmake-4.1.0-rc4
make -j4
sudo make install
cd ../..

## Install clhep
wget https://proj-clhep.web.cern.ch/proj-clhep/dist1/clhep-2.4.7.1.tgz
mkdir clhep
mv clhep-* clhep
cd clhep
tar -zxvf clhep-*
cd 2.4*
mkdir build
cd build
cmake ../CLHEP
make -j4
sudo make install
cd ../../../

wget https://dlcdn.apache.org//xerces/c/3/sources/xerces-c-3.3.0.tar.gz
mkdir xerces
mv xerces-c-3.3.0.tar.gz xerces
cd xerces
tar -zxvf xerces-c-3.3.0.tar.gz
cd xerces-c-3.3.0
mkdir build
cd build
cmake ../
make -j4
sudo make install
cd ../../..
