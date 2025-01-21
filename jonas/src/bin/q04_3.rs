use std::fs;

fn main() {
    let mut nails: Vec<usize> = fs::read_to_string("./inputs/everybody_codes_e2024_q04_p3.txt")
        .unwrap()
        .lines()
        .map(|line| str::parse::<usize>(line).unwrap())
        .collect();

    nails.sort();
    let target_height = nails[nails.len() / 2];

    let target_height_alt = nails.iter().sum::<usize>() / nails.len();

    println!("{} {}", target_height, target_height_alt);

    let hits = nails
        .iter()
        .map(|x| x.abs_diff(target_height))
        .sum::<usize>();
    println!("{:?}", hits);
}
