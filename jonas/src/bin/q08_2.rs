use std::fs;
fn main() {
    let null_pr: i32 = fs::read_to_string("./inputs/everybody_codes_e2024_q08_p2.txt")
        .unwrap()
        .parse::<i32>()
        .unwrap();

    let stones = 20240000;

    // let null_pr = 3;
    let acol_pr = 1111;

    let mut step = 1;
    let mut pyramid = 1;
    let mut thick = 1;
    while pyramid < stones {
        step += 2;
        thick = (thick * null_pr) % acol_pr;
        pyramid += step * thick;
    }

    println!("{} {} {}", step * (pyramid - stones), step, pyramid);
}
