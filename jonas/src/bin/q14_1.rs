use std::fs;

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
    let file = fs::read_to_string("./inputs/everybody_codes_e2024_q14_p1.txt").unwrap();
    let growth_seq: Vec<&str> = file.split(',').collect();

    let mut dirs: Vec<(i32, i32, i32)> = Vec::new();
    let mut amounts: Vec<i32> = Vec::new();

    for val in growth_seq {
        let chars = val.chars().collect::<Vec<char>>();
        dirs.push(dir_to_cord(chars[0]));
        amounts.push(chars[1..].iter().collect::<String>().parse().unwrap());
    }

    let mut pos = (0, 0, 0);
    let mut max_height = 0;
    for (i, amount) in amounts.iter().enumerate() {
        pos.0 += amount * dirs[i].0;
        pos.1 += amount * dirs[i].1;
        pos.2 += amount * dirs[i].2;
        max_height = max_height.max(pos.2);
    }
    println!("{}", max_height);
}
