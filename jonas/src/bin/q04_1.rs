use std::fs;

fn main() {
    let nails: Vec<i32> = fs::read_to_string("./inputs/everybody_codes_e2024_q04_p2.txt")
        .unwrap()
        .lines()
        .map(|line| str::parse::<i32>(line).unwrap())
        .collect();

    let min_heigt = nails.iter().min().unwrap();
    let hits = nails.iter().sum::<i32>() - min_heigt * nails.len() as i32;
    println!("{:?}", hits);
}
