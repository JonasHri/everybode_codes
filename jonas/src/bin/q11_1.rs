use std::fs;

fn main() {
    let message: Vec<String> = fs::read_to_string("./inputs/everybody_codes_e2024_q11_p1.txt")
        .unwrap()
        .lines()
        .map(String::from)
        .collect();

    let mut current_pop: Vec<usize> = vec![0].repeat(256);
    let mut next_pop = current_pop.clone();

    current_pop['A' as usize] = 1;

    for _ in 0..4 {
        for line in &message {
            let linevec = line.chars().collect::<Vec<char>>();
            let chr_idx = linevec[0];
            let current_count = current_pop[chr_idx as usize];
            for i in (2..linevec.len()).step_by(2) {
                next_pop[linevec[i] as usize] += current_count;
            }
        }

        current_pop = next_pop;
        next_pop = vec![0].repeat(256);
    }

    println!("{}", current_pop.iter().sum::<usize>());
}
