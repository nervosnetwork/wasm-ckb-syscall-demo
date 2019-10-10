# wasm-ckb-syscall-demo

This is a demo writing CKB scripts with syscalls in Rust

# How to use this:

```bash
$ git clone --recursive https://github.com/WebAssembly/wabt
$ git clone https://github.com/nervosnetwork/ckb-system-scripts
$ git clone https://github.com/nervosnetwork/wasm-ckb-syscall-demo
$ cd wabt
$ export WABT_PATH=`pwd`
$ mkdir build
$ cd build
$ cmake ..
$ cmake --build .
$ cd ../..
$ cd wasm-ckb-syscall-demo
$ cargo build --release --target=wasm32-unknown-unknown
$ $WABT_PATH/bin/wasm2c target/wasm32-unknown-unknown/release/wasm-secp256k1-test.wasm -o syscall.c
$ cd ..
$ sudo docker run --rm -it -v `pwd`:/code nervos/ckb-riscv-gnu-toolchain:xenial bash
(docker) $ cd /code/wasm-ckb-syscall-demo
(docker) $ riscv64-unknown-elf-gcc -o syscall_riscv64 -O3 main.c syscall.c /code/wabt/wasm2c/wasm-rt-impl.c -I /code/wabt/wasm2c -I /code/ckb-system-scripts/c
(docker) $ exit
```

Now you will have a syscall_riscv64 script ready to use in CKB, it will deny any transaction which has a cell starting with "carrot" in the data section.
