# Unit C Testing With CMocka 

[cmocka]: https://api.cmocka.org/
[CMakeLists]: tests/CMakeLists.txt
[AddressSanitizer]: https://clang.llvm.org/docs/AddressSanitizer.html
[calculator_test]: https://git.cryptomilk.org/projects/cmocka.git/tree/example/calculator_test.c
**[cmocka]** is a an elegant unit testing framework for `C` with support for mock objects. It only requires the standard `C` library, unit testing `C` library with mock support.

This tutorial describes unit testing pure `C` code with **[cmocka]**.
## How to install CMake
Remove old version of cmake:

`sudo apt purge --auto-remove cmake`
Obtain a copy of the signing key:

`wget -O - https://apt.kitware.com/keys/kitware-archive-latest.asc 2>/dev/null | gpg --dearmor - | sudo tee /etc/apt/trusted.gpg.d/kitware.gpg >/dev/null`

Add the repository to your sources list:

a. For Ubuntu Focal Fossa (20.04)

`sudo apt-add-repository 'deb https://apt.kitware.com/ubuntu/ focal main'`     
b. For Ubuntu Bionic Beaver (18.04)

`sudo apt-add-repository 'deb https://apt.kitware.com/ubuntu/ bionic main'`
c. For Ubuntu Xenial Xerus (16.04)

`sudo apt-add-repository 'deb https://apt.kitware.com/ubuntu/ xenial main'`
Update and install

`sudo apt update`
`sudo apt install cmake`

## How to install adress sanitizer library:
`sudo apt install libasan5`

## How to install CMocka
1. wget http://git.cryptomilk.org/projects/cmocka.git/snapshot/master.tar.gz
2. tar -xvf master
3. cd master
4. mkdir build
5. cd build/
6. cmake ..
7. sudo make all install

**Note** If you get the following error when you build your project with cmocka:

`error while loading shared libraries: libcmocka.so.0: cannot open shared object file: No such file or directory`

It means that program loader cannot find the cmocka shared library file. You need to add the directory in which the shared library  `libmocka.so.0` is present to the file `/etc/ld.so.conf`:

1. First check if `/usr/local/lib` is in LD_LIBRARY_PATH : `echo $LD_LIBRARY_PATH`
2. If step 1 fails: Try temporarily adding it using `export LD_LIBRARY_PATH=/usr/local/lib64:${LD_LIBRARY_PATH}`. When you run your program this time it should work.
3. If step 2 works: Check whether `libcmocka.so.0` resides in `/usr/local/lib` or `/usr/local/lib64`. For example in my Fedora Workstation it resides in `/usr/local/lib64`.
4. Now check whether `/usr/local/lib64` is in `etc/ld.so.conf`. Note that some distros, like my Fedora Workstation, have an `/etc/ld.so.conf.d` directory with and `.conf` file is in that directory. In my case it is `/etc/ld.so.conf.d/libiscsi-x86_64.conf`.
5. Add `/usr/local/lib` (or `/usr/local/lib64`) into the `.conf` file. So in my case I add `/usr/local/lib64` into `/etc/ld.so.conf.d/libiscsi-x86_64.conf` by opening my `emacs` editor in `sudo` mode.
6. Run `sudo ldconfig`.


**NOTE**: After this simple introductive tutorial you should see the examples in **https://git.cryptomilk.org/projects/cmocka.git/tree/example** especially **[calculator_test]** to be able to use [cmocka] in full power! )

1. `master` branch gives 2 examples of basics of testing with `cmocka`
2. `mocking-examples` branch gives 3 non-trivial examples of mocking with `cmocka`.


## Things to note in tests/[CMakeLists]
[AddressSanitizer] (`asan` library) is a fast memory error detector. (`sudo dnf install libasan`)
* `target_compile_options(${TARGET_NAME} PUBLIC "-fsanitize=address" "-g" "-O1" "-fno-omit-frame-pointer")`
### Link the test target with the sanitizer lib (should be first), mocka lib, and the lib that it tests. lib has been created before!
* `target_link_libraries(${TARGET_NAME} asan ${TARGET_BASE_LIB} cmocka)` 
### Add test into the cmake tests
* `add_test(NAME ${TARGET_NAME} COMMAND ${TARGET_NAME})`
### Set some test properties which will be used by CMake
* `set_tests_properties(${TARGET_NAME} PROPERTIES TIMEOUT 5)`


