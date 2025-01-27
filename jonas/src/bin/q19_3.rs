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

fn rotate<T>(cypher_text: &mut Vec<Vec<T>>, i: usize, j: usize, direction: char)
where
    T: Clone,
    T: Copy,
{
    let start = vec![
        (i - 1, j),
        (i - 1, j + 1),
        (i, j + 1),
        (i + 1, j + 1),
        (i + 1, j),
        (i + 1, j - 1),
        (i, j - 1),
        (i - 1, j - 1),
    ];

    let end: Vec<(usize, usize)> = match direction {
        'R' => vec![
            (0, 2),
            (1, 2),
            (2, 2),
            (2, 1),
            (2, 0),
            (1, 0),
            (0, 0),
            (0, 1),
        ],
        'L' => vec![
            (0, 0),
            (0, 1),
            (0, 2),
            (1, 2),
            (2, 2),
            (2, 1),
            (2, 0),
            (1, 0),
        ],

        _ => vec![(999, 999)],
    };

    let mut save = vec![vec![cypher_text[0][0]; 3]; 3];

    for x in 0..start.len() {
        save[end[x].0][end[x].1] = cypher_text[start[x].0][start[x].1];
    }

    for x in 0..=2 {
        for y in 0..=2 {
            if x == 1 && y == 1 {
                continue;
            }
            cypher_text[i + x - 1][j + y - 1] = save[x][y];
        }
    }
}

fn main() {
    let input: Vec<Vec<char>> = fs::read_to_string("./inputs/everybody_codes_e2024_q19_p3.txt")
        .unwrap()
        .lines()
        .map(|line| line.chars().collect())
        .collect();

    let pattern = input[0].clone();

    let mut cypher_text = vec![vec!['+'; input[2].len()]; input.len() - 2];

    for i in 0..cypher_text.len() {
        for j in 0..cypher_text[0].len() {
            cypher_text[i][j] = input[i + 2][j]
        }
    }

    for iteration in tqdm(0..1048576000) {
        let mut key_pos = 0;

        let sol_start = find_indexes(&cypher_text, '>')[0];
        let sol_end = find_indexes(&cypher_text, '<')[0];

        if sol_start.0 == sol_end.0 && sol_start.1 < sol_end.1 {
            let mut potential = true;
            for i in sol_start.1..=sol_end.1 {
                if cypher_text[sol_start.0][i] == '.' {
                    potential = false;
                    break;
                }
            }
            if potential {
                for i in sol_start.1..=sol_end.1 {
                    print!("{}", cypher_text[sol_start.0][i])
                }
                println!(" {}\n", iteration);
            }
        }

        for i in 1..cypher_text.len() - 1 {
            for j in 1..cypher_text[0].len() - 1 {
                rotate(&mut cypher_text, i, j, pattern[key_pos % pattern.len()]);
                key_pos += 1;
            }
        }
    }

    cypher_text
        .iter()
        .for_each(|x| println!("{}", String::from_iter(x)));
}
