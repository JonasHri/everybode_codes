use std::cmp;
use std::fs;

fn get_val(depths: &Vec<Vec<i32>>, i: i32, j: i32) -> i32 {
    if i < 0 || i as usize >= depths.len() || j < 0 || j as usize >= depths[i as usize].len() {
        return 0;
    }
    depths[i as usize][j as usize]
}

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
                for x in -1..=1 {
                    for y in -1..=1 {
                        if x == 0 && y == 0 {
                            continue;
                        }
                        adj.push(get_val(&depths, i as i32 + x, j as i32 + y));
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
