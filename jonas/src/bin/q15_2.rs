use itertools::Itertools;
use std::collections::VecDeque;
use std::fs;

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
    let field_alt: Vec<Vec<char>> = fs::read_to_string("./inputs/everybody_codes_e2024_q15_p2.txt")
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

    let herbs = vec!['A', 'B', 'C'];

    let herb_positions: Vec<Vec<(usize, usize)>> =
        herbs.iter().map(|x| find_indexes(&field, *x)).collect();

    let mut shortest_path = usize::MAX;
    for order in vec![0 as usize, 1 as usize, 2 as usize]
        .iter()
        .permutations(3)
    {
        for &tar1 in &herb_positions[*order[0]] {
            for &tar2 in &herb_positions[*order[1]] {
                for &tar3 in &herb_positions[*order[2]] {
                    let targets = vec![tar1, tar2, tar3, start_pos];

                    let mut cur_tar = 0;
                    let mut visited = vec![vec![0; field[0].len()]; field.len()];
                    let mut queue = VecDeque::new();
                    queue.push_back((start_pos.0, start_pos.1, 0));
                    loop {
                        let pos = queue.pop_front().unwrap();
                        if visited[pos.0][pos.1] == 1 {
                            continue;
                        }
                        visited[pos.0][pos.1] = 1;

                        if field[pos.0][pos.1] == '#' || field[pos.0][pos.1] == '~' {
                            continue;
                        }
                        if (pos.0, pos.1) == targets[cur_tar] {
                            if cur_tar == targets.len() - 1 {
                                shortest_path = shortest_path.min(pos.2);
                                break;
                            }
                            cur_tar += 1;
                            queue = VecDeque::new();
                            visited = vec![vec![0; field[0].len()]; field.len()];
                        }

                        queue.push_back((pos.0 + 1, pos.1, pos.2 + 1));
                        queue.push_back((pos.0, pos.1 + 1, pos.2 + 1));
                        queue.push_back((pos.0 - 1, pos.1, pos.2 + 1));
                        queue.push_back((pos.0, pos.1 - 1, pos.2 + 1));
                    }
                }
            }
        }
    }
    println!("{}", shortest_path);
}
