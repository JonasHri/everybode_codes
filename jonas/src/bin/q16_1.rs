use std::fs;

use itertools::Itertools;

fn get_display(faces: Vec<Vec<&str>>, advances: Vec<usize>, spins: usize) -> String {
    let positions = advances
        .iter()
        .enumerate()
        .map(|(i, val)| val * spins % faces[i].len())
        .collect::<Vec<usize>>();
    let result = positions
        .iter()
        .enumerate()
        .map(|(i, &pos)| faces[i][pos])
        .join("");
    return result;
}

fn main() {
    let machine: Vec<String> = fs::read_to_string("./inputs/everybody_codes_e2024_q16_p1.txt")
        .unwrap()
        .lines()
        .map(|line| line.to_owned())
        .collect();

    let advances: Vec<usize> = machine[0]
        .split(',')
        .map(|x| x.parse::<usize>().unwrap())
        .collect();

    let faces = (0..advances.len())
        .map(|j| {
            (2..machine.len())
                .map(|i| &machine[i][4 * j..4 * j + 3])
                .filter(|x| !x.eq(&"   "))
                .collect::<Vec<&str>>()
        })
        .collect::<Vec<Vec<&str>>>();

    let res = get_display(faces, advances, 100);

    let mut coins = 0;
    let mut streak = 0;
    let mut cur = 'S';

    for c in res.chars().sorted().collect::<Vec<char>>() {
        if c == cur {
            streak += 1;
        } else {
            coins += 0.max(streak - 2);
            streak = 0;
            cur = c;
        }
    }
    println!("{} {}", res, coins);
}
