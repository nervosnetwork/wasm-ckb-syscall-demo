#include <stdio.h>
#include <stdlib.h>

#include "ckb_syscalls.h"
#include "syscall.h"

u32 (*Z_envZ_ckb_debugZ_ii)(u32);
u32 (*Z_envZ_ckb_load_cell_dataZ_iiijjj)(u32, u32, u64, u64, u64);
void (*Z_envZ_ckb_exitZ_vi)(u32);

u32 wasm_ckb_debug(u32 offset) {
  uint8_t* p = &(WASM_RT_ADD_PREFIX(Z_memory)->data[offset]);
  return (u32)ckb_debug(p);
}

u32 wasm_ckb_load_cell_data(u32 addr_offset, u32 len_offset, u64 offset,
                            u64 index, u64 source) {
  uint8_t* addr = &(WASM_RT_ADD_PREFIX(Z_memory)->data[addr_offset]);
  volatile uint64_t* len =
      (volatile uint64_t*)(&(WASM_RT_ADD_PREFIX(Z_memory)->data[len_offset]));
  return ckb_load_cell_data(addr, len, offset, index, source);
}

void wasm_ckb_exit(u32 code) { ckb_exit(code); }

int main() {
  Z_envZ_ckb_debugZ_ii = &wasm_ckb_debug;
  Z_envZ_ckb_load_cell_dataZ_iiijjj = &wasm_ckb_load_cell_data;
  Z_envZ_ckb_exitZ_vi = &wasm_ckb_exit;
  init();
  return WASM_RT_ADD_PREFIX(Z_mainZ_iii)(0, 0);
}
