use std::cmp::{max, min};
use std::fs;
fn main() {
    let field: Vec<Vec<char>> = fs::read_to_string("./inputs/everybody_codes_e2024_q03_p3.txt")
        .unwrap()
        .lines()
        .map(|line| line.chars().collect())
        .collect();

    let mut depths = vec![vec![0; field[0].len()]; field.len()];
    for _ in 0..100 {
        for i in 0..field.len() {
            for j in 0..field[i].len() {
                if field[i][j] != '#' {
                    continue;
                }
                let mut adj: Vec<i32> = Vec::new();

                for cols in &depths[max(i as i32 - 1, 0) as usize..=min(i + 1, depths.len() - 1)] {
                    for val in
                        &cols[max(j as i32 - 1, 0) as usize..=min(j + 1, depths[0].len() - 1)]
                    {
                        adj.push(*val);
                    }
                }
                if adj.len() != 9 {
                    adj.push(0);
                }
                depths[i][j] = adj.iter().min().unwrap() + 1;
            }
        }
    }
    println!(
        "{}",
        depths
            .iter()
            .map(|x| -> i32 { x.iter().sum() })
            .sum::<i32>()
    );
}
