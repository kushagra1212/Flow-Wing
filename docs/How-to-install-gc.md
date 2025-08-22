```bash
git clone https://github.com/ivmai/libatomic_ops.git
git clone https://github.com/ivmai/bdwgc.git
```

## Mac
```bash
brew install automake autoconf libtool
```

## Linux (Ubuntu)
```bash
sudo apt-get  install automake autoconf libtool
```


```bash
cd libatomic_ops
./autogen.sh && ./configure && make && sudo make install
cd ..


cd bdwgc
./autogen.sh && ./configure --enable-static --disable-shared --enable-cplusplus && make && sudo make install

```
```bash
ls /usr/local/lib
```