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
    let field_alt: Vec<Vec<char>> = fs::read_to_string("./inputs/everybody_codes_e2024_q20_p1.txt")
        .unwrap()
        .lines()
        .map(|line| line.chars().collect())
        .collect();

    let mut field = vec![vec!['#'; field_alt[0].len() + 2]; field_alt.len() + 2];
    for (i, col) in field_alt.iter().enumerate() {
        for (j, &val) in col.iter().enumerate() {
            field[i + 1][j + 1] = val;
        }
    }
    for i in 0..field.len() {
        for j in 0..field[0].len() {
            print!("{}", field[i][j])
        }
        println!();
    }

    let mut gilders = VecDeque::new();
    let mut seen = HashMap::new();

    let start = find_indexes(&field, 'S')[0];
    gilders.push_back((start.0, start.1, start.0 - 1, start.1, 1001));
    seen.insert((start.0, start.1, start.0 - 1, start.1), 998);
    let mut max_alts = vec![vec![0 as usize; field[0].len()]; field.len()];

    for _time in 0..101 {
        let mut next_gliders = VecDeque::new();
        for (ci, cj, li, lj, l_alt) in gilders {
            if field[ci][cj] == '#' {
                continue;
            }

            let c_alt = match field[ci][cj] {
                '+' => l_alt + 1,
                '-' => l_alt - 2,
                _ => l_alt - 1,
            };

            if seen.contains_key(&(ci, cj, li, lj)) {
                if seen.get(&(ci, cj, li, lj)).unwrap() >= &c_alt {
                    continue;
                }
            }
            seen.insert((ci, cj, li, lj), c_alt);

            max_alts[ci][cj] = max_alts[ci][cj].max(c_alt);

            let next_pos = vec![(ci + 1, cj), (ci - 1, cj), (ci, cj + 1), (ci, cj - 1)];

            for (ni, nj) in next_pos {
                if (ni, nj) == (li, lj) {
                    continue;
                }
                next_gliders.push_back((ni, nj, ci, cj, c_alt));
            }
        }
        gilders = next_gliders;
    }

    println!(
        "{}",
        max_alts
            .iter()
            .map(|x| x.iter().max().unwrap())
            .max()
            .unwrap()
    );
}
