use std::cmp::{max, min};
use std::fs;

fn find_idx(maze: &Vec<Vec<char>>, chr: char) -> (usize, usize) {
    for (i, col) in maze.iter().enumerate() {
        for (j, val) in col.iter().enumerate() {
            if *val == chr {
                return (i, j);
            }
        }
    }
    return (usize::MAX, usize::MAX);
}

fn height(chr: char) -> usize {
    match chr {
        'S' => 0,
        'E' => 0,
        x => x.to_digit(10).unwrap() as usize,
    }
}

fn main() {
    let maze: Vec<Vec<char>> = fs::read_to_string("./inputs/everybody_codes_e2024_q13_p2.txt")
        .unwrap()
        .lines()
        .map(|line| line.chars().collect())
        .collect();

    let mut padmaze: Vec<Vec<char>> = vec![vec!['#'; maze[0].len() + 2]; maze.len() + 2];

    for (i, col) in maze.iter().enumerate() {
        for (j, val) in col.iter().enumerate() {
            padmaze[i + 1][j + 1] = *val;
        }
    }

    let mut traves_times = vec![vec![usize::MAX; padmaze[0].len()]; padmaze.len()];

    for i in 0..padmaze.len() {
        for j in 0..padmaze[0].len() {
            if padmaze[i][j] == 'S' {
                traves_times[i][j] = 0;
            }
        }
    }

    let adj: Vec<(i64, i64)> = vec![(-1, 0), (1, 0), (0, -1), (0, 1)];

    for _ in 0..100 {
        for i in 0..traves_times.len() {
            for j in 0..traves_times[0].len() {
                let val = traves_times[i][j];
                if val == usize::MAX || padmaze[i][j] == '#' {
                    continue;
                }
                let cur_height = height(padmaze[i][j]);
                for mov in &adj {
                    let i_next = (i as i64 + mov.0) as usize;
                    let j_next = (j as i64 + mov.1) as usize;

                    if padmaze[i_next][j_next] == '#' {
                        continue;
                    }
                    let next_height = height(padmaze[i_next][j_next]);

                    let height_dif = cur_height.abs_diff(next_height);
                    let time = if height_dif > 5 {
                        10 - height_dif
                    } else {
                        height_dif
                    };
                    let next_time = val + time + 1;
                    traves_times[i_next][j_next] = min(traves_times[i_next][j_next], next_time);
                }
            }
        }
    }

    let end = find_idx(&padmaze, 'E');
    println!("{}", traves_times[end.0][end.1]);
}
