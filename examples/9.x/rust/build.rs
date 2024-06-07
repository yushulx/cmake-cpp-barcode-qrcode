use std::env;
use cc::Build;

use std::fs;
use walkdir::WalkDir;
use std::path::{Path, PathBuf};

fn main() {
    // Determine the target operating system
    let target_os = env::var("CARGO_CFG_TARGET_OS").unwrap();
    println!("OUT_DIR: {}..............................................", env::var("OUT_DIR").unwrap());
    println!("cargo:warning=OS: {}..............................................", target_os);

    match target_os.as_str() {
        "windows" => {
            // Link Dynamsoft Barcode Reader for Windows
            println!("cargo:rustc-link-search=../../../platforms/win/lib");
            println!("cargo:rustc-link-lib=static=DBRx64");

            // Copy *.dll files to the output path for Windows
            let src_dir = Path::new("../../../platforms/win/bin");
            copy_shared_libs_from_dir_to_out_dir(src_dir, &get_out_dir(), "dll");
        },
        "linux" => {
            // Link Dynamsoft Barcode Reader for Linux
            println!("cargo:rustc-link-search=../../../platforms/linux");
            println!("cargo:rustc-link-lib=dylib=DynamsoftBarcodeReader");

            // Set rpath for Linux
            println!("cargo:rustc-link-arg=-Wl,-rpath,../../../platforms/linux");

            // Copy *.so files to the output path for Linux
            let src_dir = Path::new("../../../platforms/linux/bin");
            copy_shared_libs_from_dir_to_out_dir(src_dir, &get_out_dir(), "so");
        },
        "macos" => {
            // Link Dynamsoft Barcode Reader for macOS
            println!("cargo:rustc-link-search=../../../platforms/macos");
            println!("cargo:rustc-link-lib=dylib=DynamsoftBarcodeReader");
            
            // Set rpath for macOS
            println!("cargo:rustc-link-arg=-Wl,-rpath,@loader_path/../../../platforms/macos");

            // Copy *.dylib files to the output path for macOS
            let src_dir = Path::new("../../../platforms/macos");
            copy_shared_libs_from_dir_to_out_dir(src_dir, &get_out_dir(), "dylib");
        },
        _ => {
            panic!("Unsupported target OS: {}", target_os);
        }
    }

    // Compile the C++ code
    Build::new()
        .cpp(true)
        .include("../../../include")
        .file("lib/bridge.cpp")
        .compile("bridge");

    // Tell cargo to tell rustc to link the compiled C library
    println!("cargo:rustc-link-lib=static=bridge");

    // Add the directory where the library was built to the search path
    println!("cargo:rustc-link-search=native={}", env::var("OUT_DIR").unwrap());
}

fn get_out_dir() -> PathBuf {
    let out_dir = env::var("OUT_DIR").unwrap();
    let debug_offset = out_dir.find("debug").unwrap_or(0);
    let release_offset = out_dir.find("release").unwrap_or(0);
    let mut path = String::from("");

    if debug_offset > 0 {
        println!(">>> where is debug {}", debug_offset);
        path.push_str(&format!("{}", &out_dir[..debug_offset]));
        path.push_str("debug");
        println!("{}", path);
    }

    if release_offset > 0 {
        println!(">>> where is release {}", release_offset);
        path.push_str(&format!("{}", &out_dir[..release_offset]));
        path.push_str("release");
        println!("{}", path);
    }

    PathBuf::from(path)
}

fn copy_shared_libs_from_dir_to_out_dir(src_dir: &Path, out_dir: &Path, extension: &str) {
    for entry in WalkDir::new(src_dir).into_iter().filter_map(|e| e.ok()) {
        if entry.path().extension().and_then(|ext| ext.to_str()) == Some(extension) {
            let lib_path = entry.path();
            let file_name = lib_path.file_name().unwrap();
            let dest_path = out_dir.join(file_name);

            fs::copy(lib_path, dest_path.clone()).expect("Failed to copy shared library");
            println!("Copied {} to {}", lib_path.display(), dest_path.display());
        }
    }
}