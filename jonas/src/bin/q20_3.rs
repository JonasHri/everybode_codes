use std::collections::{HashMap, VecDeque};
use std::{fs, usize};

fn find_indexes(field: &Vec<Vec<char>>, target: char) -> Vec<(usize, usize)> {
    let mut indexes = Vec::new();

    for (i, row) in field.iter().enumerate() {
        for (j, &value) in row.iter().enumerate() {
            if value == target {
                indexes.push((i, j));
            }
        }
    }

    indexes
}

fn main() {
    let field: Vec<Vec<char>> = fs::read_to_string("./inputs/everybody_codes_e2024_q20_p3.txt")
        .unwrap()
        .lines()
        .map(|line| line.chars().collect())
        .collect();

    for i in 0..field.len() {
        for j in 0..field[0].len() {
            print!("{}", field[i][j])
        }
        println!();
    }

    let mut alt = 384400;

    let mut pos = find_indexes(&field, 'S')[0];

    pos.1 = pos.1 + 2;
    alt -= 2;

    while alt > 0 {
        alt += match field[pos.0 % field.len()][pos.1] {
            '+' => 1,
            _ => -1,
        };
        pos.0 += 1;
    }
    println!("{}", pos.0);
}
