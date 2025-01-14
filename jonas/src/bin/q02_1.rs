use std::fs;

fn main() {
    let message: Vec<String> = fs::read_to_string("./inputs/everybody_codes_e2024_q02_p1.txt")
        .unwrap()
        .lines()
        .map(String::from)
        .collect();
    for line in &message {
        println!("{}", line);
    }

    let rune_words: Vec<&str> = message[0].split(':').collect::<Vec<&str>>()[1]
        .split(',')
        .collect();
    println!("{:?}", rune_words);

    let words: Vec<&str> = message[2].split(' ').collect();

    println!("{:?}", words);

    let rune_counts: Vec<usize> = words
        .iter()
        .map(|x| {
            rune_words
                .iter()
                .map(|y| x.contains(y) as usize)
                .sum::<usize>()
        })
        .collect();

    println!("{}", rune_counts.iter().sum::<usize>());
}
