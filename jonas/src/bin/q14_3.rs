use std::collections::{HashSet, VecDeque};
use std::hash::Hash;
use std::{fs, usize};

fn dir_to_cord(dir: char) -> (i32, i32, i32) {
    match dir {
        'U' => (0, 0, 1),
        'D' => (0, 0, -1),
        'R' => (0, 1, 0),
        'L' => (0, -1, 0),
        'F' => (1, 0, 0),
        'B' => (-1, 0, 0),
        _ => (0, 0, 0),
    }
}

fn main() {
    let file = fs::read_to_string("./inputs/everybody_codes_e2024_q14_p3.txt").unwrap();

    let space_size = 200;
    let mut space = vec![vec![vec![0 as usize; space_size]; space_size]; space_size];
    let mut sap_points: Vec<(usize, usize, usize)> = Vec::new();

    for line in file.lines() {
        let growth_seq: Vec<&str> = line.split(',').collect();

        let mut dirs: Vec<(i32, i32, i32)> = Vec::new();
        let mut amounts: Vec<usize> = Vec::new();

        for val in growth_seq {
            let chars = val.chars().collect::<Vec<char>>();
            dirs.push(dir_to_cord(chars[0]));
            amounts.push(chars[1..].iter().collect::<String>().parse().unwrap());
        }

        let mut pos: (usize, usize, usize) = (space_size / 2, space_size / 2, 0);

        for (i, &amount) in amounts.iter().enumerate() {
            for _ in 0..amount {
                pos.0 = (pos.0 as i32 + dirs[i].0) as usize;
                pos.1 = (pos.1 as i32 + dirs[i].1) as usize;
                pos.2 = (pos.2 as i32 + dirs[i].2) as usize;

                space[pos.0][pos.1][pos.2] = 1;
            }
        }
        if space[pos.0][pos.1][pos.2] != 2 {
            space[pos.0][pos.1][pos.2] = 2;
            sap_points.push(pos);
        } else {
            println!("overlap!");
        }
    }

    sap_points.iter().for_each(|x| println!("{:?}", x));

    let mut min_murk = usize::MAX;
    for target_height in 0..space_size - 1 {
        let target = (space_size / 2, space_size / 2, target_height);
        if space[target.0][target.1][target.2] != 1 {
            continue;
        }
        let mut murkyness = 0;
        for point in &sap_points {
            let mut queue = VecDeque::new();
            let mut seen = HashSet::new();

            queue.push_back((point.0, point.1, point.2, 0 as usize));
            loop {
                let position = queue.pop_front().unwrap();

                if seen.contains(&(position.0, position.1, position.2)) {
                    continue;
                }
                seen.insert((position.0, position.1, position.2));

                if (position.0, position.1, position.2) == target {
                    murkyness += position.3;
                    break;
                }

                for dx in position.0 - 1..=position.0 + 1 {
                    for dy in position.1 - 1..=position.1 + 1 {
                        for dz in position.2 - 1..=position.2 + 1 {
                            if space[dx][dy][dz] < 1 {
                                continue;
                            }
                            if dx.abs_diff(position.0)
                                + dy.abs_diff(position.1)
                                + dz.abs_diff(position.2)
                                != 1
                            {
                                continue;
                            }
                            queue.push_back((dx, dy, dz, position.3 + 1));
                        }
                    }
                }
            }
        }
        min_murk = min_murk.min(murkyness);
    }
    println!("{}", min_murk);
}
