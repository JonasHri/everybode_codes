use std::fs;

fn main() {
    let people_alt: Vec<Vec<usize>> =
        fs::read_to_string("./inputs/everybody_codes_e2024_q05_p3.txt")
            .unwrap()
            .lines()
            .map(|line| {
                line.split(' ')
                    .map(|x| str::parse::<usize>(x).unwrap())
                    .collect()
            })
            .collect();

    let mut people = vec![vec![0; people_alt.len()]; people_alt[0].len()];

    for (i, col) in people_alt.iter().enumerate() {
        for (j, &val) in col.iter().enumerate() {
            people[j][i] = val;
        }
    }

    let mut seen = 0;

    people.iter().for_each(|x| println!("{:?}", x));

    for i in 0..10e7 as usize {
        let cur_line = i % people.len();
        let next_line = (cur_line + 1) % people.len();
        let mover = people[cur_line].remove(0);
        let nl = people[next_line].len();
        let movepos = (mover - 1) % (2 * nl);
        if movepos < nl {
            people[next_line].insert(movepos, mover);
        } else {
            people[next_line].insert(2 * nl - movepos, mover);
        }
        let mut ran = 0;
        for j in 0..people.len() {
            ran *= 10000;
            ran += people[j][0]
        }
        if ran > seen {
            seen = ran;
            println!("{} {}", ran, i);
        }
    }
}
