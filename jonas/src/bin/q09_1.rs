use std::fs;
fn main() {
    let mut brightnesses: Vec<i32> =
        fs::read_to_string("./inputs/everybody_codes_e2024_q09_p1.txt")
            .unwrap()
            .lines()
            .map(|x| match x.parse::<i32>() {
                Ok(res) => res,
                _ => -1,
            })
            .collect::<Vec<i32>>();

    // brightnesses = vec![2, 4, 7, 16];

    let stamps = vec![1, 3, 5, 10];

    let mut total_stamps = 0;
    for brightness in brightnesses.clone() {
        let mut br = brightness;
        for stamp in stamps.iter().rev() {
            total_stamps += br / stamp;
            br = br % stamp;
        }
    }

    println!("{}", total_stamps);
    println!("{:?}", brightnesses);
}
