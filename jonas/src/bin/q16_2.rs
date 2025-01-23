use std::fs;

use itertools::Itertools;

fn get_display(faces: &Vec<Vec<&str>>, advances: &Vec<usize>, spins: usize) -> String {
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

fn payout_display(display: &String) -> usize {
    let mut coins = 0;
    let mut streak = 1;
    let sort_disp = display.chars().sorted().collect::<Vec<char>>();
    let mut cur = sort_disp[0];

    for idx in 1..sort_disp.len() {
        let c = sort_disp[idx];
        if c == cur {
            streak += 1;
        } else {
            streak = 1;
            cur = c;
        }
        if streak > 2 {
            coins += 1;
        }
    }
    // println!("{} : {}", sort_disp.iter().join(""), coins);
    return coins;
}

fn main() {
    let machine: Vec<String> = fs::read_to_string("./inputs/everybody_codes_e2024_q16_p2.txt")
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

    let eyes_string = faces
        .iter()
        .map(|line| {
            line.iter()
                .map(|x| [&x[0..1], &x[2..3]].join(""))
                .collect::<Vec<String>>()
        })
        .collect::<Vec<Vec<String>>>();

    let eyes = eyes_string
        .iter()
        .map(|line| line.iter().map(|x| x.as_str()).collect::<Vec<&str>>())
        .collect::<Vec<Vec<&str>>>();

    let mut loop_spin = 0;

    for i in 1..1_000_000 {
        let mut val = 0;
        for j in 0..advances.len() {
            val += advances[j] * i % faces[j].len()
        }
        if val == 0 {
            loop_spin = i;
            break;
        }
    }
    println!("{}", loop_spin);

    let total_spins = 202420242024;
    let full_spins = total_spins / loop_spin;
    let partia_spins = total_spins % loop_spin;

    let mut full = 0;
    let mut partial = 0;

    for i in 1..partia_spins + 1 {
        partial += payout_display(&get_display(&eyes, &advances, i));
    }

    if full_spins > 0 {
        for i in 1..loop_spin + 1 {
            full += payout_display(&get_display(&eyes, &advances, i));
        }
    }

    let payout = full * full_spins + partial;

    println!("{} {}", payout, partial);
}
