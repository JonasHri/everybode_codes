use std::error::Error;
use std::fs;

fn main() -> Result<(), Box<dyn Error>> {
    let message: Vec<String> = fs::read_to_string("everybody_codes_e2024_q06_p1.txt")
        .unwrap()
        .lines()
        .map(String::from)
        .collect();
    for line in &message {
        println!("{}", line);
    }
    for line in message.clone() {
        if line.contains("@") {
            println!(
                "\n{}",
                dist(&message, line.split(":").collect::<Vec<&str>>()[0])
            );
        }
    }
    Ok(())
}

fn dist(tree: &Vec<String>, node: &str) -> i32 {
    print!("{}", node);
    if node == "RR" {
        0
    } else {
        for line in tree {
            let root_branch = line.split(":").collect::<Vec<&str>>();
            let root = root_branch[0];
            let branches = root_branch[1];
            if branches.contains(node) {
                return 1 + dist(tree, root);
            }
        }
        0
    }
}
