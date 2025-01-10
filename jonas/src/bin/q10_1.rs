use std::fs;

fn main() {
    let runes: Vec<Vec<char>> = fs::read_to_string("./inputs/everybody_codes_e2024_q10_p1.txt")
        .unwrap()
        .lines()
        .map(|line| line.chars().collect())
        .collect();

    runes.iter().for_each(|x| println!("{:?}", x));

    for i in 0..runes.len() {
        for j in 0..runes[0].len() {
            if runes[i][j] != '.' {
                continue;
            }
            let mut char_count = vec![0].repeat(256);
            for delta in 0..runes.len() {
                if runes[delta][j] != '.' {
                    char_count[runes[delta][j] as usize] += 1;
                }
                if runes[i][delta] != '.' {
                    char_count[runes[i][delta] as usize] += 1;
                }
            }
            // println!("{} {}", i, j);
            // println!("{:?}", char_count);

            print!(
                "{}",
                char::from_u32(char_count.iter().position(|x| *x == 2).unwrap() as u32).unwrap()
            );
        }
    }

    println!();
}
