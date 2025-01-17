use std::fs;

fn main() {
    let field: Vec<Vec<char>> = fs::read_to_string("./inputs/everybody_codes_e2024_q03_p3.txt")
        .unwrap()
        .lines()
        .map(|line| line.chars().collect())
        .collect();

    let mut big_field: Vec<Vec<char>> = vec![vec!['.'; field[0].len() + 2]; field.len() + 2];
    for (i, col) in field.iter().enumerate() {
        for (j, val) in col.iter().enumerate() {
            big_field[i + 1][j + 1] = *val;
        }
    }

    let mut depths = vec![vec![0; big_field[0].len()]; big_field.len()];
    for _ in 0..100 {
        for i in 1..big_field.len() - 1 {
            for j in 1..big_field[i].len() - 1 {
                if big_field[i][j] != '#' {
                    continue;
                }
                let mut adj: Vec<i32> = Vec::new();

                for col in &depths[i - 1..=i + 1] {
                    for val in &col[j - 1..=j + 1] {
                        adj.push(*val);
                    }
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
