use std::error::Error;
use std::{fs, iter};

fn main() -> Result<(), Box<dyn Error>> {
    let message: Vec<String> = fs::read_to_string("everybody_codes_e2024_q06_p2.txt")
        .unwrap()
        .lines()
        .map(String::from)
        .collect();
    for line in &message {
        println!("{}", line);
    }

    let mut lenghts: Vec<usize> = iter::repeat(0).take(20).collect();
    for line in message.clone() {
        if line.contains("@") {
            let curdist = dist(&message, line.split(":").collect::<Vec<&str>>()[0]);
            lenghts[curdist] += 1;
        }
    }

    for ele in &lenghts {
        print!("{} ", ele);
    }
    println!();
    let best_len = match lenghts.iter().position(|&x| x == 1) {
        Some(x) => x,
        _ => 0,
    };

    for line in message.clone() {
        if line.contains("@") {
            let curdist = dist(&message, line.split(":").collect::<Vec<&str>>()[0]);
            if curdist == best_len {
                let res = printer(&message, line.split(":").collect::<Vec<&str>>()[0]);
                println!("{}", res);
            }
            lenghts[curdist] += 1;
        }
    }

    Ok(())
}

fn dist(tree: &Vec<String>, node: &str) -> usize {
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

fn printer(tree: &Vec<String>, node: &str) -> String {
    if node == "RR" {
        "R".to_string()
    } else {
        for line in tree {
            let root_branch = line.split(":").collect::<Vec<&str>>();
            let root = root_branch[0];
            let branches = root_branch[1];
            let strchar: &str = match node.chars().next() {
                Some(x) => &x.to_string(),
                _ => &" ".to_string(),
            };
            if branches.contains(node) {
                return format!("{}{}", printer(tree, root), strchar);
            }
        }
        " ".to_string()
    }
}
