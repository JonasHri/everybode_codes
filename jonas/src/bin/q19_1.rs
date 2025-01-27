use std::{fs, usize};

fn rotate(cypher_text: &mut Vec<Vec<char>>, i: usize, j: usize, direction: char) {
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

    let mut save = vec![vec!['c'; 3]; 3];

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
    let input: Vec<Vec<char>> =
        fs::read_to_string("./inputs/everybody_codes_e2024_q19_p1_trial.txt")
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

    // for _ in 0..10 {
    //     println!();
    //     cypher_text
    //         .iter()
    //         .for_each(|x| println!("{}", String::from_iter(x)));

    //     rotate(&mut cypher_text, 1, 2, 'L');
    // }

    let mut key_pos = 0;
    for i in 1..cypher_text.len() - 1 {
        for j in 1..cypher_text[0].len() - 1 {
            rotate(&mut cypher_text, i, j, pattern[key_pos % pattern.len()]);
            key_pos += 1;
        }
    }

    cypher_text
        .iter()
        .for_each(|x| println!("{}", String::from_iter(x)));
}
