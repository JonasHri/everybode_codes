use std::fs;

use itertools::Itertools;

fn get_display(faces: &Vec<Vec<&str>>, advances: &Vec<usize>, spins: usize, offset: i32) -> String {
    let positions = advances
        .iter()
        .enumerate()
        .map(|(i, val)| {
            (val * spins + (offset + 1000 * faces[i].len() as i32) as usize) % faces[i].len()
        })
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
    let machine: Vec<String> = fs::read_to_string("./inputs/everybody_codes_e2024_q16_p3.txt")
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

    let pull_count = 256;

    let mut min_pay = vec![vec![usize::MAX / 2; 4 * pull_count]; pull_count + 1];
    let mut max_pay = vec![vec![0; 2 * pull_count + 1]; pull_count + 1];

    min_pay[1][pull_count] = payout_display(&get_display(&eyes, &advances, 1, 0));
    min_pay[1][pull_count + 1] = payout_display(&get_display(&eyes, &advances, 1, 1));
    min_pay[1][pull_count - 1] = payout_display(&get_display(&eyes, &advances, 1, -1));
    max_pay[1][pull_count] = payout_display(&get_display(&eyes, &advances, 1, 0));
    max_pay[1][pull_count + 1] = payout_display(&get_display(&eyes, &advances, 1, 1));
    max_pay[1][pull_count - 1] = payout_display(&get_display(&eyes, &advances, 1, -1));

    for pull in 1..pull_count {
        for ofs in -(pull as i32)..=(pull as i32) {
            let pos = (pull_count as i32 + ofs) as usize;

            let coins_max = max_pay[pull][pos];
            max_pay[pull + 1][pos + 1] = max_pay[pull + 1][pos + 1]
                .max(payout_display(&get_display(&eyes, &advances, pull + 1, ofs + 1)) + coins_max);
            max_pay[pull + 1][pos - 1] = max_pay[pull + 1][pos - 1]
                .max(payout_display(&get_display(&eyes, &advances, pull + 1, ofs - 1)) + coins_max);
            max_pay[pull + 1][pos] = max_pay[pull + 1][pos]
                .max(payout_display(&get_display(&eyes, &advances, pull + 1, ofs)) + coins_max);

            let coins_min = min_pay[pull][pos];
            min_pay[pull + 1][pos + 1] = min_pay[pull + 1][pos + 1]
                .min(payout_display(&get_display(&eyes, &advances, pull + 1, ofs + 1)) + coins_min);
            min_pay[pull + 1][pos - 1] = min_pay[pull + 1][pos - 1]
                .min(payout_display(&get_display(&eyes, &advances, pull + 1, ofs - 1)) + coins_min);
            min_pay[pull + 1][pos] = min_pay[pull + 1][pos]
                .min(payout_display(&get_display(&eyes, &advances, pull + 1, ofs)) + coins_min);
        }
    }

    // max_pay.iter().for_each(|x| println!("{:?}", x));

    println!(
        "{} {}",
        max_pay[pull_count].iter().max().unwrap(),
        min_pay[pull_count].iter().min().unwrap()
    )
}
