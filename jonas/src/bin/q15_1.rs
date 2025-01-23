use std::cmp::min;
use std::collections::{HashSet, VecDeque};
use std::fs;

fn main() {
    let field_alt: Vec<Vec<char>> = fs::read_to_string("./inputs/everybody_codes_e2024_q15_p1.txt")
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

    let mut visited = vec![vec![0; field[0].len()]; field.len()];

    field.iter().for_each(|x| println!("{:?}", x));

    let mut start_pos: (usize, usize) = (1, 1);

    for i in 1..field.len() - 1 {
        if field[i][1] == '.' {
            start_pos = (i, 1)
        }
        if field[i][field[i].len() - 2] == '.' {
            start_pos = (i, field[i].len() - 2);
        }
    }

    for i in 1..field[0].len() - 1 {
        if field[1][i] == '.' {
            start_pos = (1, i)
        }
        if field[field.len() - 2][i] == '.' {
            start_pos = (field.len() - 2, i);
        }
    }

    println!("{:?}", start_pos);

    let mut queue = VecDeque::new();
    queue.push_back((start_pos.0, start_pos.1, 0));
    loop {
        let pos = queue.pop_front().unwrap();
        if visited[pos.0][pos.1] == 1 {
            continue;
        }
        visited[pos.0][pos.1] = 1;

        if field[pos.0][pos.1] == '#' {
            continue;
        }
        if field[pos.0][pos.1] == 'H' {
            println!("{}", pos.2 * 2);
            break;
        }

        queue.push_back((pos.0 + 1, pos.1, pos.2 + 1));
        queue.push_back((pos.0, pos.1 + 1, pos.2 + 1));
        queue.push_back((pos.0 - 1, pos.1, pos.2 + 1));
        queue.push_back((pos.0, pos.1 - 1, pos.2 + 1));
    }
}
