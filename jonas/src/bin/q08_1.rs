use std::fs;
fn main() {
    let mut stones: i32 = fs::read_to_string("./inputs/everybody_codes_e2024_q08_p1.txt")
        .unwrap()
        .parse::<i32>()
        .unwrap();

    // stones = 13;
    let mut step = 1;
    let mut pyramid = 1;
    while pyramid < stones {
        step += 2;
        pyramid += step;
    }

    println!("{} {} {}", step * (pyramid - stones), step, pyramid);
}
