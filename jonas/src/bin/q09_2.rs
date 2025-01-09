use std::fs;
fn main() {
    let brightnesses: Vec<usize> = fs::read_to_string("./inputs/everybody_codes_e2024_q09_p2.txt")
        .unwrap()
        .lines()
        .map(|x| match x.parse::<usize>() {
            Ok(res) => res,
            _ => 0,
        })
        .collect::<Vec<usize>>();

    let mut needed_stamps =
        vec![0].repeat(brightnesses.iter().max().unwrap().to_owned() + 1 as usize);

    let stamps = vec![1, 3, 5, 10, 15, 16, 20, 24, 25, 30];

    for i in 1..needed_stamps.len() {
        let valid_stamps = stamps.iter().filter(|x| **x <= i).collect::<Vec<&usize>>();

        needed_stamps[i] = valid_stamps
            .iter()
            .map(|x| needed_stamps[i - **x] + 1)
            .min()
            .unwrap() as i32;
    }

    println!(
        "{}",
        brightnesses.iter().map(|x| needed_stamps[*x]).sum::<i32>()
    );
}
