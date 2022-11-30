# Quick Start
## install conan
This repo uses conan as a package manager.  
Read [this site](https://docs.conan.io/en/latest/installation.html), and install it!

## install modules
```sh
$ conan install . --install-folder bin
```

## build
```sh
$ conan build . --build-folder bin 
```

## Run offline Algorithms
```sh
$ bin/bin/main --type=offline --input-file ./input-files/input1.txt --graph-file ./graph-config/three-dfa/config1.spec 
```