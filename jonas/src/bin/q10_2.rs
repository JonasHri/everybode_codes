use std::fs;

fn main() {
    let runes: Vec<Vec<char>> = fs::read_to_string("./inputs/everybody_codes_e2024_q10_p2.txt")
        .unwrap()
        .lines()
        .map(|line| line.chars().collect())
        .collect();

    // runes.iter().for_each(|x| println!("{:?}", x));

    let mut power = 0;

    for ud in (0..runes.len()).step_by(9) {
        for lr in (0..runes[0].len()).step_by(9) {
            let mut pos = 1;
            for i in 2..=5 {
                for j in 2..=5 {
                    let mut char_count = vec![0].repeat(256);
                    for delta in 0..8 {
                        let rune_lr = runes[ud + delta][lr + j];
                        let rune_ud = runes[ud + i][lr + delta];
                        if rune_lr != '.' {
                            char_count[rune_lr as usize] += 1;
                        }
                        if rune_ud != '.' {
                            char_count[rune_ud as usize] += 1;
                        }
                    }
                    // println!("{} {}", i, j);
                    // println!("{:?}", char_count);

                    power +=
                        (char_count.iter().position(|x| *x == 2).unwrap() - 'A' as usize + 1) * pos;
                    pos += 1;

                    // print!(
                    //     "{}",
                    //     char::from_u32(char_count.iter().position(|x| *x == 2).unwrap() as u32)
                    //         .unwrap()
                    // );
                }
            }
        }
    }

    println!("{}", power);
}
