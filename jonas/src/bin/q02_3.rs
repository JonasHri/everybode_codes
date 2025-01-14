use std::fs;

fn main() {
    let message: Vec<String> = fs::read_to_string("./inputs/everybody_codes_e2024_q02_p3.txt")
        .unwrap()
        .lines()
        .map(String::from)
        .collect();

    let mut rune_words: Vec<String> = message[0].split(':').collect::<Vec<&str>>()[1]
        .split(',')
        .map(String::from)
        .collect();

    let mut rune_words_bwd: Vec<String> = rune_words
        .iter()
        .map(|x| x.chars().rev().collect::<String>())
        .collect::<Vec<String>>();

    rune_words.append(&mut rune_words_bwd);

    let scale_mail: Vec<Vec<char>> = message[2..]
        .iter()
        .map(|x| x.chars().collect::<Vec<char>>())
        .collect();

    let mut is_rune = vec![vec![0; scale_mail[0].len()]; scale_mail.len()];

    for i in 0..scale_mail.len() {
        for j in 0..scale_mail[0].len() {
            for dir in 0..=1 {
                for rw in &rune_words {
                    let mut correct = true;
                    for (pos, chr) in rw.chars().enumerate() {
                        let di = i + dir * pos;
                        let dj = (j + (1 - dir) * pos) % scale_mail[0].len();
                        if di >= scale_mail.len() || scale_mail[di][dj] != chr {
                            correct = false;
                            break;
                        }
                    }
                    if correct {
                        for pos in 0..rw.len() {
                            let di = (i + dir * pos) % scale_mail.len();
                            let dj = (j + (1 - dir) * pos) % scale_mail[0].len();
                            is_rune[di][dj] = 1;
                        }
                    }
                }
            }
        }
    }

    let rune_count: usize = is_rune.iter().map(|line| line.iter().sum::<usize>()).sum();
    println!("{}", rune_count);
    // is_rune.iter().for_each(|x| println!("{:?}", x));
    // scale_mail.iter().for_each(|x| println!("{:?}", x));
    // println!("{:?}", rune_words);
}
