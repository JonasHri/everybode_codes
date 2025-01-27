use std::{fs, usize};

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
fn invert(pos_map: &mut Vec<Vec<(usize, usize)>>) {
    let mut inv_map = vec![vec![(0, 0); pos_map[0].len()]; pos_map.len()];

    for i in 0..pos_map.len() {
        for j in 0..pos_map[0].len() {
            let x = pos_map[i][j].0;
            let y = pos_map[i][j].1;
            inv_map[x][y] = (i, j);
        }
    }
    for i in 0..pos_map.len() {
        for j in 0..pos_map[0].len() {
            pos_map[i][j] = inv_map[i][j];
        }
    }
}

fn apply_map<T>(pos_map: &Vec<Vec<(usize, usize)>>, cypher: &mut Vec<Vec<T>>)
where
    T: Clone,
    T: Copy,
{
    let mut cop_cypher = vec![vec![cypher[0][0]; cypher[0].len()]; cypher.len()];

    for i in 0..pos_map.len() {
        for j in 0..pos_map[0].len() {
            let x = pos_map[i][j].0;
            let y = pos_map[i][j].1;
            cop_cypher[x][y] = cypher[i][j];
        }
    }
    for i in 0..pos_map.len() {
        for j in 0..pos_map[0].len() {
            cypher[i][j] = cop_cypher[i][j];
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

    let mut pos_map = vec![vec![(0, 0); cypher_text[0].len()]; cypher_text.len()];

    for i in 0..pos_map.len() {
        for j in 0..pos_map[0].len() {
            pos_map[i][j] = (i, j);
        }
    }

    let mut key_pos = 0;

    for i in 1..cypher_text.len() - 1 {
        for j in 1..cypher_text[0].len() - 1 {
            rotate(&mut pos_map, i, j, pattern[key_pos % pattern.len()]);
            key_pos += 1;
        }
    }
    invert(&mut pos_map);

    let mut iterations = 1048576000;
    // iterations = 100;

    while iterations > 0 {
        if iterations % 2 == 1 {
            apply_map(&pos_map, &mut cypher_text);
        }
        iterations /= 2;

        let mut new_map = vec![vec![(0, 0); cypher_text[0].len()]; cypher_text.len()];
        for i in 0..pos_map.len() {
            for j in 0..pos_map[0].len() {
                new_map[i][j] = (i, j);
            }
        }

        apply_map(&pos_map, &mut new_map);
        apply_map(&pos_map, &mut new_map);
        invert(&mut new_map);

        for i in 0..pos_map.len() {
            for j in 0..pos_map[0].len() {
                pos_map[i][j] = new_map[i][j];
            }
        }
    }

    cypher_text
        .iter()
        .for_each(|x| println!("{}", String::from_iter(x)));
}
