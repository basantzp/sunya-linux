// Sunya Linux Package Manager
// Language: Rust
// Fast, memory-safe, low battery usage

use std::env;
use std::process;

fn main() {
    let args: Vec<String> = env::args().collect();

    if args.len() < 2 {
        print_help();
        process::exit(1);
    }

    match args[1].as_str() {
        "install"   => install(&args[2..]),
        "remove"    => remove(&args[2..]),
        "update"    => update(),
        "search"    => search(&args[2..]),
        "list"      => list(),
        "--version" => println!("sunya-pkg v0.1.0"),
        "--help"    => print_help(),
        _           => {
            eprintln!("Unknown command: {}", args[1]);
            print_help();
            process::exit(1);
        }
    }
}

fn install(packages: &[String]) {
    if packages.is_empty() {
        eprintln!("Error: No package name provided.");
        process::exit(1);
    }
    for pkg in packages {
        println!("Installing {}...", pkg);
    }
}

fn remove(packages: &[String]) {
    if packages.is_empty() {
        eprintln!("Error: No package name provided.");
        process::exit(1);
    }
    for pkg in packages {
        println!("Removing {}...", pkg);
    }
}

fn update() {
    println!("Updating all packages...");
}

fn search(packages: &[String]) {
    if packages.is_empty() {
        eprintln!("Error: No search term provided.");
        process::exit(1);
    }
    for pkg in packages {
        println!("Searching for {}...", pkg);
    }
}

fn list() {
    println!("Listing installed packages...");
}

fn print_help() {
    println!("Sunya Package Manager v0.1.0");
    println!("Usage: sunya-pkg <command> [packages]");
    println!();
    println!("Commands:");
    println!("  install <pkg>   Install a package");
    println!("  remove  <pkg>   Remove a package");
    println!("  update          Update all packages");
    println!("  search  <pkg>   Search for a package");
    println!("  list            List installed packages");
    println!("  --version       Show version");
    println!("  --help          Show this help");
}
