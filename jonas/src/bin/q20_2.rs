use std::collections::{HashMap, VecDeque};
use std::{fs, usize};
use tqdm::tqdm;

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
    let field_alt: Vec<Vec<char>> = fs::read_to_string("./inputs/everybody_codes_e2024_q20_p2.txt")
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
    gilders.push_back((start.0, start.1, start.0 - 1, start.1, 10001, 0, 0, 0));
    seen.insert((start.0, start.1, start.0 - 1, start.1, 0, 0, 0), 998);
    let mut max_alts = vec![vec![0 as usize; field[0].len()]; field.len()];

    let mut completed = false;
    for time in tqdm(0..1000) {
        if completed {
            println!("{}", time - 1);
            break;
        }
        let mut next_gliders = VecDeque::new();
        for (ci, cj, li, lj, l_alt, a, b, c) in gilders {
            // if l_alt >= 10000 && a + b + c == 3 {
            //     println!("{} {} {} {} {} {} {} {} ", ci, cj, li, lj, l_alt, a, b, c);
            // }
            if l_alt > 10100 {
                continue;
            }
            if field[ci][cj] == '#' {
                continue;
            }

            if field[ci][cj] == 'S' && (a + b + c) == 3 && l_alt >= 10_000 {
                completed = true;
                break;
            }

            let c_alt = match field[ci][cj] {
                '+' => l_alt + 1,
                '-' => l_alt - 2,
                _ => l_alt - 1,
            };

            let mut na = a;
            if field[ci][cj] == 'A' {
                na = 1;
            }

            let mut nb = b;
            if field[ci][cj] == 'B' && a == 1 {
                nb = 1;
            }

            let mut nc = c;
            if field[ci][cj] == 'C' && b == 1 {
                nc = 1;
            }

            if seen.contains_key(&(ci, cj, li, lj, na, nb, nc)) {
                let val = seen.get(&(ci, cj, li, lj, na, nb, nc)).unwrap();
                // if val.1 + val.2 + val.3 > na + nb + nc {
                //     continue;
                // }
                if val >= &c_alt {
                    continue;
                }
            }
            seen.insert((ci, cj, li, lj, na, nb, nc), c_alt);

            max_alts[ci][cj] = max_alts[ci][cj].max(c_alt);

            let next_pos = vec![(ci + 1, cj), (ci - 1, cj), (ci, cj + 1), (ci, cj - 1)];

            for (ni, nj) in next_pos {
                if (ni, nj) == (li, lj) {
                    continue;
                }
                next_gliders.push_back((ni, nj, ci, cj, c_alt, na, nb, nc));
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
