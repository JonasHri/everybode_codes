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
    let plantation_alt: Vec<Vec<char>> =
        fs::read_to_string("./inputs/everybody_codes_e2024_q18_p2.txt")
            .unwrap()
            .lines()
            .map(|line| line.chars().collect())
            .collect();

    let mut plantation = vec![vec!['#'; plantation_alt[0].len() + 2]; plantation_alt.len() + 2];
    for (i, col) in plantation_alt.iter().enumerate() {
        for (j, &val) in col.iter().enumerate() {
            plantation[i + 1][j + 1] = val;
        }
    }
    let palm_cords = find_indexes(&plantation, 'P');

    let mut flooded = vec![vec![false; plantation[0].len()]; plantation.len()];
    let mut flooded_next = vec![vec![false; plantation[0].len()]; plantation.len()];

    for i in 1..plantation.len() - 1 {
        if plantation[i][1] == '.' {
            flooded[i][1] = true;
        }
        if plantation[i][plantation[i].len() - 2] == '.' {
            flooded[i][plantation[i].len() - 2] = true;
        }
    }

    for i in 1..plantation[0].len() - 1 {
        if plantation[1][i] == '.' {
            flooded[1][i] = true;
        }
        if plantation[plantation.len() - 2][i] == '.' {
            flooded[plantation.len() - 2][i];
        }
    }

    for time in 0..10000 {
        let mut done = true;
        for &(x, y) in &palm_cords {
            if !flooded[x][y] {
                done = false;
                break;
            }
        }
        if done {
            println!("{}", time);
            break;
        }

        for (i, col) in plantation.iter().enumerate() {
            for (j, &val) in col.iter().enumerate() {
                if val == '#' {
                    continue;
                }
                if flooded[i][j] {
                    flooded_next[i][j] = true;
                    flooded_next[i + 1][j] = true;
                    flooded_next[i - 1][j] = true;
                    flooded_next[i][j + 1] = true;
                    flooded_next[i][j - 1] = true;
                }
            }
        }
        flooded = flooded_next;

        flooded_next = vec![vec![false; plantation[0].len()]; plantation.len()];

        // flooded.iter().for_each(|x| println!("{:?}", x));
        // println!();
    }
}
