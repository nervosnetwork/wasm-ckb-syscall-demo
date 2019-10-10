use std::ptr;

const CKB_INDEX_OUT_OF_BOUND: u32 = 1;
const CKB_SOURCE_OUTPUT: u64 = 2;

const TEST_STRING: &str = "carrot";

extern "C" {
    fn ckb_exit(code: i8);
    fn ckb_debug(message: *const u8) -> i32;
    fn ckb_load_cell_data(
        addr: *mut u8,
        len: *mut u64,
        offset: u64,
        index: u64,
        source: u64,
    ) -> u32;
}

fn main() {
    unsafe {
        ckb_debug("Hello from Rust".as_ptr());
    };
    let mut buffer = [0u8; 6];
    #[allow(unused_assignments)]
    let mut len = 0u64;
    let mut index = 0u64;

    loop {
        len = 6;
        unsafe {
            let p = buffer.as_mut_ptr();
            ptr::write_bytes(p, 0, buffer.len());
        };
        let ret = unsafe {
            ckb_load_cell_data(buffer.as_mut_ptr(), &mut len, 0, index, CKB_SOURCE_OUTPUT)
        };
        if ret == CKB_INDEX_OUT_OF_BOUND {
            break;
        }
        if buffer == TEST_STRING.as_bytes() {
            unsafe {
                ckb_exit(-1);
            }
            unreachable!();
        }
        index += 1;
    }
}
