use itertools::iproduct;
use itertools::Itertools;
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

fn path_length(field: &Vec<Vec<char>>, start: (usize, usize), end: (usize, usize)) -> usize {
    let mut queue = VecDeque::new();
    let mut visited = vec![vec![0; field[0].len()]; field.len()];
    queue.push_back((start.0, start.1, 0));
    loop {
        let pos = queue.pop_front().unwrap();
        if visited[pos.0][pos.1] == 1 {
            continue;
        }
        visited[pos.0][pos.1] = 1;

        if field[pos.0][pos.1] == '#' || field[pos.0][pos.1] == '~' {
            continue;
        }
        if (pos.0, pos.1) == end {
            return pos.2;
        }

        queue.push_back((pos.0 + 1, pos.1, pos.2 + 1));
        queue.push_back((pos.0, pos.1 + 1, pos.2 + 1));
        queue.push_back((pos.0 - 1, pos.1, pos.2 + 1));
        queue.push_back((pos.0, pos.1 - 1, pos.2 + 1));
    }
}

fn main() {
    let field_alt: Vec<Vec<char>> =
        fs::read_to_string("./inputs/everybody_codes_e2024_q15_p3_try_3.txt")
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
    let middle = 614;
    // let start_pos: (usize, usize) = find_indexes(&field, 'S')[0];
    // let herbs = "GHIJKZ".chars().collect::<Vec<char>>();

    let left = 430;
    // let start_pos: (usize, usize) = find_indexes(&field, 'E')[0];
    // let herbs = "ABCD".chars().collect::<Vec<char>>();

    let right = 446;
    let start_pos: (usize, usize) = find_indexes(&field, 'R')[0];
    let herbs = "NOPQ".chars().collect::<Vec<char>>();

    let extra_steps = 12;

    println!("{} ", middle + left + right + extra_steps);

    let herb_positions: Vec<Vec<(usize, usize)>> =
        herbs.iter().map(|x| find_indexes(&field, *x)).collect();

    let mut shortest_path = usize::MAX;
    let mut seen: HashMap<((usize, usize), (usize, usize)), usize> = HashMap::new();

    let order: Vec<usize> = herbs.iter().enumerate().map(|(i, _)| i).collect();
    for ord in tqdm(order.iter().permutations(herbs.len())) {
        for v in iproduct!(
            &vec![start_pos],
            &herb_positions[*ord[0]],
            &herb_positions[*ord[1]],
            &herb_positions[*ord[2]],
            &herb_positions[*ord[3]],
            // &herb_positions[*ord[4]],
            // &herb_positions[*ord[5]],
            // &herb_positions[*ord[6]],
            // &herb_positions[*ord[7]],
            // &herb_positions[*ord[8]],
            // &herb_positions[*ord[9]],
            &vec![start_pos],
        ) {
            let targets = vec![
                *v.0, *v.1, *v.2, *v.3, *v.4, *v.5, // *v.6, *v.7, // *v.8, *v.9, *v.10,
            ];
            let mut total_distance = 0;
            for i in 0..targets.len() - 1 {
                let mut run = vec![targets[i], targets[i + 1]];

                run.sort_by(|x, y| (x.0 * 10000 + x.1).cmp(&(y.0 * 10000 - y.1)));
                let key = (run[0], run[1]);
                if seen.contains_key(&key) {
                    total_distance += seen.get(&key).unwrap();
                } else {
                    let dist = path_length(&field, key.0, key.1);
                    total_distance += dist;
                    seen.insert(key, dist);
                }
            }
            if total_distance < shortest_path {
                shortest_path = total_distance;
            }
        }
    }
    println!("{}", shortest_path);
}
