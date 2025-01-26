use std::{collections::VecDeque, fs, usize};

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
        fs::read_to_string("./inputs/everybody_codes_e2024_q18_p3.txt")
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

    let mut minsum = usize::MAX;

    let mut all_dist = vec![vec![0; plantation[0].len()]; plantation.len()];
    for palm in palm_cords {
        let mut visited = vec![vec![false; plantation[0].len()]; plantation.len()];
        let mut flood = VecDeque::new();
        flood.push_back(palm);

        for time in 0..10000 {
            let mut next_flood = VecDeque::new();
            for (i, j) in flood {
                if plantation[i][j] == '#' {
                    continue;
                }
                if visited[i][j] {
                    continue;
                }
                visited[i][j] = true;
                all_dist[i][j] += time;
                next_flood.push_back((i + 1, j));
                next_flood.push_back((i - 1, j));
                next_flood.push_back((i, j + 1));
                next_flood.push_back((i, j - 1));
            }
            if next_flood.len() == 0 {
                break;
            }
            flood = next_flood;
        }
    }

    for i in 0..all_dist.len() {
        for j in 0..all_dist[0].len() {
            if all_dist[i][j] == 0 || plantation[i][j] == 'P' {
                all_dist[i][j] = usize::MAX;
            }
        }
    }

    println!(
        "{}",
        all_dist
            .iter()
            .map(|x| x.iter().min().unwrap())
            .min()
            .unwrap()
    );
}
