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
    let file = fs::read_to_string("./inputs/everybody_codes_e2024_q14_p2_trial.txt").unwrap();

    let space_size = 200;
    let mut space = vec![vec![vec![0 as usize; space_size]; space_size]; space_size];

    for line in file.lines() {
        let growth_seq: Vec<&str> = line.split(',').collect();

        let mut dirs: Vec<(i32, i32, i32)> = Vec::new();
        let mut amounts: Vec<usize> = Vec::new();

        for val in growth_seq {
            let chars = val.chars().collect::<Vec<char>>();
            dirs.push(dir_to_cord(chars[0]));
            amounts.push(chars[1..].iter().collect::<String>().parse().unwrap());
        }

        let mut pos: (usize, usize, usize) = (100, 100, 0);

        for (i, &amount) in amounts.iter().enumerate() {
            for j in 0..amount {
                pos.0 = (pos.0 as i32 + dirs[i].0) as usize;
                pos.1 = (pos.1 as i32 + dirs[i].1) as usize;
                pos.2 = (pos.2 as i32 + dirs[i].2) as usize;

                space[pos.0][pos.1][pos.2] = 1;
            }
        }
    }

    println!(
        "{}",
        space
            .iter()
            .map(|mat| mat
                .iter()
                .map(|val| val.iter().sum::<usize>())
                .sum::<usize>())
            .sum::<usize>()
    );
}
