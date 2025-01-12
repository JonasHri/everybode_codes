use std::fs;

fn _ch_to_num(chr: char) -> usize {
    chr as usize - 'A' as usize
}

fn ch_to_idx(c1: char, c2: char, c3: char) -> usize {
    (_ch_to_num(c1) * 26 * 26) + (_ch_to_num(c2) * 26) + _ch_to_num(c3)
}

fn main() {
    let message: Vec<String> = fs::read_to_string("./inputs/everybody_codes_e2024_q11_p3.txt")
        .unwrap()
        .lines()
        .map(String::from)
        .collect();

    let mut min_pop = u64::max_value();
    let mut max_pop = 0;

    let possible_starters: Vec<&str> = message
        .iter()
        .map(|x| x.split(":").collect::<Vec<&str>>()[0])
        .collect();

    for starter in possible_starters {
        let start_chars: Vec<char> = starter.chars().collect();
        let mut current_pop: Vec<u64> = vec![0].repeat(26 * 26 * 26);
        let mut next_pop = current_pop.clone();

        current_pop[ch_to_idx(start_chars[0], start_chars[1], start_chars[2])] = 1;

        for _ in 0..20 {
            for line in &message {
                let linevec = line.chars().collect::<Vec<char>>();
                let current_count = current_pop[ch_to_idx(linevec[0], linevec[1], linevec[2])];
                for i in (4..linevec.len() - 2).step_by(4) {
                    next_pop[ch_to_idx(linevec[i], linevec[i + 1], linevec[i + 2])] +=
                        current_count;
                }
            }

            current_pop = next_pop;
            next_pop = vec![0].repeat(26 * 26 * 26);
        }

        let fin_pop = current_pop.iter().sum::<u64>();
        if fin_pop < min_pop {
            min_pop = fin_pop;
        }
        if fin_pop > max_pop {
            max_pop = fin_pop;
        }
    }
    println!("{}", max_pop - min_pop);
}
