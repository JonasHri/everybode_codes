use std::fs;

fn main() {
    let message: Vec<String> = fs::read_to_string("./inputs/everybody_codes_e2024_q02_p2.txt")
        .unwrap()
        .lines()
        .map(String::from)
        .collect();
    // for line in &message {
    //     println!("{}", line);
    // }

    let mut rune_words: Vec<String> = message[0].split(':').collect::<Vec<&str>>()[1]
        .split(',')
        .map(String::from)
        .collect();

    let mut rune_words_bwd: Vec<String> = rune_words
        .iter()
        .map(|x| x.chars().rev().collect::<String>())
        .collect::<Vec<String>>();

    rune_words.append(&mut rune_words_bwd);
    // rune_words.iter().for_each(|x| println!("{}", x));

    let mut total_power = 0;
    for line in &message[2..] {
        // println!("{}", line);
        let mut is_rune = vec![0].repeat(line.len());
        for rw in &rune_words {
            let mut indexes: Vec<usize> = line.match_indices(rw).map(|x| x.0).collect();
            let mut rindexes: Vec<usize> = line.rmatch_indices(rw).map(|x| x.0).collect();
            indexes.append(&mut rindexes);
            for start in indexes {
                for i in 0..rw.len() {
                    is_rune[start + i] = 1;
                }
            }
        }
        println!("{}", line);
        is_rune.iter().for_each(|x| print!("{}", x));
        println!();
        total_power += is_rune.iter().sum::<usize>();
    }

    println!("{}", total_power);
}
