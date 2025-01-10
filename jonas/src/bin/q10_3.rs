use std::{cmp, fs, vec};

fn main() {
    let mut runes: Vec<Vec<char>> = fs::read_to_string("./inputs/everybody_codes_e2024_q10_p3.txt")
        .unwrap()
        .lines()
        .map(|line| line.chars().collect())
        .collect();

    // runes.iter().for_each(|x| println!("{:?}", x));

    for _ in 0..100 {
        for ud in (0..runes.len() - 3).step_by(6) {
            for lr in (0..runes[0].len() - 3).step_by(6) {
                for i in 2..=5 {
                    for j in 2..=5 {
                        let mut char_count = vec![0].repeat(256);
                        for delta in vec![0, 1, 6, 7] {
                            let rune_lr = runes[ud + delta][lr + j];
                            let rune_ud = runes[ud + i][lr + delta];
                            assert!(rune_lr != '.');
                            assert!(rune_ud != '.');
                            char_count[rune_lr as usize] += 1;
                            char_count[rune_ud as usize] += 1;
                        }
                        let fitting_chars = char_count.iter().filter(|x| **x == 2).count();
                        let char_code = match char_count.iter().position(|x| *x == 2) {
                            Some(x) => x,
                            _ => 0,
                        };
                        runes[ud + i][lr + j] = match fitting_chars {
                            1 => char::from_u32(char_code as u32).unwrap(),
                            0 => match char_count[63] {
                                1 => runes[ud + i][lr + j],
                                _ => '#',
                            },
                            _ => '#',
                        };
                    }
                }
            }
        }
        for ud in (0..runes.len() - 3).step_by(6) {
            for lr in (0..runes[0].len() - 3).step_by(6) {
                for i in 2..=5 {
                    for j in 2..=5 {
                        if runes[ud + i][lr + j] != '.' {
                            continue;
                        }
                        for delta in vec![0, 1, 6, 7] {
                            let rune_lr = runes[ud + delta][lr + j];
                            let rune_ud = runes[ud + i][lr + delta];
                            let mut out_runes: Vec<char> = vec![];
                            let mut in_runes: Vec<char> = vec![];
                            let mut q_i = 0;
                            let mut q_j = 0;
                            if rune_ud == '?' {
                                q_i = ud + i;
                                q_j = lr + delta;
                                // runes[q_i][q_j] = '/';
                                out_runes = vec![0, 1, 6, 7]
                                    .iter()
                                    .map(|x| runes[ud + x][lr + j])
                                    .collect();
                                in_runes = vec![2, 3, 4, 5]
                                    .iter()
                                    .map(|x| runes[ud + x][lr + j])
                                    .collect();
                            } else if rune_lr == '?' {
                                q_i = ud + delta;
                                q_j = lr + j;
                                // runes[q_i][q_j] = '/';
                                out_runes = vec![0, 1, 6, 7]
                                    .iter()
                                    .map(|x| runes[ud + i][lr + x])
                                    .collect();
                                in_runes = vec![2, 3, 4, 5]
                                    .iter()
                                    .map(|x| runes[ud + i][lr + x])
                                    .collect();
                            }
                            let mut placecount = 0;
                            for or in out_runes.clone() {
                                if in_runes.contains(&or) {
                                    continue;
                                } else {
                                    placecount += 1;
                                }
                            }
                            if placecount == 1 {
                                for or in out_runes {
                                    if in_runes.contains(&or) {
                                        continue;
                                    } else {
                                        runes[ud + i][lr + j] = or;
                                        runes[q_i][q_j] = or;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    println!();
    for i in 0..runes.len() {
        for j in 0..runes[0].len() {
            print!("{}", runes[i][j]);
        }
        println!()
    }

    let mut total_power: i64 = 0;
    for ud in (0..runes.len() - 3).step_by(6) {
        for lr in (0..runes[0].len() - 3).step_by(6) {
            let mut pos = 1;
            let mut current_power = 0;
            for i in 2..=5 {
                for j in 2..=5 {
                    let rune = runes[ud + i][lr + j];
                    if rune == '.' || rune == '#' {
                        current_power = -99999999;
                    }
                    current_power += (rune as i64 - 'A' as i64 + 1) * pos;
                    pos += 1;
                }
            }
            let fin_power = cmp::max(0, current_power);
            // println!("{}", fin_power);
            total_power += fin_power;
        }
    }

    println!("{}", total_power)
}
