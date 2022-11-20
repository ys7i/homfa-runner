# Quick Start
## install conan
This repo uses conan as a package manager.  
Reading [this site](https://docs.conan.io/en/latest/installation.html), and install it!

## install modules
```sh
$ conan install . --install-folder modules
```

## build
```sh
$ cmake . -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release
$ cd bin
$ cmake --build ..
```

## Run offline Algorithms
```sh
$ cd bin
$ ./main --input-file ../input-files/input1.txt --graph-file ../graph-config/three-dfa/config1.spec 
```