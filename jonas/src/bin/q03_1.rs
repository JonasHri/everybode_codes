use std::cmp;
use std::fs;

fn main() {
    let field: Vec<Vec<char>> = fs::read_to_string("./inputs/everybody_codes_e2024_q03_p2.txt")
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

                depths[i][j] = vec![
                    depths[i + 1][j],
                    depths[i - 1][j],
                    depths[i][j + 1],
                    depths[i][j - 1],
                ]
                .iter()
                .min()
                .unwrap()
                    + 1;
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
