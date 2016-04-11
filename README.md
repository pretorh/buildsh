# buildsh
Generate shell commands to extract, configure, build and install from tar files

Installing software from source tar files usually require the following statements:
```
tar vxzf <file.tar.ext>
cd <file>
./configure [some optional parameters]
make
[sudo] make install
[remove the extracted files]
```

This is pretty easy. But doing it 20+ times (like installing a whole system from source) can get really iritating. Enter buildsh:
```
buildsh <file> --configure [option 1] --configure [option 2] ... | sh -e
```

## CLI parameters

The parameters are still changing. See the tests for sample usage
